//
// Created by makleyston on 24/08/22.
//

#include "parser_json.h"
#include "../util/util.h"

using json = nlohmann::json;

namespace ufcity {

    device * device_from_json(const std::string& data) {
        try {
            auto j = json::parse(data);
            auto *pDevice = new device(); /* No uuid_device = generate uuid_device on constructor */
            if(!trim(j.at("uuid_device")).empty())
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
        std::vector<ufcity::service *> _services;
        if(j.contains("services")) {
            for (auto service: j.at("services")) {
                auto *_service = new ufcity::service(service.at("uuid_service"));
                for (auto data: service.at("data")) {
                    auto *_service_data = new ufcity::service_data(data.at("tag"), data.at("value"));
                    _service->add_service_data(_service_data);
                }
                _services.push_back(_service);
            }
        }
        auto * _resource = new resource(j.at("uuid_resource"));
        _resource->set_services(_services);
        auto * _location = new location();
        if(j.contains("location")){
            auto jLocation = j.at("location");
            if(jLocation.at("lat"))
                _location->set_lat(jLocation.at("lat"));
            if(jLocation.at("lng"))
                _location->set_lng(jLocation.at("lng"));
            if(jLocation.at("alt"))
                _location->set_alt(jLocation.at("alt"));
        }
        _resource->set_location(_location);
        return _resource;
    }

//    resource * resource_from_json(const std::string& data_json){
//        auto j = json::parse(data_json);
//        auto *uuid_services_map = new std::unordered_map<std::string, std::unordered_map<std::string, std::string>>(); //service_uuid <-> values
//        for(auto service : j.at("services")){
//            auto *values = new std::unordered_map<std::string, std::string>(); //data_tag <-> value
//            for(auto data : service.at("data")){
//                values->insert(std::pair<std::string, std::string>(data.at("tag"), data.at("value")));
//            }
//            uuid_services_map->insert(
//                    std::pair<std::string, std::unordered_map<std::string, std::string>>(service.at("uuid_service"), *values));
//        }
//        auto *_resource = new resource(j.at("uuid_resource"), uuid_services_map);
//        return _resource;
//    }

    std::string resource_to_json(ufcity::resource * _resource){
        json _jResource;
        _jResource["uuid_resource"] = _resource->get_uuid_resource();
        _jResource["location"]["lat"] = _resource->get_location()->get_lat();
        _jResource["location"]["lng"] = _resource->get_location()->get_lng();
        _jResource["location"]["alt"] = _resource->get_location()->get_alt();
        json _jServices = json::array();
        for(auto _service : _resource->get_services()){
            json _jService;
            _jService["uuid_service"] = _service->get_uuid_service();
            json _jData = json::array();
            for(auto _data : _service->get_service_data()){
                json _jDataItem;
                _jDataItem["tag"] = _data->get_tag();
                _jDataItem["value"] = _data->get_value();
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
        _jDevice["location"]["alt"] = _device->get_location()->get_alt();
        return _jDevice.dump();
    }

} // ufcity
