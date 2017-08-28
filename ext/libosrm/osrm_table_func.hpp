#ifndef OSRM_TABLE_FUNC
#define OSRM_TABLE_FUNC

#include "globals.hpp"

#include <osrm/osrm.hpp>
#include <osrm/json_container.hpp>

using namespace Rice;

std::vector<std::size_t> table_array_conversion(Object o);

Rice::Object wrap_table(Object self, Array coordinates, Hash opts);

#endif
