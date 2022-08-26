//
// Created by makleyston on 07/07/22.
//

#ifndef UFCITY_RESOURCE_H
#define UFCITY_RESOURCE_H

#include <string>
#include <unordered_map>

namespace ufcity {

    class resource {
    private:
        std::string device_uuid;
        std::string resource_uuid;
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> * services_uuid_map{}; //<service_uuid, <data_tag, value>>

    public:
        explicit resource(std::string device_uuid, std::string resource_uuid, std::unordered_map<std::string, std::unordered_map<std::string, std::string>> * map);
        explicit resource(const std::string& message);

        std::string get_device_uuid() const;
        std::string get_resource_uuid() const;
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> * get_services();
        std::unordered_map<std::string, std::string> * get_service_by_uuid(const std::string& uuid);
    };

} // ufcity

#endif //UFCITY_RESOURCE_H
