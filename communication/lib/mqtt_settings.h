//
// Created by makleyston on 21/09/22.
//

#include <string>
#include "../../model/device.h"
#include "../../model/resource.h"
#include "../../util/util.h"
#include "../../in_memory_storage/common/fog_node_address.h"
#include "../../in_memory_storage/device_data/device_data.h"


#ifndef UFCITY_TOPIC_H
#define UFCITY_TOPIC_H

namespace ufcity {

    class mqtt_settings{
    private:
        inline static const std::string DFLT_SERVER_ADDRESS{"tcp://localhost:"};
        inline static const std::string DFLT_SERVER_PORT{"1883"};
        inline static const std::string CLIENT_ID_PREFIX{"ufcity_"};
        inline static const int QOS = 0;

        inline static const std::string DATA_PUBLISH = "resource_data";
        inline static const std::string REMOVED_RESOURCE_PUBLISH = "removed_resource";
        inline static const std::string REGISTERED_RESOURCE_PUBLISH = "registered_resource";
        inline static const std::string DEVICE_PUBLISH = "device";
        inline static const std::string SUB = "sub_";
        inline static const std::string PUB = "pub_";

    public:
        inline static const std::string COMMANDS_RECEIVED = "commands_fog_to_edge";
        inline static const std::string RESEND = "resend";

        // std::string _address = "tcp://" + address + ":";
        static std::string get_fog_node_address() {
            std::string _address = ufcity_db::fog_node_address::get_instance()->get_fog_node_address();
            std::string _port = ufcity_db::fog_node_address::get_instance()->get_fog_node_port();
            std::string _full_address = "tcp://"+(_address.empty() ? DFLT_SERVER_ADDRESS : _address)+":"+(_port.empty() ? DFLT_SERVER_PORT : _port);
            return _full_address;
        }

        static std::string get_sub_client_id(){
            std::string _client_id = CLIENT_ID_PREFIX + SUB + ufcity_db::device_data::get_instance()->get_device()->get_uuid_device();
            return  _client_id;
        }

        static std::string get_pub_client_id(){
            std::string _client_id = CLIENT_ID_PREFIX + PUB + ufcity_db::device_data::get_instance()->get_device()->get_uuid_device();
            return  _client_id;
        }

        // device/uuid_device    -> device_json
        static std::string get_topic_device() {
            return DEVICE_PUBLISH + "/" + ufcity_db::device_data::get_instance()->get_device()->get_uuid_device();
        }

        // registered_resource/uuid_device     -> Message is resource data
        static std::string get_topic_registered_resource() {
            return REGISTERED_RESOURCE_PUBLISH + "/" + ufcity_db::device_data::get_instance()->get_device()->get_uuid_device();
        }

        // removed_resource/uuid_device    -> Message is uuid_resource
        static std::string get_topic_removed_resource() {
            return REMOVED_RESOURCE_PUBLISH + "/" + ufcity_db::device_data::get_instance()->get_device()->get_uuid_device();
        }

        // resource_data/uuid_device/uuid_resource     -> Message is resource data
        static std::string get_topic_resource_data(const ufcity::resource * _resource) {
            return DATA_PUBLISH + "/" + ufcity_db::device_data::get_instance()->get_device()->get_uuid_device() + "/" + _resource->get_uuid_resource();
        }

        static std::vector<std::string> get_topics(){
            auto uuid_device = ufcity_db::device_data::get_instance()->get_device()->get_uuid_device();
            std::vector<std::string> _topics;
            _topics.push_back(RESEND+"/"+uuid_device);                  /* resend/[device] */
            _topics.push_back(RESEND+"/"+uuid_device+"/+");             /* resend/[device]/[resource] */
            _topics.push_back(COMMANDS_RECEIVED+"/"+uuid_device+"/+");  /* commands_fog_to_edge/uuid_device/uuid_resource */
            return _topics;
        }

    };

} // ufcity

#endif //UFCITY_TOPIC_H
