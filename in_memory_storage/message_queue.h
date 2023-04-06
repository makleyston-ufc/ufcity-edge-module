//
// Created by makleyston on 04/04/23.
//

#ifndef UFCITY_MESSAGE_QUEUE_H
#define UFCITY_MESSAGE_QUEUE_H

#include <queue>
#include <mutex>
#include "../model/message.h"

namespace ufcity_db {

    class message_queue {
    private:
        static message_queue* instance;
        message_queue();
        std::queue<ufcity::message *> received_messages;
        std::queue<ufcity::message *> messages_to_send;
        bool running = true;
        std::mutex _mutex_pub_sub;
        std::mutex _mutex_running;
    public:
        static message_queue* get_instance();
        void push_to_queue_received_messages(const std::string &_topic, const std::string &_message);
        void push_to_queue_messages_to_send(const std::string &_topic, const std::string &_message);
        ufcity::message * pull_queue_received_message();
        ufcity::message * pull_queue_messages_to_send();
        void set_run_state(bool state);
        bool get_run_state();
    };

} // ufcity_db

#endif //UFCITY_MESSAGE_QUEUE_H
