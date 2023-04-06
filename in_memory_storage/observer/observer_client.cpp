//
// Created by makleyston on 06/04/23.
//

#include <sstream>
#include "observer_client.h"
#include "../../communication/lib/mqtt_settings.h"
#include "../resources_map/resources_map.h"

namespace ufcity_db {

    observer_client::observer_client() = default;
    observer_client *observer_client::instance = nullptr;
    observer_client *observer_client::get_instance() {
        if (instance == nullptr) {
            instance = new observer_client();
        }
        return instance;
    }

    void observer_client::register_observer(ufcity::observer *observer) {
        this->observer_clients.push_back(observer);
    }

    void observer_client::remove_observer(ufcity::observer *observer) {
        remove_observer(observer->get_id_client());
    }

    void observer_client::remove_observer(int id_client) {
        for (int i = 0; i < this->observer_clients.size(); i++) {
            if (this->observer_clients[i]->get_id_client() == id_client) {
                this->observer_clients.erase(this->observer_clients.begin() + i);
                return;
            }
        }
    }

    void observer_client::notify_observers(std::string topic, std::string message) {
        for (auto o : this->observer_clients) { // notify all observers
            o->update(topic, message);
        }
    }

    void observer_client::receive_message(std::string topic, std::string message) {
        std::vector<std::string> topics;
        std::istringstream f(topic);
        std::string s;
        while (getline(f, s, '/')) {
            topics.push_back(s);
        }
        if (topics[0] == ufcity::mqtt_settings::COMMANDS_RECEIVED) {
            this->notify_observers(topic, message);
        }else if(topics[0] == ufcity::mqtt_settings::RESEND){ /* Resend data to fog */
            if(topics.size() == 2){ /* 2 topics means resend device: resend/[uuid_device] */
                /* Sending device data to fog computing */
                ufcity_db::device_data::get_instance()->send_to_fog();
            } else { /* 3 topics means resend resource: resend/[uuid_device]/[uuid_resource] */
                /* Sending resource data to fog computing */
                ufcity_db::resources_map::get_instance()->send_register_to_fog(message);
            }
        }
    }

}