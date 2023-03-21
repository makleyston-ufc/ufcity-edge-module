//
// Created by makleyston on 26/08/22.
//

#include "message_sender.h"
#include "../../in_memory_storage/resources_map/resources_map.h"
#include "../lib/mqtt_settings.h"
#include "../communication_interface/mqtt_publish.h"

namespace ufcity {

    message_sender::message_sender() = default;
    message_sender * message_sender::instance = nullptr;
    message_sender *message_sender::get_instance() {
        if(instance == nullptr){
            instance = new message_sender();
            return instance;
        }
        return instance;
    }

    int message_sender::send_registred_resource(ufcity::resource * _resource) {
        device * _device = ufcity_db::device_data::get_instance()->get_device();
//        std::string _semantic = ufcity_db::resources_map::get_instance()->get_semantic_by_uuid(_resource.get_resource_uuid());
        std::string _topic  = ufcity::get_topic_to_publish(_device, _resource);
//        std::cout << _semantic << " - " << _topic << "  -  " << _resource.get_device_uuid() << " - " << _device->get_device_uuid();
//        return ufcity_mqtt::publish(_topic, this->data_formatter(_resource));
        std::string _address = ufcity::get_fog_node_address();
        std::string _pub_client_id = ufcity::get_pub_client_id();
        auto mp = new ufcity_mqtt::mqtt_publish();
        return mp->publish( _address, _pub_client_id, this->data_formatter(_resource), _topic);
    }

    int message_sender::send_resource_data(const std::string& _data) {
        //TODO
        return 0;
    }

    std::string message_sender::data_formatter(ufcity::resource *_resource) {
        //TODO
        return "## formatted data ##" + _resource->get_resource_uuid();
    }
} // ufcity