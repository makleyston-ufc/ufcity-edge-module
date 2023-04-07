//
// Created by makleyston on 25/08/22.
//

#include "resources_map.h"
#include "../message_queue.h"
#include "../../communication/lib/mqtt_settings.h"
#include "../../orchestrator/orchestrator.h"

namespace ufcity_db {

    resources_map::resources_map() {
        this->map_resource = new std::unordered_map<std::string, const ufcity::resource *>();
    }
    resources_map * resources_map::instance = nullptr;
    resources_map * resources_map::get_instance(){
        if (instance == nullptr){
            instance = new resources_map();
        }
        return instance;
    }

    bool resources_map::find_by_uuid_resource(const std::string &uuid) const {
        auto it = this->map_resource->find(uuid);
        if (it != this->map_resource->end()) return true;
        else return false;
    }

    ufcity::resource * resources_map::get_resource_by_uuid(const std::string& uuid){
        auto it = this->map_resource->find(uuid);
        if (it != this->map_resource->end()) {
            auto _resource =  it->second;
            return const_cast<ufcity::resource *>(_resource);
        }
        else return nullptr;
    }

    int resources_map::register_resource(ufcity::resource *_resource) {
        /* Registering locally. */
        this->map_resource->insert(std::pair<std::string, const ufcity::resource *>(_resource->get_uuid_resource(), _resource));
        /* Sending to fog computing. */
        this->send_register_to_fog(_resource);
        return 0; //OK
    }

    int resources_map::remove_by_uuid(const std::string& uuid) const{
        if(this->map_resource->erase(uuid) == 1) {
            ufcity_db::message_queue::get_instance()
                    ->push_to_queue_messages_to_send(ufcity::mqtt_settings::get_topic_removed_resource(), uuid);
            return 0; //OK
        }
        return 1; //Resource not removed!
    }

    std::unordered_map<std::string, const ufcity::resource *> * resources_map::get_resources_map() {
        return this->map_resource;
    }

    void resources_map::send_register_to_fog(ufcity::resource * _resource) {
        ufcity_db::message_queue::get_instance()
                ->push_to_queue_messages_to_send(ufcity::mqtt_settings::get_topic_registered_resource(), _resource->to_string());
    }

    void resources_map::send_register_to_fog(const std::string& uuid_resource) {
        auto _resource = this->get_resource_by_uuid(uuid_resource);
        if(_resource != nullptr)
            ufcity_db::message_queue::get_instance()
                    ->push_to_queue_messages_to_send(ufcity::mqtt_settings::get_topic_registered_resource(), _resource->to_string());
        else
            ufcity::orchestrator::print_log("Resource not found.");
    }

    void resources_map::send_data_to_fog(ufcity::resource *_resource) {
        ufcity_db::message_queue::get_instance()
                ->push_to_queue_messages_to_send(ufcity::mqtt_settings::get_topic_resource_data(_resource), _resource->to_string());
    }

} // ufcity_db