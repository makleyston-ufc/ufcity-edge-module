//
// Created by makleyston on 25/08/22.
//

#include "resources_map.h"
#include "../../communcation/message_sender/message_sender.h"

//#include "../../parser/parser_json.h"
//#include "../../client_demo/ext/json_data_sample.hpp"

namespace ufcity_db {

    resources_map::resources_map() {
        this->map_resource = new std::unordered_map<std::string, const ufcity::resource *>();
        this->map_semantic = new std::unordered_map<std::string, const std::string>();
    }
    resources_map * resources_map::instance = nullptr;
    resources_map * resources_map::get_instance(){
        if (instance == nullptr){
            instance = new resources_map();
        }
        return instance;
    }

    bool resources_map::find_resource_uuid(const std::string &uuid) const {
        auto it = this->map_resource->find(uuid);
        if (it != this->map_resource->end()) return true;
        else return false;
    }

    bool resources_map::find_semantic_uuid(const std::string &uuid) const {
        auto it = this->map_semantic->find(uuid);
        if (it != this->map_semantic->end()) return true;
        else return false;
    }

    std::string resources_map::get_semantic_by_uuid(const std::string& uuid) const{
        auto it = this->map_semantic->find(uuid);
        if (it != this->map_semantic->end()) {
            return it->second;
        }
        else return "";
    }

    const ufcity::resource * resources_map::get_resource_by_uuid(const std::string& uuid){
        auto it = this->map_resource->find(uuid);
        if (it != this->map_resource->end()) {
            auto _resource =  it->second;
            return _resource;
        }
        else return nullptr;
    }

    int resources_map::register_resource(const ufcity::resource *_resource, const std::string& _semantic) const{
        this->map_resource->insert(std::pair<std::string, const ufcity::resource *>(_resource->get_resource_uuid(), _resource));
        this->map_semantic->insert(std::pair<std::string, const std::string>(_resource->get_resource_uuid(), _semantic));
        ufcity::message_sender::get_instance()->send_resource_registration_data(*_resource);
        return 0; //OK
    }

    int resources_map::remove_by_uuid(const std::string& uuid) const{
        if(this->map_resource->erase(uuid) == 1 && this->map_semantic->erase(uuid) == 1)
            return 0; //OK
        return 1; //Resource not removed!
    }

    std::unordered_map<std::string, const ufcity::resource *> * resources_map::get_resources_map() {
        return this->map_resource;
    }

    std::unordered_map<std::string, const std::string> * resources_map::get_semantics_map() {
        return this->map_semantic;
    }

} // ufcity_db