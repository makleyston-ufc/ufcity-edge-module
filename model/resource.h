//
// Created by makleyston on 07/07/22.
//

#ifndef UFCITY_RESOURCE_H
#define UFCITY_RESOURCE_H

#include <string>
#include <vector>

namespace ufcity {

    class resource {
    private:
        std::string device_uuid;
        std::string resource_uuid;
        std::vector<std::string> * service_uuid_list{};

    public:
        explicit resource(std::string device_uuid, std::string resource_uuid, std::vector<std::string> * services_uuid_list){
            this->resource_uuid = std::move(resource_uuid);
            this->device_uuid = std::move(device_uuid);
            this->service_uuid_list = services_uuid_list;
        }

        explicit resource(const std::string& message){
            //TODO convert message in JSON to this model and to set them the params into following construct
            auto * l = new std::vector<std::string>();
            resource("device_uuid", "resource_uuid", l);
        }

        std::string get_device_uuid() const{
            return this->device_uuid;
        }

        std::string get_resource_uuid() const{
            return this->resource_uuid;
        }

        std::vector<std::string> * get_services_uuid(){
            return this->service_uuid_list;
        }

    };

} // ufcity

#endif //UFCITY_RESOURCE_H
