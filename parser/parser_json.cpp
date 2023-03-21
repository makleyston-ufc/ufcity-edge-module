//
// Created by makleyston on 24/08/22.
//

#include "parser_json.h"
#include "../in_memory_storage/device_data/device_data.h"

using json = nlohmann::json;

namespace ufcity {

    device * device_from_json(const std::string& data) {
        try {
            auto j = json::parse(data);
            auto *pDevice = new device();
            pDevice->set_device_uuid(j.at("device_uuid"));
            ufcity::location * _location = new ufcity::location();
            _location->set_lat(j.at("location").at("lat"));
            _location->set_lng(j.at("location").at("lng"));
            pDevice->set_location(_location);
            return pDevice;
        } catch (int error){
            return nullptr;
        }
    }

    resource * resource_from_json(const std::string& data_json){
        auto j = json::parse(data_json);
        auto *services_uuid_map = new std::unordered_map<std::string, std::unordered_map<std::string, std::string>>(); //service_uuid <-> values
        for(auto service : j.at("services")){
            auto *values = new std::unordered_map<std::string, std::string>(); //data_tag <-> value
            for(auto data : service.at("data")){
                values->insert(std::pair<std::string, std::string>(data.at("tag"), data.at("value")));
            }
            services_uuid_map->insert(
                    std::pair<std::string, std::unordered_map<std::string, std::string>>(service.at("service_uuid"), *values));
        }
        auto *_resource = new resource(j.at("resource_uuid"), services_uuid_map);
        return _resource;
    }

    std::string resource_to_json(ufcity::resource * _resouce){

        json _jResource;
        _jResource["resource_uuid"] = _resouce->get_resource_uuid();
        _jResource["location"]["lat"] = _resouce->get_location()->get_lat();
        _jResource["location"]["lng"] = _resouce->get_location()->get_lng();
        json _jServices = json::array();

//        <service_uuid, <data_tag, value>>
        for(auto _service : *_resouce->get_services()){
            json _jService;
            _jService["service_uuid"] = _service.first;
            json _jData = json::array();
            for(auto _data : _service.second){
                json _jDataItem;
                _jDataItem["tag"] = _data.first;
                _jDataItem["value"] = _data.second;
                _jData.push_back(_jDataItem);
            }
            _jService["data"] = _jData;
            _jServices.push_back(_jService);
        }

        _jResource["services"] = _jServices;

        return _jResource.dump();
    }

} // ufcity
