//
// Created by makleyston on 26/08/22.
//

#include "message_sender.h"
#include "../lib/mqtt_settings.h"
#include "../../in_memory_storage/message_queue.h"
#include "../communication_interface/mqtt_publish.h"

namespace ufcity {

    void message_sender::running_thread_publish() {
        while(ufcity_db::message_queue::get_instance()->get_run_state()){ /* While alive */
            auto item = ufcity_db::message_queue::get_instance()->pull_queue_messages_to_send();
            if(item != nullptr){
                auto _address = ufcity::mqtt_settings::get_fog_node_address();
                auto _pub_client_id = ufcity::mqtt_settings::get_pub_client_id()+"-"+std::to_string(rand());
                /* Publishing data */
                auto _error = ufcity_mqtt::mqtt_publish::publish(_address, _pub_client_id, item->get_message(), item->get_topic());
                if (_error != 0)
                    std::cout << "Error: " + std::to_string(_error) << std::endl;
            }
        }
        std::cout << "Finishing the Publishing." << std::endl;
    }

} // ufcity