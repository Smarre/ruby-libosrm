#ifndef OSRM_ACTION
#define OSRM_ACTION

#include "globals.hpp"

#include <osrm/osrm.hpp>
#include <osrm/json_container.hpp>

/**
 * Abstract class implementing some common methods many OSRM actions requires.
 */
class OSRMAction {

public:
    Array parse_waypoints(osrm::json::Array waypoints);
    Hash parse_route(osrm::json::Object route);

private:
    Array parse_route_legs(osrm::util::json::Value value);
    Array parse_route_leg_steps(osrm::util::json::Value value);
    Hash parse_route_leg_annotations(osrm::util::json::Value value);
};

#endif