//
// Created by makleyston on 21/09/22.
//

#include <string>
#include "../../model/device.h"
#include "../../model/resource.h"
#include "../../util/util.h"
#include "../../in_memory_storage/spatial_context_data/spatial_context_data.h"


#ifndef UFCITY_TOPIC_H
#define UFCITY_TOPIC_H

namespace ufcity {

    const std::string DFLT_SERVER_ADDRESS{"tcp://localhost:1883"};
    const std::string CLIENT_ID_PREFIX{"ufcity_"};
    const std::string PERSIST_DIR{"./persist"};
    const int QOS = 0;

    const std::string COMMANDS_RECEIVED = "commands_received";
    const std::string DATA_PUBLISH = "data_publish";
    const std::string SUB = "sub_";
    const std::string PUB = "pub_";


    std::string get_fog_node_address() {
        std::string _address = ufcity_db::fog_node_address::get_instance()->get_fog_node_address();
        return (_address.empty() ? DFLT_SERVER_ADDRESS : _address);
    }

    std::string get_sub_client_id(){
        std::string _client_id = CLIENT_ID_PREFIX + SUB + ufcity_db::spatial_context_data::get_instance()->get_device()->get_device_uuid();
        return  _client_id;
    }

    std::string get_pub_client_id(){
        std::string _client_id = CLIENT_ID_PREFIX + PUB + ufcity_db::spatial_context_data::get_instance()->get_device()->get_device_uuid();
        return  _client_id;
    }

// data_publish/uuid_device/type_resource/uuid_resource
    std::string get_topic_publish_data(ufcity::device *device_, ufcity::resource resource_) {
        return trim(DATA_PUBLISH) + "/" + device_->get_device_uuid() + "/" + "semmantic" + "/" +
               resource_.get_resource_uuid();
    }

// commands_received/type_resource/uuid_resource/
    std::string get_topic_receive_commands() {
        return trim(COMMANDS_RECEIVED) + "/+/+";
    }

} // ufcity

#endif //UFCITY_TOPIC_H
