
#include "ruby_engine_config.hpp"

Data_Type<osrm::EngineConfig> rb_cEngineConfig;
Enum<osrm::EngineConfig::Algorithm> rb_eEngineConfigAlgorithm;

template<>
osrm::EngineConfig::Algorithm from_ruby<osrm::EngineConfig::Algorithm>(Object x) {
    Data_Object<osrm::EngineConfig::Algorithm> d(x, rb_eEngineConfigAlgorithm);
    return *d;
}

#define EC_ACC_INT(variable) \
    Object EngineConfig_##variable##_get(Object self) { \
        Data_Object<osrm::EngineConfig> c(self, rb_cEngineConfig); \
        return c->variable; \
    }\
    \
    Object EngineConfig_##variable##_set(Object self, Object value) { \
        Data_Object<osrm::EngineConfig> c(self, rb_cEngineConfig); \
        c->variable = value.value(); \
        return value; \
    }

Object EngineConfig_storage_config_get(Object self) {
    Data_Object<osrm::EngineConfig> c(self, rb_cEngineConfig);
    //return c->storage_config;
    return self;
}

Object EngineConfig_storage_config_set(Object self, Object value) {
    Data_Object<osrm::EngineConfig> c(self, rb_cEngineConfig);
    c->storage_config = from_ruby<osrm::storage::StorageConfig>(value.value());
    return value;
}

Object EngineConfig_use_shared_memory_get(Object self) {
    Data_Object<osrm::EngineConfig> c(self, rb_cEngineConfig);
    return c->use_shared_memory;
}

Object EngineConfig_use_shared_memory_set(Object self, Object value) {
    Data_Object<osrm::EngineConfig> c(self, rb_cEngineConfig);
    c->use_shared_memory = value.value();
    return value;
}

EC_ACC_INT(max_locations_trip)
EC_ACC_INT(max_locations_viaroute)
EC_ACC_INT(max_locations_distance_table)
EC_ACC_INT(max_locations_map_matching)
EC_ACC_INT(max_results_nearest)

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

void init_engine_config() {
    rb_cEngineConfig =
            define_class_under<osrm::EngineConfig>(rb_mLibOSRM, "EngineConfig")
                .define_constructor(Constructor<osrm::EngineConfig>())
                .define_method("valid?", &osrm::EngineConfig::IsValid)
                ATTR_ACCESSOR_DECL(EngineConfig, storage_config)
                ATTR_ACCESSOR_DECL(EngineConfig, max_locations_trip)
                ATTR_ACCESSOR_DECL(EngineConfig, max_locations_viaroute)
                ATTR_ACCESSOR_DECL(EngineConfig, max_locations_distance_table)
                ATTR_ACCESSOR_DECL(EngineConfig, max_locations_map_matching)
                ATTR_ACCESSOR_DECL(EngineConfig, max_results_nearest)
                ATTR_ACCESSOR_DECL(EngineConfig, use_shared_memory)
            ;

    rb_eEngineConfigAlgorithm =
      define_enum<osrm::EngineConfig::Algorithm>("Algorithm", rb_cEngineConfig)
      .define_value("CH", osrm::EngineConfig::Algorithm::CH)
      .define_value("CoreCH", osrm::EngineConfig::Algorithm::CoreCH)
      .define_value("MLD", osrm::EngineConfig::Algorithm::MLD);

    rb_eEngineConfigAlgorithm.define_method("description", description);

    init_storage_config();
}