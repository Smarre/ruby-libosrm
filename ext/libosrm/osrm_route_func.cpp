
#include "osrm_route_func.hpp"

#include <osrm/route_parameters.hpp>

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

Hash parse_route_leg_annotations(osrm::util::json::Value value) {
    auto annotations = value.get<osrm::json::Object>();
    Hash result;
    for(std::pair<std::string, osrm::util::json::Value> e : annotations.values) {
        if(e.first == "distance") {
            Array values;
            for(auto const &value : e.second.get<osrm::json::Array>().values) {
                values.push(to_ruby(value));
            }
            result[String("distance")] = values;
        } else if(e.first == "duration") {
            Array values;
            for(auto const &value : e.second.get<osrm::json::Array>().values) {
                values.push(to_ruby(value));
            }
            result[String("duration")] = values;
        } else if(e.first == "datasources") {
            Array values;
            for(auto const &value : e.second.get<osrm::json::Array>().values) {
                values.push(to_ruby(value));
            }
            result[String("datasources")] = values;
        } else if(e.first == "nodes") {
            Array values;
            for(auto const &value : e.second.get<osrm::json::Array>().values) {
                values.push(to_ruby(value));
            }
            result[String("nodes")] = values;
        } else if(e.first == "weight") {
            Array values;
            for(auto const &value : e.second.get<osrm::json::Array>().values) {
                values.push(to_ruby(value));
            }
            result[String("weight")] = values;
        } else if(e.first == "speed") {
            Array values;
            for(auto const &value : e.second.get<osrm::json::Array>().values) {
                values.push(to_ruby(value));
            }
            result[String("speed")] = values;
        } else  {
            throw Exception(rb_eRuntimeError, "Invalid JSON value when building a route leg annotations from libosrm.so: %s", e.first.c_str());
        }
    }

    return result;
}

Array parse_route_leg_steps(osrm::util::json::Value value) {
    Array steps_array;

    auto &stepsValues = value.get<osrm::json::Array>();
    for(auto const& stepValue : stepsValues.values) {
        auto step = stepValue.get<osrm::json::Object>();
        Hash step_result;
        for(std::pair<std::string, osrm::util::json::Value> e : step.values) {
            if(e.first == "distance") {
                step_result[String("distance")] = e.second.get<osrm::json::Number>().value;
            } else if(e.first == "duration") {
                step_result[String("duration")] = e.second.get<osrm::json::Number>().value;
            } else if(e.first == "weight") {
                step_result[String("weight")] = e.second.get<osrm::json::Number>().value;
            } else if(e.first == "geometry") {
                step_result[String("geometry")] = e.second.get<osrm::json::String>().value;
            } else if(e.first == "name") {
                step_result[String("name")] = e.second.get<osrm::json::String>().value;
            } else if(e.first == "ref") {
                step_result[String("ref")] = e.second.get<osrm::json::String>().value;
            } else if(e.first == "pronunciation") {
                step_result[String("pronunciation")] = e.second.get<osrm::json::String>().value;
            } else if(e.first == "destinations") {
                step_result[String("destinations")] = e.second.get<osrm::json::String>().value;
            } else if(e.first == "exits") {
                step_result[String("exits")] = e.second.get<osrm::json::String>().value;
            } else if(e.first == "mode") {
                step_result[String("mode")] = e.second.get<osrm::json::String>().value;
            } else if(e.first == "maneuver") {
                auto values = e.second.get<osrm::json::Object>().values;
                Hash maneuver;
                maneuver[String("modifier")] = values.at("modifier").get<osrm::json::String>().value;
                maneuver[String("type")] = values.at("type").get<osrm::json::String>().value;
                step_result[String("maneuver")] = maneuver;
            } else if(e.first == "intersections") {
                //step_result[String("intersections")] = e.second.get<osrm::json::String>().value; // TODO
            } else if(e.first == "rotary_name") {
                step_result[String("rotary_name")] = e.second.get<osrm::json::String>().value;
            } else if(e.first == "rotary_pronunciation") {
                step_result[String("rotary_pronunciation")] = e.second.get<osrm::json::String>().value;
            } else {
                throw Exception(rb_eRuntimeError, "Invalid JSON value when building a route leg steps from libosrm.so: %s", e.first.c_str());
            }
        }

        steps_array.push(step_result);
    }

    return steps_array;
}

Array parse_route_legs(osrm::util::json::Value value) {
    Array legs_array;

    auto &legsValues = value.get<osrm::json::Array>();
    for(auto const& legValue : legsValues.values) {
        auto leg = legValue.get<osrm::json::Object>();
        Hash leg_result;
        for(std::pair<std::string, osrm::util::json::Value> e : leg.values) {
            if(e.first == "distance") {
                leg_result[String("distance")] = e.second.get<osrm::json::Number>().value;
            } else if(e.first == "duration") {
                leg_result[String("duration")] = e.second.get<osrm::json::Number>().value;
            } else if(e.first == "weight") {
                leg_result[String("weight")] = e.second.get<osrm::json::Number>().value;
            } else if(e.first == "summary") {
                leg_result[String("summary")] = e.second.get<osrm::json::String>().value;
            } else if(e.first == "steps") {
                leg_result[String("steps")] = parse_route_leg_steps(e.second);
            } else if(e.first == "annotation") {
                leg_result[String("annotation")] = parse_route_leg_annotations(e.second);
            } else {
                throw Exception(rb_eRuntimeError, "Invalid JSON value when building a route legs from libosrm.so: %s", e.first.c_str());
            }
        }

        legs_array.push(leg_result);
    }

    return legs_array;
}


Object wrap_route(Object self, Array coordinates, Hash opts) {
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
                route_result[String("geometry")] = e.second.get<osrm::json::String>().value;
            } else if(e.first == "legs") {
                route_result[String("legs")] = parse_route_legs(e.second);
            } else {
                throw Exception(rb_eRuntimeError, "Invalid JSON value when building a route from libosrm.so: %s", e.first.c_str());
            }
        }

        routes_array.push(route_result);
    }
    routes_result[String("routes")] = routes_array;

    return routes_result;
}