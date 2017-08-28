#ifndef RUBY_OSRM_OBJECT_H_
#define RUBY_OSRM_OBJECT_H_

#include "globals.hpp"

using namespace Rice;

#include <osrm/osrm.hpp>

#include <osrm/engine_config.hpp>

#include <osrm/table_parameters.hpp>
#include <osrm/trip_parameters.hpp>
#include <osrm/json_container.hpp>

Object wrap_distance_by_roads(Object self, Object o);

void init_osrm_object();

#endif