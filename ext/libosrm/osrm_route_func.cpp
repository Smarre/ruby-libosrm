
#include "osrm_route_func.hpp"

#include <osrm/route_parameters.hpp>

Object wrap_route(Object self, Array coordinates, Hash opts) {
    RouteFunc func;
    return func.wrap_route(self, coordinates, opts);
}

template<>
Object to_ruby<osrm::json::Value>(osrm::json::Value const & x) {
    if(x.is<osrm::json::String>()) {
        return String(x.get<osrm::json::String>().value);
    } else if(x.is<osrm::json::Number>()) {
        return to_ruby(x.get<osrm::json::Number>().value);
    } else {
        throw Exception(rb_eRuntimeError, "Failed to convert osrm::json::Value, from libosrm.so");
    }
}

Object RouteFunc::wrap_route(Object self, Array coordinates, Hash opts) {
    // Convert Ruby object to native type
    osrm::RouteParameters params;

    Array::iterator it = coordinates.begin();
    Array::iterator end = coordinates.end();
    for(; it != end; ++it) {
        Hash latlon = (Hash)*it;
        double lat = from_ruby<double>(latlon[Symbol("latitude")]);
        double lon = from_ruby<double>(latlon[Symbol("longitude")]);
        params.coordinates.push_back({osrm::util::FloatLongitude{lon}, osrm::util::FloatLatitude{lat}});
    }

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
        routes_array.push(parse_route(routeValue.get<osrm::json::Object>()));
    }
    routes_result[String("routes")] = routes_array;

    return routes_result;
}