
#include "globals.hpp"

using namespace Rice;

#include "ruby_engine_config.hpp"
#include "ruby_osrm_object.hpp"

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