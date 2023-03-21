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
        explicit orchestrator(device * device);
        ~orchestrator();

    public:
        /* Static access method. */
        static int init(const std::string& _data);
        static orchestrator* get_instance();
        static void destroy();

        /* Interface */
        int register_resource(const std::string& data);
        int remove_resource(const std::string& data) const;
        int send_resource_data(const std::string& data) const;
        int update_location(device * l) const;
        int save_device(device * _device) const;
        int save_fog_node_address(const std::string& address) const;
        static void print_log(const std::string& log);
        std::unordered_map<std::string, const ufcity::resource *> * get_resources_map() const;
        int connect_to_fog(const std::string& fog_node_address) const;

        int register_observer(ufcity::observer *observer) const;
        int remove_observer(ufcity::observer *observer) const;

        static int check_fog_node_address(const std::string& _address);
    };

} // ufcity

#endif //UFCITY_ORCHESTRATOR_H
