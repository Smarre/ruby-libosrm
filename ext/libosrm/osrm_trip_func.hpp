#ifndef OSRM_TRIP_FUNC
#define OSRM_TRIP_FUNC

#include "globals.hpp"
#include "osrm_action.hpp"

#include <osrm/osrm.hpp>
#include <osrm/json_container.hpp>

using namespace Rice;

Rice::Object wrap_trip(Rice::Object self, Rice::Array coordinates, Rice::Hash opts);

class TripFunc : private OSRMAction {

public:
    Rice::Object wrap_trip(Rice::Object self, Rice::Array coordinates, Rice::Hash opts);
};

#endif