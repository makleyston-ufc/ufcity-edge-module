//
// Created by makleyston on 05/04/23.
//

#include "message.h"
#include <utility>

void ufcity::message::set_topic(std::string _topic) {
    this->topic = std::move(_topic);
}

void ufcity::message::set_message(std::string _message) {
    this->msg = std::move(_message);
}

std::string ufcity::message::get_topic() {
    return this->topic;
}

std::string ufcity::message::get_message() {
    return this->msg;
}

ufcity::message::message(const std::string& _topic, const std::string& _message) {
    this->topic = _topic;
    this->msg = _message;
}
