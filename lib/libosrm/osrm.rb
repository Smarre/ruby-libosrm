
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

    osrm = LibOSRM::OSRM.new(config)

    params = LibOSRM::RouteParameters.new
    params << [ 60.16468, 24.94119 ]
    params << [ 60.17427, 24.95888 ]

    result = osrm.route params
    puts result.inspect

=begin
    if (status == Status::Ok) {
        auto &routes = result.values["routes"].get<json::Array>();

        // Let's just use the first route
        auto &route = routes.values.at(0).get<json::Object>();
        const auto distance = route.values["distance"].get<json::Number>().value;
        const auto duration = route.values["duration"].get<json::Number>().value;

        // Warn users if extract does not contain the default coordinates from above
        if (distance == 0 || duration == 0)
        {
            std::cout << "Note: distance or duration is zero. ";
            std::cout << "You are probably doing a query outside of the OSM extract.\n\n";
        }

        std::cout << "Distance: " << distance << " meter\n";
        std::cout << "Duration: " << duration << " seconds\n";
        return EXIT_SUCCESS;
    }
    else if (status == Status::Error)
    {
        const auto code = result.values["code"].get<json::String>().value;
        const auto message = result.values["message"].get<json::String>().value;

        std::cout << "Code: " << code << "\n";
        std::cout << "Message: " << code << "\n";
        return EXIT_FAILURE;
    }
=end
  end

  def distance_by_roads addresses
    nil
  end
end

osrm = LibOSRM::RubyOSRM.new