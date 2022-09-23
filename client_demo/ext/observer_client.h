//
// Created by makleyston on 21/09/22.
//

#ifndef UFCITY_OBSERVER_CLIENT_H
#define UFCITY_OBSERVER_CLIENT_H

#include "../../ufcity_interface.h"
#include "../../observer/observer.h"

class observer_client : public ufcity::observer{
private:
    int id;
public:
    explicit observer_client(int id);
    void update(std::string msg) override;
};

void observer_client::update(std::string msg) {
    // print the changed values
    std::cout << "---Client (" << id << ") " << std::endl;
    std::cout << "Message: " + msg << std::endl;
    std::cout << "**********" << std::endl;
}

observer_client::observer_client(int id) {
    this->id = id;
}

#endif //UFCITY_OBSERVER_CLIENT_H
