#ifndef RUBY_STORAGE_CONFIG_H_
#define RUBY_STORAGE_CONFIG_H_

#include "globals.hpp"
#include "rice/String.hpp"

#include "osrm/storage_config.hpp"

using namespace Rice;

/*
template<>
osrm::storage::StorageConfig from_ruby<osrm::storage::StorageConfig>(Object x) {
  // ...
}

template<>
Object to_ruby<osrm::storage::StorageConfig>(osrm::storage::StorageConfig const & x) {

}
*/

void init_storage_config();

#endif