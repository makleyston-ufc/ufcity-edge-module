//
// Created by makleyston on 07/07/22.
//

#include "ufcity_interface.h"

using namespace ufcity;

int ufcity_interface::init(const std::string& _device){
    ufcity::orchestrator::print_log("Task: Initializing the Edge Module.");
    int _init_error = orchestrator::init(_device);
    if (_init_error != 0){
        ufcity::orchestrator::destroy();
        return _init_error;
    }
    return 0;
}

int check_initialized_instance(orchestrator *pOrchestrator){
    if(pOrchestrator == nullptr)
    {
        ufcity::orchestrator::print_log("Must initialize Edge Module before registering resources. See more in 'init' command.");
        return ERROR_EDGE_MODULE_NOT_INITIALIZED;
    }
    return 0;
}

int ufcity_interface::register_resource(const std::string& data) {
    ufcity::orchestrator::print_log("Task: Registering a resource.");
    int initialized_instance_error = check_initialized_instance(orchestrator::get_instance());
    if(initialized_instance_error != 0) return initialized_instance_error;
    return orchestrator::get_instance()->register_resource(data);
}

int ufcity_interface::remove_resource(const std::string& data) {
    ufcity::orchestrator::print_log("Task: Removing a resource.");
    int initialized_instance_error = check_initialized_instance(orchestrator::get_instance());
    if(initialized_instance_error != 0) return initialized_instance_error;
    return orchestrator::get_instance()->remove_resource(data);
}

int ufcity_interface::send_resource_data(const std::string& data) {
    ufcity::orchestrator::print_log("Task: Sending resource data.");
    int initialized_instance_error = check_initialized_instance(orchestrator::get_instance());
    if(initialized_instance_error != 0) return initialized_instance_error;
    return orchestrator::get_instance()->send_resource_data(data);
}

int ufcity_interface::update_location(const std::string& data) {
    ufcity::orchestrator::print_log("Task: Updating the device.");
    int initialized_instance_error = check_initialized_instance(orchestrator::get_instance());
    if(initialized_instance_error != 0) return initialized_instance_error;
    device * l = device_from_json(data);
    if(l  == nullptr) return ERROR_JSON_PARSER;
    orchestrator::print_log("Convert from JSON to Location successfully!");
    return orchestrator::get_instance()->update_location(l);
}

int ufcity_interface::register_observer(ufcity::observer * observer) {
    ufcity::orchestrator::print_log("Task: Registering an observer to receive commands from Fog Computing.");
    int initialized_instance_error = check_initialized_instance(orchestrator::get_instance());
    if(initialized_instance_error != 0) return initialized_instance_error;
    return orchestrator::get_instance()->register_observer(observer);
}

std::unordered_map<std::string, std::string> * ufcity_interface::get_resources_map(){
    ufcity::orchestrator::print_log("Task: Retrieving all registered resources.");
    int initialized_instance_error = check_initialized_instance(orchestrator::get_instance());
    if(initialized_instance_error != 0){
        ufcity::orchestrator::print_log("There are no registered resources.");
        return nullptr;
    }
    auto map = orchestrator::get_instance()->get_resources_map();
    std::string msg = std::to_string(map->size())+" resource were returned";
    if(map->size() == 1) msg = "1 resource was returned";
    ufcity::orchestrator::print_log(msg);
    return map;
}

int ufcity_interface::remove_observer(ufcity::observer * observer){
    ufcity::orchestrator::print_log("Task: Removing an observer client.");
    int initialized_instance_error = check_initialized_instance(orchestrator::get_instance());
    if(initialized_instance_error != 0) return initialized_instance_error;
    return orchestrator::get_instance()->remove_observer(observer);
}

int ufcity_interface::connect_to_fog(std::string _fog_node_address) {
    ufcity::orchestrator::print_log("Task: Connecting to fog computing. Fog node dddress = " + _fog_node_address);
    int initialized_instance_error = check_initialized_instance(orchestrator::get_instance());
    if(initialized_instance_error != 0) return initialized_instance_error;
    return orchestrator::get_instance()->connect_to_fog(_fog_node_address);
}

int ufcity_interface::finish() {
    //TODO
    return 0;
}
