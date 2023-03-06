//
// Created by makleyston on 26/08/22.
//

#include "message_sender.h"
//#include "../communication_interface/mqtt_publish.h"
#include "../../in_memory_storage/resources_map/resources_map.h"
//#include "../../in_memory_storage/spatial_context_data/spatial_context_data.h"
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

    int message_sender::send_resource_registration_data(const resource &_resource) {
        device * _device = ufcity_db::device_data::get_instance()->get_device();
        std::string _semantic = ufcity_db::resources_map::get_instance()->get_semantic_by_uuid(_resource.get_resource_uuid());
        std::string _topic = ufcity::get_topic_publish_data(_device, _resource);
        std::cout << _semantic << " - " << _topic << "  -  " << _resource.get_device_uuid() << " - " << _device->get_device_uuid();
        return ufcity_mqtt::publish(_topic, _semantic);
    }

    int message_sender::send_resource_data(const std::string &semantic) {
        //TODO
        return 0;
    }

    int message_sender::data_formatter(const std::string &semantic) {
        //TODO
        return 0;
    }
} // ufcity