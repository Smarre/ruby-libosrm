
#include "ruby_osrm_object.hpp"
#include "osrm_match_func.hpp"
#include "osrm_nearest_func.hpp"
#include "osrm_route_func.hpp"
#include "osrm_tile_func.hpp"
#include "osrm_table_func.hpp"

using namespace Rice;

Data_Type<osrm::OSRM> rb_cOsrm;

template<>
osrm::engine::EngineConfig from_ruby<osrm::engine::EngineConfig>(Object x) {
    if(x.is_nil()) {
        // TODO: raise error
    }

    osrm::engine::EngineConfig config;
    config.storage_config = { x.to_s().c_str() };
    config.use_shared_memory = false;
    return config;
}

Object wrap_distance_by_roads(Object self, Object o) {

    // Convert Ruby object to native type
    osrm::RouteParameters params;

    Array coordinates = o;
    Array::iterator it = coordinates.begin();
    Array::iterator end = coordinates.end();
    for(; it != end; ++it) {
        Hash latlon = (Hash)*it;
        double lat = from_ruby<double>(latlon[Symbol("latitude")]);
        double lon = from_ruby<double>(latlon[Symbol("longitude")]);
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

void init_osrm_object() {
    rb_cOsrm = define_class_under<osrm::OSRM>(rb_mLibOSRM, "OSRM")
                .define_constructor(Constructor<osrm::OSRM, osrm::EngineConfig>(), Arg("config"))
                .define_method("distance_by_roads", &wrap_distance_by_roads)
                .define_method("route", &wrap_route, (Arg("coordinates"), Arg("opts") = Nil))
                .define_method("table", &wrap_table, (Arg("coordinates"), Arg("opts") = Nil))
                .define_method("nearest", &wrap_nearest, (Arg("latitude"), Arg("longitude"), Arg("amount") = 1))
                .define_method("trip", &osrm::OSRM::Trip)
                .define_method("match", &wrap_match, (Arg("coordinates"), Arg("opts") = Nil))
                .define_method("tile", &wrap_tile, (Arg("x"), Arg("y"), Arg("zoom")))
            ;
}