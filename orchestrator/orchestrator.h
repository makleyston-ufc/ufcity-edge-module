//
// Created by makleyston on 13/08/22.
//

#ifndef UFCITY_ORCHESTRATOR_H
#define UFCITY_ORCHESTRATOR_H

#include <string>
#include <iostream>
#include "../model/location_model.h"

namespace ufcity {

    class orchestrator{
    private:
        static orchestrator* instance;
        orchestrator(std::string location);

    public:
        /* Static access method. */
        static int init(std::string location);
        static orchestrator* get_instance();

        /* Interface */
        int register_resource(std::string data);
        int remove_resource(std::string data);
        int send_resource_data(std::string data);
        int location_updater(std::string data);
//        void command_receiver(ufcity::ufcity_observer ufcityObserver);
        int save_location(std::string data);

    };
} // ufcity

#endif //UFCITY_ORCHESTRATOR_H
