
#include "osrm_match_func.hpp"

#include <osrm/match_parameters.hpp>

Hash parse_match_result(osrm::json::Object match) {
    Hash result;
    for(std::pair<std::string, osrm::util::json::Value> e : match.values) {
        if(e.first == "code") {
            result[String("code")] = e.second.get<osrm::json::String>().value;
        } else if(e.first == "tracepoints") {
            // TODO
        } else if(e.first == "matchings") {
            // TODO
        } else {
            throw Exception(rb_eRuntimeError, "Invalid JSON value when building a match from libosrm.so: %s", e.first.c_str());
        }
    }
}

Object wrap_match(Object self, Array coordinates, Hash opts) {
    // Convert Ruby object to native type
    osrm::MatchParameters params;

    Array::iterator it = coordinates.begin();
    Array::iterator end = coordinates.end();
    for(; it != end; ++it) {
        Hash latlon = (Hash)*it;
        double lat = from_ruby<double>(latlon[Symbol("latitude")]);
        double lon = from_ruby<double>(latlon[Symbol("longitude")]);
        params.coordinates.push_back({osrm::util::FloatLongitude{lon}, osrm::util::FloatLatitude{lat}});
    }

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

    // Response is in JSON format
    osrm::json::Object result;

    Data_Object<osrm::OSRM> osrm(self);

    // Execute routing request, this does the heavy lifting
    const auto status = osrm->Match(params, result);

    if (status != osrm::Status::Ok) {
        const auto code = result.values["code"].get<osrm::json::String>().value;
        const auto message = result.values["message"].get<osrm::json::String>().value;

        throw Exception(rb_eRuntimeError, "Failed to route with given input. error code: %s, message: %s", code.c_str(), message.c_str());
    }

    return parse_match_result(result);
}
