
#include "osrm_table_func.hpp"

#include <osrm/table_parameters.hpp>

#include "osrm_nearest_func.hpp"

Object wrap_table(Object self, Array coordinates, Hash opts) {
    TableFunc func;
    return func.wrap_table(self, coordinates, opts);
}

Hash TableFunc::parse_table_result(osrm::json::Object match) {
    Hash result;
    for(std::pair<std::string, osrm::util::json::Value> e : match.values) {
        if(e.first == "code") {
            result[String("code")] = e.second.get<osrm::json::String>().value;
        } else if(e.first == "durations") {
            Array durations_result;
            for(auto const& durationArrayValue : e.second.get<osrm::json::Array>().values) {
                auto durationArray = durationArrayValue.get<osrm::json::Array>();
                Array duration_result;
                for(auto const& durationValue : durationArray.values) {
                    duration_result.push(durationValue.get<osrm::json::Number>().value);
                }
                durations_result.push(duration_result);
            }
            result[String("durations")] = durations_result;
        } else if(e.first == "sources") {
            result[String("sources")] = parse_waypoints(e.second.get<osrm::json::Array>());
        } else if(e.first == "destinations") {
            result[String("destinations")] = parse_waypoints(e.second.get<osrm::json::Array>());
        } else {
            throw Exception(rb_eRuntimeError, "Invalid JSON value when building a table from libosrm.so: %s", e.first.c_str());
        }
    }

    return result;
}

std::vector<std::size_t> TableFunc::table_array_conversion(Object o) {
    std::vector<std::size_t> out;
    if(o.is_a(rb_cArray)) {
        Array a = (Array) o;
        Array::iterator it = a.begin();
        Array::iterator end = a.end();
        for(; it != end; ++it) {
            int index = (int)(Object)*it;
            out.push_back(index);
        }
    } else if(o.is_a(rb_cString)) {
        out.push_back(from_ruby<int>(o));
    } else if(o.is_a(rb_cNumeric)) {
        out.push_back(from_ruby<int>(o));
    }

    return out;
}

Object TableFunc::wrap_table(Object self, Array coordinates, Hash opts) {
    // Convert Ruby object to native type
    osrm::TableParameters params;

    Array::iterator it = coordinates.begin();
    Array::iterator end = coordinates.end();
    for(; it != end; ++it) {
        Hash latlon = (Hash)*it;
        double lat = from_ruby<double>(latlon[Symbol("latitude")]);
        double lon = from_ruby<double>(latlon[Symbol("longitude")]);
        params.coordinates.push_back({osrm::util::FloatLongitude{lon}, osrm::util::FloatLatitude{lat}});
    }

    if(!opts.is_nil()) {
        Object sources = opts[Symbol("sources")];
        if(sources) {
            params.sources = table_array_conversion(sources);
        }

        Object destinations = opts[Symbol("destinations")];
        if(sources) {
            params.destinations = table_array_conversion(destinations);
        }
    }

    // Response is in JSON format
    osrm::json::Object result;

    Data_Object<osrm::OSRM> osrm(self);

    // Execute routing request, this does the heavy lifting
    const auto status = osrm->Table(params, result);

    if (status != osrm::Status::Ok) {
        const auto code = result.values["code"].get<osrm::json::String>().value;
        const auto message = result.values["message"].get<osrm::json::String>().value;

        throw Exception(rb_eRuntimeError, "Failed to route with given input. error code: %s, message: %s", code.c_str(), message.c_str());
    }

    return parse_table_result(result);
}