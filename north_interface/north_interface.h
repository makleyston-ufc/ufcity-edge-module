//
// Created by makleyston on 29/08/22.
//

#ifndef UFCITY_NORTH_INTERFACE_H
#define UFCITY_NORTH_INTERFACE_H
#include <string>

namespace ufcity {

    class north_interface {
    private:
        std::string fog_node_address;
        north_interface();

    public:
        static north_interface * instance;
        static north_interface * get_instance();

        void set_fog_node_address(std::string fog_node_address);
        std::string get_fog_node_address();
        void publish_resource_data(const std::string& data);
        void publish_resource_registration(const std::string& data);
        void publish_resource_removal(const std::string& data);
        void receive_command();

    };

} // ufcity

#endif //UFCITY_NORTH_INTERFACE_H
