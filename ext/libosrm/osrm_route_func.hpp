#ifndef OSRM_ROUTE_FUNC
#define OSRM_ROUTE_FUNC

#include "globals.hpp"
#include "osrm_action.hpp"

#include <osrm/osrm.hpp>
#include <osrm/json_container.hpp>

using namespace Rice;

Rice::Object wrap_route(Rice::Object self, Rice::Array coordinates, Rice::Hash opts);

class RouteFunc : private OSRMAction {

public:
    Rice::Object wrap_route(Rice::Object self, Rice::Array coordinates, Rice::Hash opts);
};

#endif
