//
// Created by makleyston on 29/08/22.
//

#ifndef UFCITY_MESSAGE_RECEIVER_H
#define UFCITY_MESSAGE_RECEIVER_H

#include "../../observer/subject.h"
#include <vector>
#include <algorithm>
#include "../../error/error_list.h"

namespace ufcity {

    class message_receiver : public subject{
    private:
        message_receiver();

    public:
        static message_receiver * instance;
        static message_receiver * get_instance();
        std::vector<observer *> *observers = new std::vector<observer *>();

        int register_observer(observer *observer) override;
        int remove_observer(observer *observer) override;
        void notify_observers(std::string message) override;
        void receive_message(std::string message) override;
    };

} // ufcity

#endif //UFCITY_MESSAGE_RECEIVER_H
