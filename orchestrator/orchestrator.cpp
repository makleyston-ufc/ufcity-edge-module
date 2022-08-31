//
// Created by makleyston on 13/08/22.
//

#include "orchestrator.h"

namespace ufcity {

    orchestrator* orchestrator::instance = nullptr;

    int orchestrator::init(const std::string& data, const std::string& fog_node_address) {
        if (instance == nullptr){
            //Check location data
            location * _location = location_from_json(data);
            if (_location == nullptr) return ERROR_JSON_PARSER;
            print_log("The location data is OK!");

            //Check fog node address
            int c_address = check_fog_node_address(fog_node_address);
            if(c_address != 0) return c_address;
            print_log("The fog node address is OK!");

            //Create an instance
            instance = new orchestrator(_location, fog_node_address);
            print_log("Edge Module successfully created!");

            return 0;
        }
        print_log("An instance of the Edge Module already exists!");
        return 1; // An instance of the Edge Module already exists
    }

    orchestrator* orchestrator::get_instance(){
        return instance;
    }

    orchestrator::orchestrator(location * location, const std::string& fog_node_address) {
        this->save_location(location);
        this->save_fog_node_address(fog_node_address);
    }

    int orchestrator::save_fog_node_address(const std::string& address) const{
        north_interface::get_instance()->set_fog_node_address(address);
        return 0;
    }

    int orchestrator::check_fog_node_address(const std::string& address){
        if(address.empty()){ //TODO
            return ERROR_FOG_NODE_ADDRESS;
        }
        return 0;
    }

    int orchestrator::register_resource(const std::string& data) {
        resource * _resource = resource_from_json(data);
        if(_resource == nullptr) {
            print_log("JSON parser error!");
            return ERROR_JSON_PARSER;
        }
        print_log("Convert from JSON to Resource successfully! Resource UUID: " + _resource->get_resource_uuid());

//        _resource->print();

        ufcity_db::resources_map * map = ufcity_db::resources_map::get_instance();
        if(map->find_resource_by_uuid(_resource->get_resource_uuid())){
            print_log("The resource " + _resource->get_resource_uuid() + " already exists!");
            return ERROR_RESOURCE_ALREADY_EXIST;
        }else{
            std::string semantic = get_semantic_from_resource(_resource);
            if(semantic.empty()) return ERROR_SEMANTIC_ANNOTATION;
            print_log("Semantic annotation make successfully on " + _resource->get_resource_uuid());
            int r_reg = map->register_resource(_resource->get_resource_uuid(), semantic);
            if(r_reg == 0) print_log("Resource " + _resource->get_resource_uuid() + " has been successfully stored! ");
            return r_reg;
        }
    }

    int orchestrator::remove_resource(const std::string& data) const{
        resource * _resource = resource_from_json(data);
        if(_resource == nullptr) return ERROR_JSON_PARSER;
        print_log("Convert from JSON to Resource successfully! Resource UUID: " + _resource->get_resource_uuid());
        if(ufcity_db::resources_map::get_instance()->remove_resource(_resource->get_resource_uuid()) == 0) {
            print_log("Resource " + _resource->get_resource_uuid() + " successfully removed!");
            return 0;
        }else {
            print_log("Resource " + _resource->get_resource_uuid() + " not found!");
            return ERROR_RESOURCE_NOT_FOUND;
        }
    }

    int orchestrator::send_resource_data(const std::string& data) const{
        //Convert JSON to Resource
        resource * _resource = resource_from_json(data);
        if(_resource == nullptr) return ERROR_JSON_PARSER;
        print_log("Convert from JSON to Resource successfully! Resource UUID: " + _resource->get_resource_uuid());

        //Get semantic from resource
        std::string semantic = ufcity_db::resources_map::get_instance()->get_resource_semantic_by_uuid(_resource->get_resource_uuid());
        if(semantic.empty()){
            print_log("The resource " + _resource->get_resource_uuid() + " has not yet been registered!");
            return ERROR_RESOURCE_NOT_FOUND;
        }
        print_log("Resource " + _resource->get_resource_uuid() + " semantics were successfully retrieved.");

        //Pre-processing the already semantically annotated resource
        int r_pre = pre_proc::handler(semantic);
        if (r_pre != 0) {
            //TODO
            return r_pre;
        }

        //Pre-processing the already semantically annotated resource
        int res_p = proc::handler(semantic);
        if (res_p != 0) {
            //TODO
            return res_p;
        }

        int res_s = ufcity_db::spatial_context_data::get_instance()->add_spatial_context_data(semantic);
        if (res_s != 0) return res_s;

        int res_m = data_formatter(semantic);
        if (res_m != 0) return res_m;

        north_interface::get_instance()->publish_resource_data(semantic);

        return 0;
    }

    int orchestrator::update_location(location * l) const{
        return this->save_location(l);
    }

    int orchestrator::save_location(location * l) const{
        ufcity_db::spatial_context_data::get_instance()->save_location(l);
        print_log("Location successfully stored! Location: Lat. "+l->get_lat()+" and Lng. "+l->get_lng());
        return 0;
    }

    void orchestrator::print_log(const std::string& log) {
        bool PRINT = true;
        if(PRINT) std::cout << ">> " + log << std::endl;
    }

    std::unordered_map<std::string, std::string> * orchestrator::get_resources_map() const{
        return ufcity_db::resources_map::get_instance()->get_resources_map();
    }

    int orchestrator::register_observer(ufcity::observer *observer) const {
       message_receiver::get_instance()->register_observer(observer);
       print_log("Observer client successfully registered!");
       return 0;
    }

    int orchestrator::remove_observer(ufcity::observer *observer) const {
        int m_res = message_receiver::get_instance()->remove_observer(observer);
        if(m_res == 0) print_log("Observer client successfully removal!");
        return m_res;
    }

} // ufcity