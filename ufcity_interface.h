//
// Created by makleyston on 07/07/22.
//

#ifndef UFCITY_UFCITY_INTERFACE_H
#define UFCITY_UFCITY_INTERFACE_H

#include <string>
#include <unordered_map>
#include "orchestrator/orchestrator.h"
#include "model/observer/observer.h"
#include "model/config/data_grouping_config.h"
#include "model/config/missing_data_config.h"
#include "model/config/remove_outliers_config.h"
#include "model/config/config.h"

namespace ufcity_interface{

    int init(const std::string& _device);

    int finish();

    bool alive();

    int register_resource(const std::string& data);

    int remove_resource(const std::string& data);

    int remove_resource_by_uuid(const std::string& uuid_resource);

    int send_resource_data(const std::string& data);

    int update_location(const std::string& data);

    int register_observer(ufcity::observer * observer);

    int remove_observer(ufcity::observer * observer);

    int remove_observer(int id_observer);

    std::unordered_map<std::string, const ufcity::resource *> * get_resources_map();

    int connect_to_fog(const std::string& _fog_node_address, const std::string& _port = "1883");

    int set_config(ufcity::config *config);

}

#endif //UFCITY_UFCITY_INTERFACE_H
