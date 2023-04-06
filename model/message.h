//
// Created by makleyston on 05/04/23.
//

#ifndef UFCITY_MESSAGE_H
#define UFCITY_MESSAGE_H


#include <string>
namespace ufcity {
    class message {

    private:
        std::string topic;
        std::string msg;

    public:
        message(const std::string& _topic, const std::string& _message);

        void set_topic(std::string _topic);

        void set_message(std::string _message);

        std::string get_topic();

        std::string get_message();

    };

}

#endif //UFCITY_MESSAGE_H
