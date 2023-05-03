//
// Created by makleyston on 07/07/22.
//

#include "resource.h"
#include "../orchestrator/orchestrator.h"
#include "../util/util.h"

namespace ufcity {


//    resource::resource(std::string resource_uuid, std::unordered_map<std::string, std::unordered_map<std::string, std::string>> * map){
//        this->uuid_resource = std::move(resource_uuid);
//        this->uuid_services_map = map;
//        /* An empty location is created.
//         * Case it has its own location it will be inserted
//         * by 'set_location' and if not has, it will be
//         * filled in by the location of the device.*/
//        auto * _location = new ufcity::location();
//        _location->set_alt("");
//        _location->set_lat("");
//        _location->set_lng("");
//        this->location = _location;
//    }

    std::string resource::get_uuid_resource() const{
        return this->uuid_resource;
    }

//    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> * resource::get_services(){
//        return this->uuid_services_map;
//    }
//
//    std::unordered_map<std::string, std::string> resource::get_service_by_uuid(const std::string& uuid) {
//        auto it = this->uuid_services_map->find(uuid);
//        if (it != this->uuid_services_map->end()) {
//            auto s = it->second;
//            return s;
//        }
//        orchestrator::print_log("No services found!");
//        return *new std::unordered_map<std::string, std::string>();
//    }

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

    resource::resource(std::string _resource_uuid) {
        this->uuid_resource = _resource_uuid;
    }

    void resource::set_services(std::vector<ufcity::service *> _services) {
        this->services = _services;
    }

    void resource::add_service(ufcity::service *_service) {
        this->services.push_back(_service);
    }

    std::vector<service *> resource::get_services() {
        return this->services;
    }

    ufcity::service resource::get_service_by_uuid(const std::string &_uuid_service) {
        for(auto _service : this->services){
            if(_service->get_uuid_service()==_uuid_service)
                return *_service;
        }
        return *new ufcity::service("");
    }


} // ufcity