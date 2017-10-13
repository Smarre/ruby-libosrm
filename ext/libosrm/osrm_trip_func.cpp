
#include "osrm_trip_func.hpp"

#include <osrm/trip_parameters.hpp>

Object wrap_trip(Object self, Array coordinates, Hash opts) {
    TripFunc func;
    return func.wrap_trip(self, coordinates, opts);
}

Object TripFunc::wrap_trip(Object self, Array coordinates, Hash opts) {
    // Convert Ruby object to native type
    osrm::TripParameters params;

    Array::iterator it = coordinates.begin();
    Array::iterator end = coordinates.end();
    for(; it != end; ++it) {
        Hash latlon = (Hash)*it;
        double lat = from_ruby<double>(latlon[Symbol("latitude")]);
        double lon = from_ruby<double>(latlon[Symbol("longitude")]);
        params.coordinates.push_back({osrm::util::FloatLongitude{lon}, osrm::util::FloatLatitude{lat}});
    }

    Object roundtrip = opts[Symbol("roundtrip")];
    if(roundtrip) {
        params.roundtrip = true;
    }

    Object source = opts[Symbol("source")];
    if(!source.is_nil()) {
        Symbol source_symbol = (Symbol) source;
        const char *source_string = source_symbol.c_str();
        if(strcmp(source_string, "any") == 0) {
            params.source = osrm::TripParameters::SourceType::Any;
        } else if(strcmp(source_string, "first") == 0) {
            params.source = osrm::TripParameters::SourceType::First;
        } else {
            throw Exception(rb_eRuntimeError, "libosrm.so#wrap_trip(): failed to recognize given source symbol: %s", source_string);
        }
    }

    Object destination = opts[Symbol("destination")];
    if(!destination.is_nil()) {
        Symbol destination_symbol = (Symbol) destination;
        const char *destination_string = destination_symbol.c_str();
        if(strcmp(destination_string, "any") == 0) {
            params.destination = osrm::TripParameters::DestinationType::Any;
        } else if(strcmp(destination_string, "last") == 0) {
            params.destination = osrm::TripParameters::DestinationType::Last;
        } else {
            throw Exception(rb_eRuntimeError, "libosrm.so#wrap_trip(): failed to recognize given destination symbol: %s", destination_string);
        }
    }

    // TODO: since this option is same as in route thing, maybe we could have some kind of abstraction?
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
    const auto status = osrm->Trip(params, result);

    if (status != osrm::Status::Ok) {
        const auto code = result.values["code"].get<osrm::json::String>().value;
        const auto message = result.values["message"].get<osrm::json::String>().value;

        throw Exception(rb_eRuntimeError, "Failed to calculate a trip with given input. error code: %s, message: %s", code.c_str(), message.c_str());
    }

    Hash trip_result;
    trip_result[String("code")] = result.values["code"].get<osrm::json::String>().value;

    trip_result[String("waypoints")] = parse_waypoints(result.values["waypoints"].get<osrm::json::Array>());

    Array trips_array;
    auto &routeValues = result.values["routes"].get<osrm::json::Array>();
    for(auto const& routeValue : routeValues.values) {
        trips_array.push(parse_route(routeValue.get<osrm::json::Object>()));
    }
    trip_result[String("trips")] = trips_array;

    return trip_result;
}
