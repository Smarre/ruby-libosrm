
#include "ruby_osrm_object.hpp"

using namespace Rice;

Data_Type<osrm::OSRM> rb_cOsrm;

Object wrap_distance_by_roads(Object self, Object o) {
    // Convert Ruby object to native type
    osrm::RouteParameters params;

    Array coordinates = o.iv_get("@coordinates");
    Array::iterator it = coordinates.begin();
    Array::iterator end = coordinates.end();
    for(; it != end; ++it) {
        Array latlon = (Array)*it;
        double lat = from_ruby<double>(latlon[0]);
        double lon = from_ruby<double>(latlon[1]);
        params.coordinates.push_back({osrm::util::FloatLongitude{lon}, osrm::util::FloatLatitude{lat}});
    }

    params.overview = osrm::RouteParameters::OverviewType::False;

    // Response is in JSON format
    osrm::json::Object result;

    Data_Object<osrm::OSRM> osrm(self);

    // Execute routing request, this does the heavy lifting
    const auto status = osrm->Route(params, result);

    if (status != osrm::Status::Ok) {
        const auto code = result.values["code"].get<osrm::json::String>().value;
        const auto message = result.values["message"].get<osrm::json::String>().value;

        throw Exception(rb_eRuntimeError, "Failed to route with given input. error code: %s, message: %s", code.c_str(), message.c_str());
    }

    // We can take first route since we only want the distance.
    auto &routes = result.values["routes"].get<osrm::json::Array>();
    auto &route = routes.values.at(0).get<osrm::json::Object>();

    const auto distance = route.values["distance"].get<osrm::json::Number>().value;

    return to_ruby(distance);
}

Object wrap_route(Object self, Object o) {
    // Convert Ruby object to native type
    osrm::RouteParameters params;

    Array coordinates = o.iv_get("@coordinates");
    Array::iterator it = coordinates.begin();
    Array::iterator end = coordinates.end();
    for(; it != end; ++it) {
        Array latlon = (Array)*it;
        double lat = from_ruby<double>(latlon[0]);
        double lon = from_ruby<double>(latlon[1]);
        params.coordinates.push_back({osrm::util::FloatLongitude{lon}, osrm::util::FloatLatitude{lat}});
    }

    // Response is in JSON format
    osrm::json::Object result;

    Data_Object<osrm::OSRM> osrm(self);

    // Execute routing request, this does the heavy lifting
    const auto status = osrm->Route(params, result);

    if (status != osrm::Status::Ok) {
        const auto code = result.values["code"].get<osrm::json::String>().value;
        const auto message = result.values["message"].get<osrm::json::String>().value;

        throw Exception(rb_eRuntimeError, "Failed to route with given input. error code: %s, message: %s", code.c_str(), message.c_str());
    }

    Hash routes_result;
    routes_result[String("code")] = result.values["code"].get<osrm::json::String>().value;

    Array routes_array;
    auto &routeValues = result.values["routes"].get<osrm::json::Array>();
    for(auto const& routeValue : routeValues.values) {
        auto route = routeValue.get<osrm::json::Object>();
        Hash route_result;
        for(std::pair<std::string, osrm::util::json::Value> e : route.values) {
            if(e.first == "distance") {
                route_result[String("distance")] = e.second.get<osrm::json::Number>().value;
            } else if(e.first == "duration") {
                route_result[String("duration")] = e.second.get<osrm::json::Number>().value;
            } else if(e.first == "weight") {
                route_result[String("weight")] = e.second.get<osrm::json::Number>().value;
            } else if(e.first == "weight_name") {
                route_result[String("weight_name")] = e.second.get<osrm::json::String>().value;
            } else if(e.first == "geometry") {
                // TODO
            } else if(e.first == "legs") {
                // TODO
            } else {
                throw Exception(rb_eRuntimeError, "Invalid JSON value when building a route from libosrm.so: %s", e.first.c_str());
            }
        }

        routes_array.push(route_result);
    }
    routes_result[String("routes")] = routes_array;

    return routes_result;
}

void init_osrm_object() {
    rb_cOsrm = define_class_under<osrm::OSRM>(rb_mLibOSRM, "OSRM")
                .define_constructor(Constructor<osrm::OSRM, osrm::EngineConfig>(), Arg("config"))
                .define_method("distance_by_roads", &wrap_distance_by_roads)
                .define_method("route", &wrap_route)
                .define_method("table", &osrm::OSRM::Table)
                .define_method("nearest", &osrm::OSRM::Nearest)
                .define_method("trip", &osrm::OSRM::Trip)
                .define_method("match", &osrm::OSRM::Match)
                .define_method("tile", &osrm::OSRM::Tile)
            ;
}