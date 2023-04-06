//
// Created by makleyston on 07/07/22.
//

#include "resource.h"
#include "../orchestrator/orchestrator.h"

namespace ufcity {

    resource::resource(std::string resource_uuid, std::unordered_map<std::string, std::unordered_map<std::string, std::string>> * map){
        this->uuid_resource = std::move(resource_uuid);
        this->uuid_services_map = map;
        /* Cria-se um location vazio, pois se ele tiver locationm próprio ele será inserido pelo 'set' e caso não tenha ele será preenchido pelo location do device. */
        auto * _location = new ufcity::location();
        _location->set_alt("");
        _location->set_lat("");
        _location->set_lng("");
        this->location = _location;
    }

    std::string resource::get_uuid_resource() const{
        return this->uuid_resource;
    }

    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> * resource::get_services(){
        return this->uuid_services_map;
    }

    std::unordered_map<std::string, std::string> resource::get_service_by_uuid(const std::string& uuid) {
        auto it = this->uuid_services_map->find(uuid);
        if (it != this->uuid_services_map->end()) {
            auto s = it->second;
            return s;
        }
        orchestrator::print_log("No services found!");
        std::unordered_map<std::string, std::string> _null = *new std::unordered_map<std::string, std::string>();
        return _null;
    }

    void ufcity::resource::set_location(ufcity::location * _location) {
        this->location = _location;
    }

    ufcity::location *resource::get_location() {
        return this->location;
    }

    std::string resource::to_string() {
        auto _json = resource_to_json(this);
        return _json;
    }


} // ufcity