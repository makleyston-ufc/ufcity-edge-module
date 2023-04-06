//
// Created by makleyston on 06/04/23.
//

#ifndef UFCITY_OBSERVER_CLIENT_H
#define UFCITY_OBSERVER_CLIENT_H

#include <string>
#include <vector>
#include "../../model/observer/subject.h"

namespace ufcity_db{
    class observer_client : public subject{
private:
    observer_client();
    std::vector<ufcity::observer *> observer_clients;

public:
    static observer_client * get_instance();
    static observer_client* instance;

    void register_observer(ufcity::observer *observer) override;
    void remove_observer(ufcity::observer *observer) override;
    void remove_observer(int id_client);
    void notify_observers(std::string topic, std::string message) override;
    void receive_message(std::string topic, std::string message) override;

};
}

#endif //UFCITY_OBSERVER_CLIENT_H
