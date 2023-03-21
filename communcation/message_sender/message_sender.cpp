//
// Created by makleyston on 26/08/22.
//

#include "message_sender.h"
#include "../lib/mqtt_settings.h"
#include "../communication_interface/communication_interface.h"
#include "../../error/error_list.h"

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
        std::string _topic  = ufcity::get_topic_to_publish_registred_resource(_device, _resource);
        auto com = ufcity::communication_interface::get_instance();
        com->publish_registred_resource(this->resource_data_formatter(_resource), _topic);
        return 0;
    }

    int message_sender::send_resource_data(ufcity::resource *_resource) {

        std::string _formatted_data = ufcity::message_sender::get_instance()->resource_data_formatter(_resource);
        if (trim(_formatted_data).empty()) return ERROR_FORMATTED_DATA;

        device * _device = ufcity_db::device_data::get_instance()->get_device();
        std::string _topic  = ufcity::get_topic_to_publish_resource_data(_device, _resource);

        communication_interface::get_instance()->publish_resource_data(_formatted_data, _topic);
        return 0;
    }

    std::string message_sender::resource_data_formatter(ufcity::resource *_resource) {
        return _resource->to_string();
    }

    int message_sender::send_resource_removal(const std::string &_uuid) {
        communication_interface::get_instance()->publish_resource_removal(_uuid);
        return 0;
    }
} // ufcity