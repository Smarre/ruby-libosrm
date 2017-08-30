# frozen_string_literal: true

require_relative "../libosrm"

class LibOSRM::OSRM

  # @!macro [new] native
  #   @note This method is implemented in native code.

  # @!macro [new] api_method
  #   @note This method is a wrapper for OSRM’s API.
  #     Please see the {http://project-osrm.org/docs/v5.10.0/api HTTP API} for documentation of response values.
  #
  #     Any differences should be documented in corresponding methods;
  #     please report should you find any.

  # @!macro [new] api_method_return
  #   @return [Hash] Hash of response data as documented at {http://project-osrm.org/docs/v5.10.0/api HTTP API}

  # @!macro [new] coordinates_param
  #   @param coordinates [Array] Array of coordinates. See {#distance_by_roads} for an example.

  # @!method initialize(osrm_file)
  #   @!macro native
  #   Initializes OSRM object for routing actions.
  #
  #   @param osrm_file [String] Path to the OSRM file.

  # @!method distance_by_roads(coordinates)
  #   @!macro native
  #
  #   Calculates distance by roads from given coordinates.
  #
  #   Internally operates by invoking {#route}, but
  #   this method is implemented in native code so this works faster
  #   than {#route} if you only need distance and no other data.
  #
  #   @example Input coordinates array
  #     [
  #       { latitude: from_lat, longitude: from_lon },
  #       { latitude: to_lat, longitude: to_lon }
  #     ]
  #
  #   @param coordinates [Array] Array of coordinate hashes
  #   @return Float distance by roads in meters

  # @!method route(coordinates, opts = nil)
  #   @!macro native
  #   @!macro api_method
  #
  #   OSRM routing action. Takes two or more coordinate pairs and calculates distance
  #   by roads between them. A successful response contains an array of resulting routing data, between each
  #   point in the request.
  #
  #   @note If you only want to know distance by roads for the trip, use {#distance_by_roads} instead.
  #
  #   @!macro coordinates_param
  #   @param opts [Hash] Options to customize the request.
  #   @option opts [Symbol] :geometry_type Format in which the geometries will be returned at. Possible values: :polyline, :polyline6, :geojson. Defaults to :polyline.
  #   @option opts [Boolean] :steps Whether steps should be included in response
  #   @option opts [Boolean] :annotations Whether annotations should be included in response
  #
  #   @!macro api_method_return

  # @!method table(coordinates, opts = nil)
  #   @!macro native
  #   @!macro api_method
  #
  #   OSRM table action. Takes a list of coordinate pairs and calculates distances between each pair to all other pairs.
  #   The calculations can be customized by sources and destinations parameters. By default full table is calculated.
  #
  #   @!macro coordinates_param
  #   @param opts [Hash] Options to customize the request.
  #   @option opts [Array] :sources List of indices of coordinates array that should be used as a source location
  #   @option opts [Array] :destinations List of indices of coordinates array that should be used as a destination location
  #
  #   @!macro api_method_return

  # @!method nearest(latitude, longitude, amount = 1)
  #   @!macro native
  #   @!macro api_method
  #
  #   OSRM nearest action. Returns nearest street network points.
  #
  #   @param latitude [Float] Source position’s latitude
  #   @param longitude [Float] Source position’s longitude
  #   @param amount [Integer] Amount of nearest entries to be returned
  #
  #   @!macro api_method_return

  # @!method trip(coordinates)
  #   @!macro native
  #   @!macro api_method
  #
  #   Tries to calculate shortest possible route between given coordinates (and then back to original point;
  #   i.e. the first coordinate pair in the input), in order to solve the travelling salesman problem.
  #
  #   @!macro coordinates_param
  #
  #   @!macro api_method_return

  # @!method match(coordinates, opts = nil)
  #   @!macro native
  #   @!macro api_method
  #
  #   Tries to match given coordinates to road network in most plausible way.
  #
  #   @todo This action most likely does not work as expected.
  #
  #   @!macro coordinates_param
  #
  #   @!macro api_method_return

  # @!method tile(x, y, zoom)
  #   @!macro native
  #   @!macro api_method
  #
  #   Calculates a vector tile image that can be used to examine the routing graph. See the official documentation
  #   for more comprehensive documentation about this feature.
  #
  #   @note You should most likely use {#tile_with_coordinates} instead.
  #
  #   @param x [Integer] Tile index as documented at https://wiki.openstreetmap.org/wiki/Slippy_map_tilenames
  #   @param y [Integer] Tile index as documented at https://wiki.openstreetmap.org/wiki/Slippy_map_tilenames
  #   @param zoom [Integer] Map zoom level to generate the tile data
  #
  #   @!macro api_method_return

  # Invokes {#tile}, but first converts given coordinates to tile numbers.
  #
  # @param latitude [Float] Latitude of the location to get the tile data for
  # @param longitude [Float] Longitude of the location to get the tile data for
  # @param zoom [Integer] Map zoom level for the tile image. Controls size of the image.
  def tile_with_coordinates latitude, longitude, zoom
    xy = coordinates_to_tile_numbers latitude, longitude, zoom
    tile xy[:x], xy[:y], zoom
  end

  # Converts coordinates to tile numbers as expected by {#tile}.
  #
  # @param latitude [Float] Latitude of the location to get the tile data for
  # @param longitude [Float] Longitude of the location to get the tile data for
  # @param zoom [Integer] Map zoom level for the tile image. Controls size of the image.
  def coordinates_to_tile_numbers latitude, longitude, zoom
    lat_rad = latitude / 180 * Math::PI
    n = 2.0 ** zoom
    x = ((longitude + 180.0) / 360.0 * n).to_i
    y = ((1.0 - Math::log(Math::tan(lat_rad) + (1 / Math::cos(lat_rad))) / Math::PI) / 2.0 * n).to_i

    {:x => x, :y =>y}
  end
end