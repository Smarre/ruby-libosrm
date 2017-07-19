#ifndef RUBY_ENGINE_CONFIG_HPP_
#define RUBY_ENGINE_CONFIG_HPP_

#include "globals.hpp"

#include "ruby_storage_config.hpp"

using namespace Rice;

#include "osrm/engine_config.hpp"

// EngineConfig.storage_config
Object EngineConfig_storage_config_get(Object self);

// EngineConfig.storage_config
Object EngineConfig_storage_config_set(Object self, Object value);

Object EngineConfig_use_shared_memory_get(Object self);

Object EngineConfig_use_shared_memory_set(Object self, Object value);

char const * description(osrm::EngineConfig::Algorithm e);

void init_engine_config();

#endif
