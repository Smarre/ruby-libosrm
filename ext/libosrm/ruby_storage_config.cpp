
#include "ruby_storage_config.hpp"


Data_Type<osrm::storage::StorageConfig> rb_cStorageConfig;

template<>
Object to_ruby<boost::filesystem::path>(boost::filesystem::path const & x) {
    String s(x.c_str());
    return s;
}

template<>
boost::filesystem::path from_ruby<boost::filesystem::path>(Object x) {
    return x.to_s().c_str();
}

#define SC_ACC(variable) \
    Object StorageConfig_##variable##_get(Object self) { \
        Data_Object<osrm::storage::StorageConfig> c(self, rb_cStorageConfig); \
        Object o = to_ruby(c->variable); \
        return o; \
    }\
    \
    Object StorageConfig_##variable##_set(Object self, Object value) { \
        Data_Object<osrm::storage::StorageConfig> c(self, rb_cStorageConfig); \
        c->variable = value.to_s().c_str(); \
        return value; \
    }

SC_ACC(ram_index_path)
SC_ACC(file_index_path)
SC_ACC(hsgr_data_path)
SC_ACC(node_based_nodes_data_path)
SC_ACC(edge_based_nodes_data_path)
SC_ACC(edges_data_path)
SC_ACC(core_data_path)
SC_ACC(geometries_path)
SC_ACC(timestamp_path)
SC_ACC(turn_weight_penalties_path)
SC_ACC(turn_duration_penalties_path)
SC_ACC(datasource_names_path)
SC_ACC(datasource_indexes_path)
SC_ACC(names_data_path)
SC_ACC(properties_path)
SC_ACC(intersection_class_path)
SC_ACC(turn_lane_data_path)
SC_ACC(turn_lane_description_path)
SC_ACC(mld_partition_path)
SC_ACC(mld_storage_path)
SC_ACC(mld_graph_path)

void init_storage_config() {
    rb_cStorageConfig =
            define_class_under<osrm::storage::StorageConfig>(rb_mLibOSRM, "StorageConfig")
                .define_constructor(Constructor<osrm::storage::StorageConfig>())
                .define_constructor(Constructor<osrm::storage::StorageConfig, const boost::filesystem::path>(), Arg("base"))
                .define_method("valid?", &osrm::storage::StorageConfig::IsValid)
                ATTR_ACCESSOR_DECL(StorageConfig, ram_index_path)
                ATTR_ACCESSOR_DECL(StorageConfig, file_index_path)
                ATTR_ACCESSOR_DECL(StorageConfig, hsgr_data_path)
                ATTR_ACCESSOR_DECL(StorageConfig, node_based_nodes_data_path)
                ATTR_ACCESSOR_DECL(StorageConfig, edge_based_nodes_data_path)
                ATTR_ACCESSOR_DECL(StorageConfig, edges_data_path)
                ATTR_ACCESSOR_DECL(StorageConfig, core_data_path)
                ATTR_ACCESSOR_DECL(StorageConfig, geometries_path)
                ATTR_ACCESSOR_DECL(StorageConfig, timestamp_path)
                ATTR_ACCESSOR_DECL(StorageConfig, turn_weight_penalties_path)
                ATTR_ACCESSOR_DECL(StorageConfig, turn_duration_penalties_path)
                ATTR_ACCESSOR_DECL(StorageConfig, datasource_names_path)
                ATTR_ACCESSOR_DECL(StorageConfig, datasource_indexes_path)
                ATTR_ACCESSOR_DECL(StorageConfig, names_data_path)
                ATTR_ACCESSOR_DECL(StorageConfig, properties_path)
                ATTR_ACCESSOR_DECL(StorageConfig, intersection_class_path)
                ATTR_ACCESSOR_DECL(StorageConfig, turn_lane_data_path)
                ATTR_ACCESSOR_DECL(StorageConfig, turn_lane_description_path)
                ATTR_ACCESSOR_DECL(StorageConfig, mld_partition_path)
                ATTR_ACCESSOR_DECL(StorageConfig, mld_storage_path)
                ATTR_ACCESSOR_DECL(StorageConfig, mld_graph_path)
            ;


}