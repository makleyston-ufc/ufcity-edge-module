//
// Created by makleyston on 26/08/22.
//

#include "message_sender.h"
#include "../lib/mqtt_settings.h"
#include "../../in_memory_storage/message_queue.h"
#include "../communication_interface/mqtt_publish.h"
#include "../../orchestrator/orchestrator.h"

namespace ufcity {

    void message_sender::running_thread_publish() {
        while(ufcity_db::message_queue::get_instance()->get_run_state()){ /* While alive */
            auto item = ufcity_db::message_queue::get_instance()->pull_queue_messages_to_send();
            if(item != nullptr){
                auto _address = ufcity::mqtt_settings::get_fog_node_address();
                auto _pub_client_id = ufcity::mqtt_settings::get_pub_client_id()+"-"+std::to_string(rand());
                /* Publishing data */
                auto _error = ufcity_mqtt::mqtt_publish::publish(_address, _pub_client_id, item->get_message(), item->get_topic());
                std::cout << "\tMessage sent to Fog Computing. \n\t\tTopic:  "+item->get_topic()+", \n\t\tMessage: "+item->get_message() << std::endl;
                if (_error != 0)
                    std::cout << "Error: " + std::to_string(_error) << std::endl;
            }

            /* In order not to fill 100% of the CPU */
            std::this_thread::sleep_for(std::chrono::microseconds (500));
        }
        std::cout << "Finishing the Publishing." << std::endl;
    }

} // ufcity