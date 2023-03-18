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

        std::string data_formatter(ufcity::resource *_resource);
        int send_registred_resource(ufcity::resource * _resource);
        int send_resource_data(const std::string& _data);

    };

} // ufcity

#endif //UFCITY_MESSAGE_SENDER_H
