//
// Created by makleyston on 24/08/22.
//

#include "parser_json.h"

using json = nlohmann::json;

namespace ufcity {

    device * device_from_json(const std::string& data) {
        try {
            auto j = json::parse(data);
            auto *pDevice = new device();
            pDevice->set_uuid_device(j.at("uuid_device"));
            auto * _location = new ufcity::location();
            _location->set_lat(j.at("location").at("lat"));
            _location->set_lng(j.at("location").at("lng"));
            _location->set_alt(j.at("location").at("alt"));
            pDevice->set_location(_location);
            return pDevice;
        } catch (int error){
            return nullptr;
        }
    }

    resource * resource_from_json(const std::string& data_json){
        auto j = json::parse(data_json);
        auto *uuid_services_map = new std::unordered_map<std::string, std::unordered_map<std::string, std::string>>(); //service_uuid <-> values
        for(auto service : j.at("services")){
            auto *values = new std::unordered_map<std::string, std::string>(); //data_tag <-> value
            for(auto data : service.at("data")){
                values->insert(std::pair<std::string, std::string>(data.at("tag"), data.at("value")));
            }
            uuid_services_map->insert(
                    std::pair<std::string, std::unordered_map<std::string, std::string>>(service.at("uuid_service"), *values));
        }
        auto *_resource = new resource(j.at("uuid_resource"), uuid_services_map);
        return _resource;
    }

    std::string resource_to_json(ufcity::resource * _resource){

        json _jResource;
        _jResource["uuid_resource"] = _resource->get_uuid_resource();
        _jResource["location"]["lat"] = _resource->get_location()->get_lat();
        _jResource["location"]["lng"] = _resource->get_location()->get_lng();
        json _jServices = json::array();

//        <service_uuid, <data_tag, value>>
        for(const auto& _service : *_resource->get_services()){
            json _jService;
            _jService["uuid_service"] = _service.first;
            json _jData = json::array();
            for(const auto& _data : _service.second){
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

    std::string device_to_json(ufcity::device * _device){
        json _jDevice;
        _jDevice["uuid_device"] = _device->get_uuid_device();
        _jDevice["location"]["lat"] = _device->get_location()->get_lat();
        _jDevice["location"]["lng"] = _device->get_location()->get_lng();
        return _jDevice.dump();
    }

} // ufcity
