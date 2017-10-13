
#include "osrm_action.hpp"

Array OSRMAction::parse_waypoints(osrm::json::Array waypoints) {
    Array waypoints_result;
    for(auto const& waypointValue : waypoints.values) {
        auto waypoint = waypointValue.get<osrm::json::Object>();
        Hash waypoint_result;
        for(std::pair<std::string, osrm::util::json::Value> e : waypoint.values) {
            if(e.first == "name") {
                waypoint_result[String("name")] = e.second.get<osrm::json::String>().value;
            } else if(e.first == "location") {
                Hash location;
                auto const& values = e.second.get<osrm::json::Array>().values;
                location[Symbol("latitude")] = values[1].get<osrm::json::Number>().value;
                location[Symbol("longitude")] = values[0].get<osrm::json::Number>().value;
                waypoint_result[String("location")] = location;
            } else if(e.first == "hint") {
                waypoint_result[String("hint")] = e.second.get<osrm::json::String>().value;
            } else if(e.first == "distance") {
                waypoint_result[String("distance")] = e.second.get<osrm::json::Number>().value;
            } else if(e.first == "waypoint_index") { // Present in trip action
                waypoint_result[String("waypoint_index")] = e.second.get<osrm::json::Number>().value;
            } else if(e.first == "trips_index") { // Present in trip action
                waypoint_result[String("trips_index")] = e.second.get<osrm::json::Number>().value;
            } else {
                throw Exception(rb_eRuntimeError, "Invalid JSON value when building waypoints from libosrm.so: %s", e.first.c_str());
            }
        }

        waypoints_result.push(waypoint_result);
    }

    return waypoints_result;
}

Hash OSRMAction::parse_route(osrm::json::Object route) {
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

    return route_result;
}

Hash OSRMAction::parse_route_leg_annotations(osrm::util::json::Value value) {
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

Array OSRMAction::parse_route_leg_steps(osrm::util::json::Value value) {
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

Array OSRMAction::parse_route_legs(osrm::util::json::Value value) {
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