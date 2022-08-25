//
// Created by makleyston on 07/07/22.
//

#ifndef UFCITY_UFCITY_INTERFACE_H
#define UFCITY_UFCITY_INTERFACE_H

#include <string>
#include "observer/ufcity_observer.h"
#include "orchestrator/orchestrator.h"

namespace ufcity_interface{

    int init(std::string location);

    int register_resource(std::string data);

    int remove_resource(std::string data);

    int send_resource_data(std::string data);

    int location_updater(std::string data);

    void command_receiver(ufcity::ufcity_observer ufcityObserver);

}

#endif //UFCITY_UFCITY_INTERFACE_H
