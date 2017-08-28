# frozen_string_literal: true

require_relative "../libosrm"
require_relative "route_parameters"

class LibOSRM::OSRM

  def tile_with_coordinates latitude, longitude, zoom
    xy = coordinates_to_tile_numbers latitude, longitude, zoom
    tile xy[:x], xy[:y], zoom
  end

  def coordinates_to_tile_numbers latitude, longitude, zoom
    lat_rad = latitude / 180 * Math::PI
    n = 2.0 ** zoom
    x = ((longitude + 180.0) / 360.0 * n).to_i
    y = ((1.0 - Math::log(Math::tan(lat_rad) + (1 / Math::cos(lat_rad))) / Math::PI) / 2.0 * n).to_i

    {:x => x, :y =>y}
  end
end