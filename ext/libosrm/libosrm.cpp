
#include "globals.hpp"

using namespace Rice;

#include "ruby_engine_config.hpp"
#include "ruby_osrm_object.hpp"


// TODO: OSRM log may give some hints

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
    try {
        //RUBY_TRY
        //{
        init_engine_config();
        init_osrm_object();
        //}
        //RUBY_CATCH
    } catch(...) {
        std::clog  << "Exception found:" << std::endl;
        std::exception_ptr p = std::current_exception();
        std::clog <<(p ? p.__cxa_exception_type()->name() : "null") << std::endl;
    }
}