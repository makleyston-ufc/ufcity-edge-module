//
// Created by makleyston on 26/08/22.
//

#ifndef UFCITY_MESSAGE_SENDER_H
#define UFCITY_MESSAGE_SENDER_H

#include <string>
#include "../../model/resource.h"

namespace ufcity {

    class message_sender{
    private:
        message_sender();

    public:
        static message_sender * instance;
        static message_sender * get_instance();

        int data_formatter(const std::string& semantic);
        int send_resource_registration_data(const resource& resource);
        int send_resource_data(const std::string& semantic);

    };

} // ufcity

#endif //UFCITY_MESSAGE_SENDER_H
