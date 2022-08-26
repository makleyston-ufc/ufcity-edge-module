//
// Created by makleyston on 13/08/22.
//

#include "orchestrator.h"

namespace ufcity {

    orchestrator* orchestrator::instance = 0;

    int orchestrator::init(std::string location) {
        if (instance == 0){
            instance = new orchestrator(location);
            print_log("Edge Module successfully created!");
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

    int orchestrator::register_resource(std::string data) {
        resource * r_resource = resource_from_json(data);
        if(r_resource == nullptr) {
            print_log("ERROR : JSON parser error!");
            return 1; //JSON parser error
        }
        print_log("Convert from JSON to Resource successfully! Resource UUID: " + r_resource->get_resource_uuid());

        ufcity_db::resources_map * map = ufcity_db::resources_map::get_instance();
        bool res = map->find_resource_by_uuid(r_resource->get_resource_uuid());
        if(res){
            print_log("The resource "+ r_resource->get_resource_uuid() +" already exists!");
            return 1;
        }else{
            std::string semantic = get_semantic_from_resource(r_resource);
            print_log("Semantic annotation make successfully on " + r_resource->get_resource_uuid());// +"! Semantic: " + semantic);
            int res = map->register_resource(r_resource->get_resource_uuid(), semantic);
            print_log("Resource "+ r_resource->get_resource_uuid() +" has been stored successfully! ");
            return res;
        }
    }

    int orchestrator::remove_resource(std::string data) const{
        resource * r = resource_from_json(data);
        print_log("Convert from JSON to Resource successfully! Resource UUID: " + r->get_resource_uuid());
        int res = ufcity_db::resources_map::get_instance()->remove_resource(r->get_resource_uuid());
        if(res == 0)
            print_log("Resource "+ r->get_resource_uuid() + " successfully removed!");
        else if(res == 1)
            print_log("Resource "+ r->get_resource_uuid() + " not found!");
        return res;
    }

    int orchestrator::send_resource_data(std::string data) const{
        return 0;
        //TODO
    }

    int orchestrator::location_updater(std::string data) const{
        return 0;
        //TODO
    }

    int orchestrator::save_location(std::string data) const{
        location * location = location_from_json(data);
        if (location == nullptr) return 1; //JSON parser error
        ufcity_db::spatial_context_data::get_instance()->save_location(location);
        print_log("Location successfully stored! Location: Lat. "+location->get_lat()+" and Lng. "+location->get_lng());
        return 0;
    }

    void orchestrator::print_log(std::string log) {
        bool PRINT = true;
        if(PRINT) std::cout << ">> " + log << std::endl;
    }

    std::unordered_map<std::string, std::string> * orchestrator::get_resources_map() const{
        return ufcity_db::resources_map::get_instance()->get_resources_map();
    }

} // ufcity