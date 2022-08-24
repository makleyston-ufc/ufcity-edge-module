//
// Created by makleyston on 13/08/22.
//

#include "orchestrator.h"
#include "../parser/parserJSON.h"
#include "../model/location_model.h"
#include "../spatial_context_data/spatial_context_data.h"

namespace ufcity {

    orchestrator* orchestrator::instance = 0;

    int orchestrator::init(std::string location) {
        if (instance == 0){
            instance = new orchestrator(location);
            return 0;
        }
        return 1; // Already exists an instance
    }

    orchestrator* orchestrator::get_instance(){
        return instance;
    }

    orchestrator::orchestrator(std::string location) {
        this->save_location(location);
    }

    int orchestrator::register_resource(std::string data){
        //Test
        std::cout << data << std::endl;
        return 0;

        //TODO
    }

    int orchestrator::remove_resource(std::string data){
        return 0;
        //TODO
    }

    int orchestrator::send_resource_data(std::string data){
        return 0;
        //TODO
    }

    int orchestrator::location_updater(std::string data){
        return 0;
        //TODO
    }

    int orchestrator::save_location(std::string data){
        location_model * location = fromJSON(data);
        if (location == nullptr) return 1; //JSON parser error
        ufcity_db::spatial_context_data::get_instance()->save_location(location);
        return 0;
    }

} // ufcity