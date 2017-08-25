#ifndef OSRM_NEAREST_FUNC
#define OSRM_NEAREST_FUNC

#include "globals.hpp"

#include <osrm/osrm.hpp>
#include <osrm/json_container.hpp>

using namespace Rice;

// amount defaults to 1
Rice::Object wrap_nearest(Rice::Object self, double latitude, double longitude, int amount);

Array parse_waypoints(osrm::json::Array waypoints);

Hash parse_nearest_result(osrm::json::Object nearest);

#endif