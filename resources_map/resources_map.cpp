//
// Created by makleyston on 25/08/22.
//

#include "resources_map.h"

namespace ufcity_db {

    resources_map::resources_map() {
        this->map = new std::unordered_map<std::string, std::string>();
    }
    resources_map * resources_map::instance = nullptr;
    resources_map * resources_map::get_instance(){
        if (instance == nullptr){
            instance = new resources_map();
        }
        return instance;
    }

    bool resources_map::find_resource_by_uuid(const std::string& uuid) const{
        auto it = this->map->find(uuid);
        if (it != this->map->end()) return true;
        else return false;
    }

    std::string resources_map::get_resource_by_uuid(const std::string& uuid) const{
        auto it = this->map->find(uuid);
        if (it != this->map->end()) return it->second;
        else return nullptr;
    }

    int resources_map::register_resource(const std::string& uuid, const std::string& semantic) const{
        this->map->insert(std::pair<std::string, std::string>(uuid, semantic));
        return 0; //OK
    }

    int resources_map::remove_resource(const std::string& uuid) const{
        if( this->map->erase(uuid) == 1)
            return 0; //OK
        return 1; //Resource not removed!
    }

    std::unordered_map<std::string, std::string> * resources_map::get_resources_map() const{
        return this->map;
    }

} // ufcity_db