//
// Created by makleyston on 04/04/23.
//

#include "message_queue.h"
#include <string>
#include <iostream>

namespace ufcity_db {

    message_queue::message_queue() = default;

    message_queue* message_queue::instance = nullptr;
    message_queue* message_queue::get_instance(){
        if (instance == nullptr){
            instance = new message_queue();
        }
        return instance;
    }

    void message_queue::push_to_queue_received_messages(const std::string &_topic, const std::string &_message) {
        std::lock_guard<std::mutex> guard(_mutex_pub_sub);
        auto * msg = new ufcity::message(_topic, _message);
        received_messages.push(msg);
    }

    ufcity::message * message_queue::pull_queue_received_message() {
        std::lock_guard<std::mutex> guard(_mutex_pub_sub);
        if(!received_messages.empty()) {
            auto m = received_messages.front();
            received_messages.pop();
            return m;
        }else{
            return nullptr;
        }
    }

    void message_queue::push_to_queue_messages_to_send(const std::string &_topic, const std::string &_message) {
        std::lock_guard<std::mutex> guard(_mutex_pub_sub);
        auto * msg = new ufcity::message(_topic, _message);
        messages_to_send.push(msg);
    }

    ufcity::message *message_queue::pull_queue_messages_to_send() {
        std::lock_guard<std::mutex> guard(_mutex_pub_sub);
        if(!messages_to_send.empty()) {
            auto m = messages_to_send.front();
            messages_to_send.pop();
            return m;
        }else{
            return nullptr;
        }
    }

    void message_queue::set_run_state(bool state){
        std::lock_guard<std::mutex> guard(_mutex_running);
        this->running = state;
    }

    bool message_queue::get_run_state(){
        std::lock_guard<std::mutex> guard(_mutex_running);
        return this->running;
    }

} // ufcity_db