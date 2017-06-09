#ifndef RUBY_ENGINE_CONFIG_HPP_
#define RUBY_ENGINE_CONFIG_HPP_

#include "globals.hpp"
#include "ruby_storage_config.hpp"

using namespace Rice;

#include "osrm/engine_config.hpp"

Data_Type<osrm::EngineConfig> rb_cEngineConfig;
Enum<osrm::EngineConfig::Algorithm> rb_eEngineConfigAlgorithm;

// EngineConfig.storage_config
Object EngineConfig_storage_config_get(Object self) {
    Data_Object<osrm::EngineConfig> c(self, rb_cEngineConfig);
    //return c->storage_config;
    return self;
}

// EngineConfig.storage_config
Object EngineConfig_storage_config_set(Object self, Object value) {
    self.iv_set("@storage_config", value);
    return value;
}

// EngineConfig.max_locations_trip
Object EngineConfig_max_locations_trip_get(Object self) {
    Data_Object<osrm::EngineConfig> c(self, rb_cEngineConfig);
    return c->max_locations_trip;
}

// EngineConfig.max_locations_trip
Object EngineConfig_max_locations_trip_set(Object self, Object value) {
    Data_Object<osrm::EngineConfig> c(self, rb_cEngineConfig);
    c->max_locations_trip = value.value();
    return value;
}

char const * description(osrm::EngineConfig::Algorithm e) {
    switch(e) {
        case osrm::EngineConfig::Algorithm::CH:
            return "Contraction hierarchies";
        case osrm::EngineConfig::Algorithm::CoreCH:
            return "Partial contraction hierarchies";
        case osrm::EngineConfig::Algorithm::MLD:
            return "Multi level Dijkstra";
    }
    return "[invalid]";
}

template<>
osrm::EngineConfig::Algorithm from_ruby<osrm::EngineConfig::Algorithm>(Object x) {
    Data_Object<osrm::EngineConfig::Algorithm> d(x, rb_eEngineConfigAlgorithm);
    return *d;
}

void init_engine_config() {
    rb_cEngineConfig =
            define_class_under<osrm::EngineConfig>(rb_mLibOSRM, "EngineConfig")
                .define_constructor(Constructor<osrm::EngineConfig>())
                .define_method("valid?", &osrm::EngineConfig::IsValid)
                .define_method("storage_config=", &EngineConfig_storage_config_set)
                .define_method("storage_config", &EngineConfig_storage_config_get)
                .define_method("max_locations_trip=", &EngineConfig_max_locations_trip_set)
                .define_method("max_locations_trip", &EngineConfig_max_locations_trip_get)
            ;

    rb_eEngineConfigAlgorithm =
      define_enum<osrm::EngineConfig::Algorithm>("Algorithm", rb_cEngineConfig)
      .define_value("CH", osrm::EngineConfig::Algorithm::CH)
      .define_value("CoreCH", osrm::EngineConfig::Algorithm::CoreCH)
      .define_value("MLD", osrm::EngineConfig::Algorithm::MLD);

    rb_eEngineConfigAlgorithm.define_method("description", description);

    init_storage_config();
}

#endif
