//
// Created by makleyston on 23/09/22.
//

#ifndef UFCITY_FOG_NODE_ADDRESS_H
#define UFCITY_FOG_NODE_ADDRESS_H

#include <string>

namespace ufcity_db {

    class fog_node_address {
    private:
        static fog_node_address* instance;
        explicit fog_node_address();
        ~fog_node_address();
        std::string address;
        std::string port;

    public:
        static fog_node_address* get_instance();
        void set_fog_node_address(std::string address);
        void set_fog_node_port(std::string port);
        std::string get_fog_node_address();
        std::string get_fog_node_port();
    };

} // ufcity_db

#endif //UFCITY_FOG_NODE_ADDRESS_H
