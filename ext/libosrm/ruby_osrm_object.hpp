#ifndef RUBY_OSRM_OBJECT_H_
#define RUBY_OSRM_OBJECT_H_

#include "globals.hpp"

#include <osrm/osrm.hpp>
#include <osrm/route_parameters.hpp>
#include <osrm/table_parameters.hpp>
#include <osrm/nearest_parameters.hpp>
#include <osrm/trip_parameters.hpp>
#include <osrm/match_parameters.hpp>
#include <osrm/tile_parameters.hpp>
#include <osrm/json_container.hpp>

// Hackery for getting rendered JSON
//#include "util/json_renderer.hpp"

Data_Type<osrm::OSRM> rb_cOsrm;

/*
template<>
osrm::EngineConfig from_ruby<osrm::EngineConfig>(Object x) {
    Data_Object<osrm::EngineConfig> d(x, rb_cOsrm);
    return *d;
}
*/

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

    // This can be used to get the response with a little bit of hackery...
    //osrm::util::json::render(std::cout, result);

    auto &routes = result.values["routes"].get<osrm::json::Array>();

    // Let's just use the first route
    auto &route = routes.values.at(0).get<osrm::json::Object>();
    const auto distance = route.values["distance"].get<osrm::json::Number>().value;
    const auto duration = route.values["duration"].get<osrm::json::Number>().value;

    // Warn users if extract does not contain the default coordinates from above
    if (distance == 0 || duration == 0) {
        std::cout << "Note: distance or duration is zero. ";
        std::cout << "You are probably doing a query outside of the OSM extract.\n\n";
    }

    std::cout << "Distance: " << distance << " meter\n";
    std::cout << "Duration: " << duration << " seconds\n";

    // and then convert back so we get the result we want to have
    return to_ruby(result);
}

void init_osrm_object() {
    rb_cOsrm =
            define_class_under<osrm::OSRM>(rb_mLibOSRM, "OSRM")
                .define_constructor(Constructor<osrm::OSRM, osrm::EngineConfig>(), Arg("config"))
                .define_method("route", &wrap_route)
                .define_method("table", &osrm::OSRM::Table)
                .define_method("nearest", &osrm::OSRM::Nearest)
                .define_method("trip", &osrm::OSRM::Trip)
                .define_method("match", &osrm::OSRM::Match)
                .define_method("tile", &osrm::OSRM::Tile)
            ;
}

#endif