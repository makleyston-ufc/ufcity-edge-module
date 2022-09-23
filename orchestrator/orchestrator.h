//
// Created by makleyston on 13/08/22.
//

#ifndef UFCITY_ORCHESTRATOR_H
#define UFCITY_ORCHESTRATOR_H

#include <string>
#include <iostream>
#include "../model/device.h"
#include "../parser/parser_json.h"
#include "../model/resource.h"
#include "../semantic_annotation/semantic_annotation.h"
#include "../pre_pocessing/pre_processing.h"
#include "../processing/processing.h"
#include "../observer/subject.h"
#include <vector>
#include <algorithm>
#include "../error/error_list.h"

namespace ufcity {

    class orchestrator{
    private:
        static orchestrator* instance;
        explicit orchestrator(device * device, const std::string& fog_node_address);
        ~orchestrator();

    public:
        /* Static access method. */
        static int init(const std::string& _data, const std::string& _fog_node_address);
        static orchestrator* get_instance();
        static void destroy();

        /* Interface */
        int register_resource(const std::string& data);
        int remove_resource(const std::string& data) const;
        int send_resource_data(const std::string& data) const;
        int update_location(device * l) const;
//        void register_observer(ufcity::observer ufcityObserver);
        int save_device(device * device_) const;
        int save_fog_node_address(const std::string& address) const;
        static void print_log(const std::string& log);
        std::unordered_map<std::string, std::string> * get_resources_map() const;

        int register_observer(ufcity::observer *observer) const;
        int remove_observer(ufcity::observer *observer) const;

        static int check_fog_node_address(const std::string& _address);
    };

} // ufcity

#endif //UFCITY_ORCHESTRATOR_H
