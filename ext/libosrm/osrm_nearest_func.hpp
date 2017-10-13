#ifndef OSRM_NEAREST_FUNC
#define OSRM_NEAREST_FUNC

#include "globals.hpp"
#include "osrm_action.hpp"

#include <osrm/osrm.hpp>
#include <osrm/json_container.hpp>

using namespace Rice;

Rice::Object wrap_nearest(Rice::Object self, double latitude, double longitude, int amount);

class NearestFunc : private OSRMAction {

public:
    // amount defaults to 1
    Rice::Object wrap_nearest(Rice::Object self, double latitude, double longitude, int amount);

private:
    Hash parse_nearest_result(osrm::json::Object nearest);

};

#endif