
#include "globals.hpp"

using namespace Rice;

#include "ruby_engine_config.hpp"

/*
#include <osrm/match_parameters.hpp>
#include <osrm/nearest_parameters.hpp>
#include <osrm/route_parameters.hpp>
#include <osrm/table_parameters.hpp>
#include <osrm/trip_parameters.hpp>

#include <osrm/coordinate.hpp>
#include <osrm/engine_config.hpp>
#include <osrm/json_container.hpp>

#include <osrm/osrm.hpp>
#include <osrm/status.hpp>
*/

//#include <osrm/osrm.hpp>
//#include <storage/storage_config.hpp

extern "C"
void Init_ruby_libosrm() {
    init_engine_config();
}