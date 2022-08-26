//
// Created by makleyston on 07/07/22.
//

#include "ufcity_interface.h"

using namespace ufcity;

int ufcity_interface::init(const std::string& location){
    ufcity::orchestrator::print_log("Task: Initializing the Edge Module.");
    return orchestrator::init(location);
}

int ufcity_interface::register_resource(const std::string& data) {
    ufcity::orchestrator::print_log("Task: Registering a resource.");
    orchestrator * pOrchestrator = orchestrator::get_instance();
    if(pOrchestrator == nullptr)
    {
        ufcity::orchestrator::print_log("ERROR 3: Must initialize Edge Module before registering resources.");
        return 3;
    }
    return pOrchestrator->register_resource(data);
}

int ufcity_interface::remove_resource(const std::string& data) {
    ufcity::orchestrator::print_log("Task: Removing a resource.");
    orchestrator * pOrchestrator = orchestrator::get_instance();
    return pOrchestrator->remove_resource(data);
}

int ufcity_interface::send_resource_data(const std::string& data) {
    ufcity::orchestrator::print_log("Task: Sending resource data.");
    orchestrator * pOrchestrator = orchestrator::get_instance();
    return pOrchestrator->send_resource_data(data);
}

int ufcity_interface::location_update(const std::string& data) {
    ufcity::orchestrator::print_log("Task: Updating the location.");
    orchestrator * pOrchestrator = orchestrator::get_instance();
    return pOrchestrator->location_update(data);
}

void ufcity_interface::command_receiver(ufcity::ufcity_observer ufcityObserver) {
//    ufcity_middleware * middleware = ufcity_middleware::get_instance();
    //TODO
}

std::unordered_map<std::string, std::string> * ufcity_interface::get_resources_map(){
    orchestrator * pOrchestrator = orchestrator::get_instance();
    return pOrchestrator->get_resources_map();
}
