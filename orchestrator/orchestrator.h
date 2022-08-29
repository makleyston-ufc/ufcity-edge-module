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
#include "../pre_pocessing/pre_processing.h"
#include "../processing/processing.h"
#include "../north_interface/north_interface.h"
#include "../message_sender/message_sender.h"
#include "../observer/subject.h"
#include "../message_receiver/message_receiver.h"
#include <vector>
#include <algorithm>

namespace ufcity {

    class orchestrator{
    private:
        static orchestrator* instance;
        explicit orchestrator(const std::string& location, const std::string& fog_node_address);

    public:
        /* Static access method. */
        static int init(const std::string& location, const std::string fog_node_address);
        static orchestrator* get_instance();

        /* Interface */
        int register_resource(const std::string& data);
        int remove_resource(const std::string& data) const;
        int send_resource_data(const std::string& data) const;
        int location_update(const std::string& data) const;
//        void register_observer(ufcity::observer ufcityObserver);
        int save_location(const std::string& data) const;
        int save_fog_node_address(const std::string address) const;
        static void print_log(const std::string& log);
        std::unordered_map<std::string, std::string> * get_resources_map() const;

        int register_observer(ufcity::observer *observer) const;
        int remove_observer(ufcity::observer *observer) const;
    };

} // ufcity

#endif //UFCITY_ORCHESTRATOR_H
