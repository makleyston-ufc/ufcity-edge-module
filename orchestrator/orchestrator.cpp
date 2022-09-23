//
// Created by makleyston on 13/08/22.
//

#include <regex>
#include "orchestrator.h"
#include "../communcation/communication_interface/communication_interface.h"
#include "../in_memory_storage/resources_map/resources_map.h"
#include "../in_memory_storage/spatial_context_data/spatial_context_data.h"
#include "../communcation/message_sender/message_sender.h"
#include "../communcation/message_receiver/message_receiver.h"
#include "../in_memory_storage/common/fog_node_address.h"

namespace ufcity {

    orchestrator* orchestrator::instance = nullptr;

    int orchestrator::init(const std::string& _data, const std::string& _fog_node_address) {
        if (instance == nullptr){
            /* Check device */
            device * _device = device_from_json(_data);
            if (_device == nullptr) return ERROR_JSON_PARSER;
            print_log("The device '" + _device->get_device_uuid() + "' is OK!");

            /* Check fog node address */
            int _address_error = check_fog_node_address(_fog_node_address);
            if(_address_error != 0) return _address_error;
            print_log("The fog node address '" + _fog_node_address + "' is OK!");

            /* Create an instance */
            instance = new orchestrator(_device, _fog_node_address);
            print_log("Edge Module successfully created!");

            /* Subscribing */
            int _subscribe_error = ufcity::communication_interface::get_instance()->subscribe_receive_command();
            if(_subscribe_error != 0) return _subscribe_error;
            print_log("Edge Module coonected to fog node successfully! Fog node address: " + _fog_node_address);

            return 0;
        }
        print_log("An instance of the Edge Module already exists!");
        return 1; // An instance of the Edge Module already exists
    }

    orchestrator* orchestrator::get_instance(){
        return instance;
    }

    orchestrator::orchestrator(device * device, const std::string& fog_node_address) {
        this->save_device(device);
        this->save_fog_node_address(fog_node_address);
    }

    int orchestrator::save_fog_node_address(const std::string& address) const{
        ufcity_db::fog_node_address::get_instance()->set_fog_node_address(address);
        return 0;
    }

    int orchestrator::check_fog_node_address(const std::string& _address){
        if(_address.empty()) return ERROR_FOG_NODE_ADDRESS_EMPTY;
        if ((_address != "localhost") &&
                (!std::regex_match (_address, std::regex("^([01]?\\d\\d?|2[0-4]\\d|25[0-5])(?:\\.(?:[01]?\\d\\d?|2[0-4]\\d|25[0-5])){3}(?:[0-2]\\d|3[0-2])?$"))))
                return ERROR_FOG_NODE_ADDRESS_NOT_MATCHED;
        return 0;
    }

    int orchestrator::register_resource(const std::string& data) {
        resource * resource_ = resource_from_json(data);
        if(resource_ == nullptr) {
            print_log("JSON parser error!");
            return ERROR_JSON_PARSER;
        }
        print_log("Convert from JSON to Resource successfully! Resource UUID: " + resource_->get_resource_uuid());

        ufcity_db::resources_map * map = ufcity_db::resources_map::get_instance();
        if(map->find_resource_by_uuid(resource_->get_resource_uuid())){
            print_log("The resource " + resource_->get_resource_uuid() + " already exists!");
            return ERROR_RESOURCE_ALREADY_EXIST;
        }else{
            std::string semantic = get_semantic_from_resource(resource_);
            if(semantic.empty()) return ERROR_SEMANTIC_ANNOTATION;
            print_log("Semantic annotation make successfully on " + resource_->get_resource_uuid());
            int r_reg = map->register_resource(resource_->get_resource_uuid(), semantic);
            if(r_reg == 0) print_log("Resource " + resource_->get_resource_uuid() + " has been successfully stored! ");
            return r_reg;
        }
    }

    int orchestrator::remove_resource(const std::string& data) const{
        resource * _resource = resource_from_json(data);
        if(_resource == nullptr) return ERROR_JSON_PARSER;
        print_log("Convert from JSON to Resource successfully! Resource UUID: " + _resource->get_resource_uuid());
        if(ufcity_db::resources_map::get_instance()->remove_resource(_resource->get_resource_uuid()) == 0) {
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

        //Get semantic from resource
        std::string semantic = ufcity_db::resources_map::get_instance()->get_resource_semantic_by_uuid(_resource->get_resource_uuid());
        if(semantic.empty()){
            print_log("The resource " + _resource->get_resource_uuid() + " has not yet been registered!");
            return ERROR_RESOURCE_NOT_FOUND;
        }
        print_log("Resource " + _resource->get_resource_uuid() + " semantics were successfully retrieved.");

        //Pre-processing the already semantically annotated resource
        int r_pre = pre_proc::handler(semantic);
        if (r_pre != 0) {
            //TODO
            return r_pre;
        }

        //Pre-processing the already semantically annotated resource
        int res_p = proc::handler(semantic);
        if (res_p != 0) {
            //TODO
            return res_p;
        }

        int res_s = ufcity_db::spatial_context_data::get_instance()->add_spatial_context_data(semantic);
        if (res_s != 0) return res_s;

        int res_m = data_formatter(semantic);
        if (res_m != 0) return res_m;

        communication_interface::get_instance()->publish_resource_data(semantic);

        return 0;
    }

    int orchestrator::update_location(device * l) const{
        return this->save_device(l);
    }

    int orchestrator::save_device(device * device_) const{
        ufcity_db::spatial_context_data::get_instance()->save_device(device_);
        print_log("Location successfully stored! Location: Lat. " + device_->get_lat() + " and Lng. " + device_->get_lng());
        return 0;
    }

    void orchestrator::print_log(const std::string& log) {
        bool PRINT = true;
        if(PRINT) std::cout << ">> " + log << std::endl;
    }

    std::unordered_map<std::string, std::string> * orchestrator::get_resources_map() const{
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

} // ufcity