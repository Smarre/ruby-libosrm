#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"

using namespace Rice;

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
//#include <storage/storage_config.hpp>
#include "osrm/engine_config.hpp"

extern "C"
void Init_libosrm() {
  Data_Type<osrm::EngineConfig> rb_cEngineConfig =
    define_class<osrm::EngineConfig>("LibOSRM::EngineConfig")
    .define_constructor(Constructor<osrm::EngineConfig>())
    .define_method("valid?", &osrm::EngineConfig::IsValid);
}