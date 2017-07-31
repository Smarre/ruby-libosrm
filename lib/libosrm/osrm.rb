# frozen_string_literal: true

require_relative "../libosrm"
require_relative "route_parameters"

class LibOSRM::RubyOSRM
  def initialize
    config = LibOSRM::EngineConfig.new
    LibOSRM::EngineConfig::Algorithm.each do |x|
      #puts x.inspect
    end
    st = LibOSRM::StorageConfig.new "test/helsinki_finland.osrm"
    config.storage_config = st
    config.use_shared_memory = false

    @osrm = LibOSRM::OSRM.new(config)
  end

  # NOTE: coordinates must be numbers, Strings are not accepted.
  def distance_by_roads coordinates
    params = LibOSRM::RouteParameters.new
    coordinates.each do |coord|
      params << [ coord[:latitude], coord[:longitude] ]
    end

    @osrm.distance_by_roads params
  end
end

osrm = LibOSRM::RubyOSRM.new