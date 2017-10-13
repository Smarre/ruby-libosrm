#ifndef OSRM_TABLE_FUNC
#define OSRM_TABLE_FUNC

#include "globals.hpp"
#include "osrm_action.hpp"

#include <osrm/osrm.hpp>
#include <osrm/json_container.hpp>

using namespace Rice;

Rice::Object wrap_table(Object self, Array coordinates, Hash opts);

class TableFunc : private OSRMAction {

public:
    Rice::Object wrap_table(Object self, Array coordinates, Hash opts);

private:
    std::vector<std::size_t> table_array_conversion(Object o);
    Hash parse_table_result(osrm::json::Object match);

};

#endif