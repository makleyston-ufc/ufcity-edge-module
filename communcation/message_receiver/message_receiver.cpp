//
// Created by makleyston on 29/08/22.
//

#include "message_receiver.h"

namespace ufcity {

    int message_receiver::register_observer(observer *observer) {
        observers->push_back(observer);
        return 0;
    }

    int message_receiver::remove_observer(observer *observer) {
        auto iterator = std::find(observers->begin(), observers->end(), observer);

        if (iterator != observers->end()) { // observer found
            observers->erase(iterator); // remove the observer
            return 0;
        }

        return ERROR_OBSERVER_NOT_FOUND;
    }

    void message_receiver::notify_observers(std::string message) {
        for (observer *observer : *this->observers) { // notify all observers
            observer->update(message);
        }
    }

    void message_receiver::receive_message(std::string message){
        notify_observers(message);
    }

    message_receiver::message_receiver() = default;
    message_receiver * message_receiver::instance = nullptr;
    message_receiver *message_receiver::get_instance() {
        if(instance == nullptr){
            instance = new message_receiver();
            return instance;
        }
        return instance;
    }



} // ufcity