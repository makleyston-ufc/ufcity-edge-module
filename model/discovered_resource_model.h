//
// Created by makleyston on 07/07/22.
//

#ifndef UFCITY_DISCOVERED_RESOURCE_MODEL_H
#define UFCITY_DISCOVERED_RESOURCE_MODEL_H

#include <string>
#include <utility>

namespace msg {

    class discovered_resource_model {

    public:
        explicit discovered_resource_model(std::string device_uuid, std::string resource_uuid){
            this->resource_uuid = std::move(resource_uuid);
            this->device_uuid = std::move(device_uuid);
        }

        explicit discovered_resource_model(const std::string& message){
            //TODO convert message in JSON to this model and to set them the params into following construct

            discovered_resource_model("device_uuid", "resource_uuid");
        }

        std::string get_device_uuid() const{
            return this->device_uuid;
        }

        std::string get_resource_uuid() const{
            return this->resource_uuid;
        }

    private:
        std::string device_uuid;
        std::string resource_uuid;

    };

} // msg

#endif //UFCITY_DISCOVERED_RESOURCE_MODEL_H
