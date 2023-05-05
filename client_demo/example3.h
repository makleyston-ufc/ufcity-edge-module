//
// Created by makleyston on 18/03/23.
//

#include "../ufcity_interface.h"
#include "ext/observer_client.h"
#include <thread>
#include <fstream>
//#include "menu.h"
#include "../in_memory_storage/message_queue.h"
#include "../model/config/methods.h"
#include "../model/config/config.h"
//#include "ext/json_data_sample.hpp"
#include "ext/example3_json.h"

int get_random_time(long _ms) {
    // Cria um gerador de números aleatórios
    std::random_device rd;
    std::mt19937 gen(rd());
    // Define a distribuição do gerador para o intervalo [0, _ms)
    std::uniform_int_distribution<long> dist(0, _ms-1);
    // Retorna um número aleatório gerado pela distribuição
    return dist(gen);
}

using namespace ufcity_interface;

/* Send data to Fog Computing. */

int example3(int argc, char *argv[]){

    std::this_thread::sleep_for(std::chrono::microseconds (get_random_time(3000)));

    std::string HOST, PORT;
    int i = 1;
    while (i < argc) {
        if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--address") == 0) {
            HOST = argv[i + 1];
        }else if(strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0){
            PORT = argv[i + 1];
        }
        i = i + 2;
    }

    std::string filename = "data.txt";
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Failed to open file " << filename << std::endl;
        return 1;
    }

    /* Initializing the Edge Module */
    init(R"JSON(
    {
      "uuid_device":"",
      "location":{
        "lat":"123",
        "lng":"321",
        "alt":"0"
      }
    }
    )JSON");

    auto * config = new ufcity::config();
    config->get_data_grouping_config()->set_method(methods::FIXED_SIZE_GROUPING);
    config->get_data_grouping_config()->set_size(5);
    config->get_data_aggregation_config()->set_method(methods::MEAN_AGGREGATION_METHOD);
    set_config(config);

    /* Setting observer client */
    auto * observerClient = new observer_client(123);
    register_observer(observerClient);

    /* Connecting to Fog Computing */
    connect_to_fog(HOST, PORT); //IP Example. Change this IP for the fog computing node IP.

    /* Registering a resource */
    register_resource(ex3::get_resource_json("particullate_matter:-1"));
    register_resource(ex3::get_resource_json("sulfure_dioxide:-1)"));
    register_resource(ex3::get_resource_json("ozone:-1"));
    register_resource(ex3::get_resource_json("nitrogen_dioxide:-1"));
    register_resource(ex3::get_resource_json("carbon_monoxide:-1"));

    /* Sending data of sensors
     * Here we are simulating the several sensor data present in environment. */
    while(alive()) {
        time_t end = time(nullptr) + 2; // Pass to 2 second
        while (time(nullptr) < end);
        std::string line;
        if (std::getline(file, line)) {
            send_resource_data(ex3::get_resource_json(line));
        }
    }
    file.close();

    return 0;
}
