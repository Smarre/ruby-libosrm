
#include "osrm_tile_func.hpp"

#include <osrm/tile_parameters.hpp>

Object wrap_tile(Object self, int x, int y, int zoom) {
    // Convert Ruby object to native type
    osrm::TileParameters params;

    params.x = x;
    params.y = y;
    params.z = zoom;

    // Response is a std::string, instead of JSON stuff that is elsewhere
    std::string result;

    Data_Object<osrm::OSRM> osrm(self);

    // Execute routing request, this does the heavy lifting
    const auto status = osrm->Tile(params, result);

    if (status != osrm::Status::Ok) {
        throw Exception(rb_eRuntimeError, "Failed to get tile data with given input.");
    }

    return to_ruby(result);
}