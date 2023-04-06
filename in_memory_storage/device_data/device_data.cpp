//
// Created by makleyston on 24/08/22.
//

#include "device_data.h"
#include "../../util/util.h"
#include "../message_queue.h"
#include "../../communication/lib/mqtt_settings.h"

namespace ufcity_db {

    ufcity::device * device_data::get_device(){
        return this->device;
    }

    void device_data::save_device(ufcity::device * _device){
        this->device = _device;
    }

    device_data::device_data() = default;

    device_data* device_data::instance = nullptr;
    device_data* device_data::get_instance(){
        if (instance == nullptr){
            instance = new device_data();
        }
        return instance;
    }

    int device_data::add_spatial_context_data(ufcity::resource *_resource) {
        if(trim(_resource->get_location()->get_lat()).empty())
            _resource->get_location()->set_lat(this->get_device()->get_location()->get_lat());
        if(trim(_resource->get_location()->get_lng()).empty())
            _resource->get_location()->set_lng(this->get_device()->get_location()->get_lng());
        if(trim(_resource->get_location()->get_alt()).empty())
            _resource->get_location()->set_alt(this->get_device()->get_location()->get_alt());

        return 0;
    }

    void device_data::send_to_fog() {
        ufcity_db::message_queue::get_instance()
                ->push_to_queue_messages_to_send(ufcity::mqtt_settings::get_topic_device(), this->device->to_string());
    }

} // ufcity_db