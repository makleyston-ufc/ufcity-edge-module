//
// Created by makleyston on 07/07/22.
//

#include "ufcity_interface.h"

using namespace ufcity;

int ufcity_interface::init(const std::string& location, const std::string& fog_node_address){
    ufcity::orchestrator::print_log("Task: Initializing the Edge Module.");
    return orchestrator::init(location, fog_node_address);
}

int ufcity_interface::register_resource(const std::string& data) {
    ufcity::orchestrator::print_log("Task: Registering a resource.");
    orchestrator * pOrchestrator = orchestrator::get_instance();
    if(pOrchestrator == nullptr)
    {
        ufcity::orchestrator::print_log("Must initialize Edge Module before registering resources.");
        return ERROR_EDGE_MODULE_NOT_INITIALIZED;
    }
    return pOrchestrator->register_resource(data);
}

int ufcity_interface::remove_resource(const std::string& data) {
    ufcity::orchestrator::print_log("Task: Removing a resource.");
    return orchestrator::get_instance()->remove_resource(data);
}

int ufcity_interface::send_resource_data(const std::string& data) {
    ufcity::orchestrator::print_log("Task: Sending resource data.");
    return orchestrator::get_instance()->send_resource_data(data);
}

int ufcity_interface::update_location(const std::string& data) {
    ufcity::orchestrator::print_log("Task: Updating the location.");
    location * l = location_from_json(data);
    if(l  == nullptr) return ERROR_JSON_PARSER;
    orchestrator::print_log("Convert from JSON to Location successfully!");
    return orchestrator::get_instance()->update_location(l);
}

int ufcity_interface::register_observer(ufcity::observer * observer) {
    ufcity::orchestrator::print_log("Task: Registering an observer to receive commands from Fog Computing.");
    return orchestrator::get_instance()->register_observer(observer);
}

std::unordered_map<std::string, std::string> * ufcity_interface::get_resources_map(){
    ufcity::orchestrator::print_log("Task: Removing an observer client.");
    orchestrator * pOrchestrator = orchestrator::get_instance();
    return pOrchestrator->get_resources_map();
}

int ufcity_interface::remove_observer(ufcity::observer * observer){
    ufcity::orchestrator::print_log("Task: Removing an observer client.");
    return orchestrator::get_instance()->remove_observer(observer);
}
