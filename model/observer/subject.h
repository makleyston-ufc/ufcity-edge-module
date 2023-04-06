//
// Created by makleyston on 29/08/22.
//

#ifndef UFCITY_SUBJECT_H
#define UFCITY_SUBJECT_H

#include "observer.h"

class subject {

public:

    /**
     * Register an observer
     * @param observer the observer object to be registered
     */
    virtual void register_observer(ufcity::observer *observer) = 0;

    /**
     * Unregister an observer
     * @param observer the observer object to be unregistered
     */
    virtual void remove_observer(ufcity::observer *observer) = 0;

    /**
     * Notify all the registered observers when a change happens
     */
    virtual void notify_observers(std::string topic, std::string message) = 0;

    virtual void receive_message(std::string topic, std::string message) = 0;

};


#endif //UFCITY_SUBJECT_H
