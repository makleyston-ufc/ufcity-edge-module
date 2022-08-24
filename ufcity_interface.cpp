//
// Created by makleyston on 07/07/22.
//

#include "ufcity_interface.h"
#include "orchestrator/orchestrator.h"

using namespace ufcity;

int ufcity_interface::init(std::string location){
    return orchestrator::init(location);
}

int ufcity_interface::register_resource(std::string data) {
    orchestrator * orch = orchestrator::get_instance();
    return orch->register_resource(data);
}

int ufcity_interface::remove_resource(std::string data) {
    orchestrator * orch = orchestrator::get_instance();
    return orch->remove_resource(data);
}

int ufcity_interface::send_resource_data(std::string data) {
    orchestrator * orch = orchestrator::get_instance();
    return orch->send_resource_data(data);
}

int ufcity_interface::location_updater(std::string data) {
    orchestrator * orch = orchestrator::get_instance();
    return orch->location_updater(data);
}

void ufcity_interface::command_receiver(ufcity::ufcity_observer ufcityObserver) {
//    ufcity_middleware * middleware = ufcity_middleware::get_instance();
    //TODO
}