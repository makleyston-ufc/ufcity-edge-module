//
// Created by makleyston on 07/07/22.
//

#include <iostream>
#include "../ufcity_interface.h"
#include "json_data_sample.hpp"

using namespace ufcity_interface;

class observer_client : public ufcity::observer{
private:
    int id;
public:
    explicit observer_client(int id);
    void update(std::string msg) override;
};

void observer_client::update(std::string msg) {
    // print the changed values
    std::cout << "---Client (" << id << ") " << std::endl;
    std::cout << "Message: " + msg << std::endl;
    std::cout << "**********" << std::endl;
}

observer_client::observer_client(int id) {
    this->id = id;
}

int main(){

    /* Initializing the Edge Module */
    init(samples::json_spatial_context_data, "fog_node_address");

    /* Registering a resource */
    register_resource(samples::json_resource);

    /* Printing all stored resources */
    std::unordered_map<std::string, std::string> * map = get_resources_map();
    for (auto const &pair: *map) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }

    /* Removing a resource */
    remove_resource(samples::json_resource);

    /* Updating the location in Edge Module */
    update_location(samples::json_spatial_context_data);

    /* Sending data of sensors */
    send_resource_data(samples::json_resource_data);

    /* Testing the observer client */
    observer_client * observerClient = new observer_client(123);
    register_observer(observerClient);
    ufcity::message_receiver::get_instance()->receive_message("OOOiiii Testando");

    /* Removing an observer client */
    remove_observer(observerClient);

    return 0;
}