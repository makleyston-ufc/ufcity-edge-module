//
// Created by makleyston on 13/08/22.
//

#include <regex>
#include "orchestrator.h"
#include "../communcation/communication_interface/communication_interface.h"
#include "../in_memory_storage/resources_map/resources_map.h"
#include "../communcation/message_sender/message_sender.h"
#include "../communcation/message_receiver/message_receiver.h"
#include "../in_memory_storage/common/fog_node_address.h"
#include "../in_memory_storage/device_data/device_data.h"

namespace ufcity {

    orchestrator* orchestrator::instance = nullptr;

    int orchestrator::init(const std::string& _data) {
        if (instance == nullptr){
            /* Check device */
            device * _device = device_from_json(_data);
            if (_device == nullptr) return ERROR_JSON_PARSER;
            print_log("The device '" + _device->get_device_uuid() + "' is OK!");

            /* Create an instance */
            instance = new orchestrator(_device);
            print_log("Edge Module successfully created!");

            return 0;
        }
        print_log("An instance of the Edge Module already exists!");
        return 1; // An instance of the Edge Module already exists
    }

    orchestrator* orchestrator::get_instance(){
        return instance;
    }

    orchestrator::orchestrator(device * device) {
        this->save_device(device);
    }

    int orchestrator::save_fog_node_address(const std::string& address) const{
        std::string _full_address = "tcp://" + address + ":1883";
        ufcity_db::fog_node_address::get_instance()->set_fog_node_address(_full_address);
        return 0;
    }

    int orchestrator::check_fog_node_address(const std::string& _address){
        if(_address.empty()) return ERROR_FOG_NODE_ADDRESS_EMPTY;
        if ((_address != "localhost") &&
                (!std::regex_match (_address, std::regex(R"(^([01]?\d\d?|2[0-4]\d|25[0-5])(?:\.(?:[01]?\d\d?|2[0-4]\d|25[0-5])){3}(?:[0-2]\d|3[0-2])?$)"))))
//                (!std::regex_match (_address, std::regex("^([01]?\\d\\d?|2[0-4]\\d|25[0-5])(?:\\.(?:[01]?\\d\\d?|2[0-4]\\d|25[0-5])){3}(?:[0-2]\\d|3[0-2])?$"))))
                return ERROR_FOG_NODE_ADDRESS_NOT_MATCHED;
        return 0;
    }

    int orchestrator::register_resource(const std::string& data) {
        resource * _resource = resource_from_json(data);
        if(_resource == nullptr) {
            print_log("JSON parser error!");
            return ERROR_JSON_PARSER;
        }

        print_log("Convert from JSON to Resource successfully! Resource UUID: " + _resource->get_resource_uuid() + ".");
        ufcity_db::resources_map * map = ufcity_db::resources_map::get_instance();

        if(map->find_resource_uuid(_resource->get_resource_uuid())){
            print_log("The resource " + _resource->get_resource_uuid() + " already exists!");
            return ERROR_RESOURCE_ALREADY_EXIST;
        }else{
            int r_reg = map->register_resource(_resource);
            if(r_reg == 0) print_log("Resource " + _resource->get_resource_uuid() + " has been successfully stored! ");
            return r_reg;
        }
    }

    int orchestrator::remove_resource(const std::string& data) const{
        resource * _resource = resource_from_json(data);
        if(_resource == nullptr) return ERROR_JSON_PARSER;
        print_log("Convert from JSON to Resource successfully! Resource UUID: " + _resource->get_resource_uuid());
        if(ufcity_db::resources_map::get_instance()->remove_by_uuid(_resource->get_resource_uuid()) == 0) {
            print_log("Resource " + _resource->get_resource_uuid() + " successfully removed!");
            return 0;
        }else {
            print_log("Resource " + _resource->get_resource_uuid() + " not found!");
            return ERROR_RESOURCE_NOT_FOUND;
        }
    }

    int orchestrator::send_resource_data(const std::string& data) const{
        //Convert JSON to Resource
        resource * _resource = resource_from_json(data);
        if(_resource == nullptr) return ERROR_JSON_PARSER;
        print_log("Convert from JSON to Resource successfully! Resource UUID: " + _resource->get_resource_uuid());

        //Pre-processing the already semantically annotated resource
        int r_pre = pre_proc::handler(_resource);
        if (r_pre != 0) {
            //TODO
            return r_pre;
        }

        //Pre-processing the already semantically annotated resource
        int res_p = proc::handler(_resource);
        if (res_p != 0) {
            //TODO
            return res_p;
        }

        int res_s = ufcity_db::device_data::get_instance()->add_spatial_context_data(_resource);
        if (res_s != 0) return res_s;

        ufcity::message_sender::get_instance()->send_resource_data(_resource);
        return 0;
    }

    int orchestrator::update_location(device * _device) const{
        return this->save_device(_device);
    }

    int orchestrator::save_device(device * _device) const{
        ufcity_db::device_data::get_instance()->save_device(_device);
        print_log("Location successfully stored! Location: Lat. " + _device->get_location()->get_lat() + " and Lng. " + _device->get_location()->get_lng());
        return 0;
    }

    void orchestrator::print_log(const std::string& log) {
        bool PRINT = true;
        if(PRINT) std::cout << ">> " + log << std::endl;
    }

    std::unordered_map<std::string, const ufcity::resource *> * orchestrator::get_resources_map() const{
        return ufcity_db::resources_map::get_instance()->get_resources_map();
    }

    int orchestrator::register_observer(ufcity::observer *observer) const {
       message_receiver::get_instance()->register_observer(observer);
       print_log("Observer client successfully registered!");
       return 0;
    }

    int orchestrator::remove_observer(ufcity::observer *observer) const {
        int m_res = message_receiver::get_instance()->remove_observer(observer);
        if(m_res == 0) print_log("Observer client successfully removal!");
        return m_res;
    }

    orchestrator::~orchestrator() {
        this->save_device(nullptr);
        this->save_fog_node_address("");
    }

    void orchestrator::destroy() {
        delete orchestrator::instance;
    }

    int orchestrator::connect_to_fog(const std::string& _fog_node_address) const {
        /* Check fog node address */
        int _address_error = check_fog_node_address(_fog_node_address);
        if(_address_error != 0) return _address_error;
        this->save_fog_node_address(_fog_node_address);
        print_log("The fog node address '" + _fog_node_address + "' is OK and is stored!");

        /* Subscribing */
        print_log("Edge Module connecting and subscribing to fog node! Fog node address: " + _fog_node_address + ".");
        int _subscribe_error = ufcity::communication_interface::get_instance()->subscribe_receive_command();
        if(_subscribe_error != 0) return _subscribe_error;

        return 0;
    }


} // ufcity