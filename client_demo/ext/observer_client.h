//
// Created by makleyston on 21/09/22.
//

#ifndef UFCITY_OBSERVER_CLIENT_H
#define UFCITY_OBSERVER_CLIENT_H

#include "../../ufcity_interface.h"
#include "../../in_memory_storage/device_data/device_data.h"
#include "../../model/observer/observer.h"

class observer_client : public ufcity::observer{
private:

public:
    explicit observer_client(int id_client);
    void update(std::string topic, std::string message) override;
};

void observer_client::update(std::string topic, std::string message) {
    std::cout << "---Client (" << this->get_id_client() << ") " << std::endl;
//    std::cout << "Topic: " + topic << std::endl;
    std::cout << "Message: " + message << std::endl;
    std::cout << "**********" << std::endl;
}

observer_client::observer_client(int id_client) {
    this->set_id_client(id_client);
}


#endif //UFCITY_OBSERVER_CLIENT_H
