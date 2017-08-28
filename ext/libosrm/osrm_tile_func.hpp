#ifndef OSRM_TILE_FUNC
#define OSRM_TILE_FUNC

#include "globals.hpp"

#include <osrm/osrm.hpp>
#include <osrm/json_container.hpp>

using namespace Rice;

Rice::Object wrap_tile(Rice::Object self, int x, int y, int zoom);

#endif