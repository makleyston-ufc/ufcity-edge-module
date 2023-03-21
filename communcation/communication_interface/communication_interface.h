//
// Created by makleyston on 29/08/22.
//

#ifndef UFCITY_COMMUNICATION_INTERFACE_H
#define UFCITY_COMMUNICATION_INTERFACE_H
#include <string>

namespace ufcity {

    class communication_interface {
    private:
        communication_interface();

    public:
        static communication_interface * instance;
        static communication_interface * get_instance();

        void publish_resource_data(const std::string& data, const std::string& _topic);
        void publish_registred_resource(const std::string& data, const std::string& _topic);
        void publish_resource_removal(const std::string& _uuid);
        int subscribe_receive_command();

    };

} // ufcity

#endif //UFCITY_COMMUNICATION_INTERFACE_H
