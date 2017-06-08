
class LibOSRM::OSRM
  def initialize
    config = LibOSRM::EngineConfig.new
    config.storage_config = "TODO"
    config.use_shared_memory = false

    osrm = { "osrm" => config }

    RouteParameters params

    #// Route in monaco
    #params.coordinates.push_back({util::FloatLongitude{7.419758}, util::FloatLatitude{43.731142}});
    #params.coordinates.push_back({util::FloatLongitude{7.419505}, util::FloatLatitude{43.736825}});

    #// Response is in JSON format
    #json::Object result;

    #// Execute routing request, this does the heavy lifting
    #const auto status = osrm.Route(params, result);

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