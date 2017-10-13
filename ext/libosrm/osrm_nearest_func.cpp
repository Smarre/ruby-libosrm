
#include "osrm_nearest_func.hpp"

#include <osrm/nearest_parameters.hpp>

Object wrap_nearest(Object self, double latitude, double longitude, int amount) {
    NearestFunc func;
    return func.wrap_nearest(self, latitude, longitude, amount);
}

Hash NearestFunc::parse_nearest_result(osrm::json::Object nearest) {
    Hash result;
    for(std::pair<std::string, osrm::util::json::Value> e : nearest.values) {
        if(e.first == "code") {
            result[String("code")] = e.second.get<osrm::json::String>().value;
        } else if(e.first == "waypoints") {
            result[String("waypoints")] = parse_waypoints(e.second.get<osrm::json::Array>());
        } else {
            throw Exception(rb_eRuntimeError, "Invalid JSON value when building a match from libosrm.so: %s", e.first.c_str());
        }
    }

    return result;
}

Object NearestFunc::wrap_nearest(Object self, double latitude, double longitude, int amount) {
    // Convert Ruby object to native type
    osrm::NearestParameters params;

    params.coordinates.push_back({osrm::util::FloatLongitude{longitude}, osrm::util::FloatLatitude{latitude}});

    /*
    if(!opts.is_nil()) {
        Object geometry_type = opts[Symbol("geometry_type")];
        if(!geometry_type.is_nil()) {
            Symbol g_type = (Symbol) geometry_type;
            const char *type = g_type.c_str();
            if(strcmp(type, "polyline") == 0) {
                params.geometries = osrm::RouteParameters::GeometriesType::Polyline;
            }
            if(strcmp(type, "polyline6") == 0) {
                params.geometries = osrm::RouteParameters::GeometriesType::Polyline6;
            }
            if(strcmp(type, "geojson") == 0) {
                params.geometries = osrm::RouteParameters::GeometriesType::GeoJSON;
            }
        }

        Object steps = opts[Symbol("steps")];
        if(steps) {
            params.steps = true;
        }

        Object annotations = opts[Symbol("annotations")];
        if(annotations) {
            params.annotations = true;
        }
    }
    */

    params.number_of_results = amount;

    // Response is in JSON format
    osrm::json::Object result;

    Data_Object<osrm::OSRM> osrm(self);

    // Execute routing request, this does the heavy lifting
    const auto status = osrm->Nearest(params, result);

    if (status != osrm::Status::Ok) {
        const auto code = result.values["code"].get<osrm::json::String>().value;
        const auto message = result.values["message"].get<osrm::json::String>().value;

        throw Exception(rb_eRuntimeError, "Failed to route with given input. error code: %s, message: %s", code.c_str(), message.c_str());
    }

    return parse_nearest_result(result);
}

