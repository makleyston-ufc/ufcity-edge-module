//
// Created by makleyston on 13/08/22.
//

#ifndef UFCITY_ORCHESTRATOR_H
#define UFCITY_ORCHESTRATOR_H

#include <string>
#include <iostream>
#include "../model/location.h"
#include "../parser/parser_json.h"
#include "../spatial_context_data/spatial_context_data.h"
#include "../model/resource.h"
#include "../resources_map/resources_map.h"
#include "../semantic_annotation/semantic_annotation.h"

namespace ufcity {

    class orchestrator{
    private:
        static orchestrator* instance;
        explicit orchestrator(const std::string& location);

    public:
        /* Static access method. */
        static int init(const std::string& location);
        static orchestrator* get_instance();

        /* Interface */
        int register_resource(const std::string& data);
        int remove_resource(const std::string& data) const;
        int send_resource_data(const std::string& data) const;
        int location_update(const std::string& data) const;
//        void command_receiver(ufcity::ufcity_observer ufcityObserver);
        int save_location(const std::string& data) const;
        static void print_log(const std::string& log);
        std::unordered_map<std::string, std::string> * get_resources_map() const;
    };

} // ufcity

#endif //UFCITY_ORCHESTRATOR_H
