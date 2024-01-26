//
// Created by makleyston on 13/08/22.
//

#include <regex>
#include <thread>
#include "orchestrator.h"
#include "../in_memory_storage/resources_map/resources_map.h"
#include "../communication/message_sender/message_sender.h"
#include "../communication/message_receiver/message_receiver.h"
#include "../in_memory_storage/common/fog_node_address.h"
#include "../in_memory_storage/device_data/device_data.h"
#include "../in_memory_storage/message_queue.h"
#include "../in_memory_storage/observer/observer_client.h"
#include "../communication/lib/mqtt_settings.h"
#include "../model/config/methods.h"
#include "../in_memory_storage/buffer/buffer.h"
#include "../model/config/config.h"

namespace ufcity {

    orchestrator* orchestrator::instance = nullptr;

    int orchestrator::init(const std::string& _data) {
        if (instance == nullptr){
            /* Check device */
            device * _device = device_from_json(_data);
            if (_device == nullptr) return ERROR_JSON_PARSER;
            print_log("The device '" + _device->get_uuid_device() + "' is OK!");

            /* Create an instance */
            instance = new orchestrator(_device);
            print_log("Edge Module successfully created!");

            return 0;
        }
        print_log("An instance of the Edge Module already exists!");
        return 1; // An instance of the Edge Module already exists
    }

    orchestrator* orchestrator::get_instance(){
        return instance;
    }

    orchestrator::orchestrator(device * device) {
        this->save_device(device);

        /* Settings to data process. All disabled.  */
        this->set_config(new ufcity::config());

        ufcity_db::message_queue::get_instance()->set_run_state(true);
    }

    int orchestrator::save_fog_node_address(const std::string& _address, const std::string& _port) const{
        ufcity_db::fog_node_address::get_instance()->set_fog_node_address(_address);
        ufcity_db::fog_node_address::get_instance()->set_fog_node_port(_port);
        return 0;
    }

    int orchestrator::check_fog_node_address(const std::string& _address){
        if(_address.empty()) return ERROR_FOG_NODE_ADDRESS_EMPTY;
        if ((_address != "localhost") &&
            (!std::regex_match (_address, std::regex(R"(^([01]?\d\d?|2[0-4]\d|25[0-5])(?:\.(?:[01]?\d\d?|2[0-4]\d|25[0-5])){3}(?:[0-2]\d|3[0-2])?$)"))))
//                (!std::regex_match (_address, std::regex("^([01]?\\d\\d?|2[0-4]\\d|25[0-5])(?:\\.(?:[01]?\\d\\d?|2[0-4]\\d|25[0-5])){3}(?:[0-2]\\d|3[0-2])?$"))))
            return ERROR_FOG_NODE_ADDRESS_NOT_MATCHED;
        return 0;
    }

    int orchestrator::register_resource(const std::string& data) {
        resource * _resource = resource_from_json(data);
        if(_resource == nullptr) {
            print_log("JSON parser error!");
            return ERROR_JSON_PARSER;
        }

        int res_s = ufcity_db::device_data::get_instance()->add_spatial_context_data(_resource);
        if (res_s != 0) return res_s;

        print_log("Convert from JSON to Resource successfully! Resource UUID: " + _resource->get_uuid_resource() + ".");
        ufcity_db::resources_map * map = ufcity_db::resources_map::get_instance();

        if(map->find_by_uuid_resource(_resource->get_uuid_resource())){
            print_log("The resource " + _resource->get_uuid_resource() + " already exists!");
            return ERROR_RESOURCE_ALREADY_EXIST;
        }else{
            int r_reg = map->register_resource(_resource);
            if(r_reg == 0) print_log("Resource " + _resource->get_uuid_resource() + " has been successfully stored! ");
            return r_reg;
        }
    }

    int orchestrator::remove_resource(const std::string& data) const{
        resource * _resource = resource_from_json(data);
        if(_resource == nullptr) return ERROR_JSON_PARSER;
        print_log("Convert from JSON to Resource successfully! Resource UUID: " + _resource->get_uuid_resource());
        if(ufcity_db::resources_map::get_instance()->remove_by_uuid(_resource->get_uuid_resource()) == 0) {
            print_log("Resource " + _resource->get_uuid_resource() + " successfully removed!");
            return 0;
        }else {
            print_log("Resource " + _resource->get_uuid_resource() + " not found!");
            return ERROR_RESOURCE_NOT_FOUND;
        }
    }

    int orchestrator::remove_resource_by_uuid(const std::string& uuid_resource) const{
        if(ufcity_db::resources_map::get_instance()->remove_by_uuid(uuid_resource) == 0) {
            print_log("Resource " + uuid_resource + " successfully removed!");
            return 0;
        }else {
            print_log("Resource " + uuid_resource + " not found!");
            return ERROR_RESOURCE_NOT_FOUND;
        }
    }

    int orchestrator::send_resource_data(const std::string& data) const{
        //Convert JSON to Resource
        resource * _resource = resource_from_json(data);
        if(_resource == nullptr) return ERROR_JSON_PARSER;
//        print_log("Convert from JSON to Resource successfully! Resource UUID: " + _resource->get_uuid_resource());

        int res_s = ufcity_db::device_data::get_instance()->add_spatial_context_data(_resource);
        if (res_s != 0) return res_s;

        if(this->config->get_data_grouping_config()->get_method_char() != methods::NONE){ //It has a config set
            ufcity_db::buffer::get_instance()->add_resource(_resource);
            auto _data = ufcity_db::buffer::get_instance()->get_resource_buffer();
            std::cout << "Total resources to be send: " << _data.size() << std::endl;
            if(_data.size() > 0){
                auto _resources_to_send = proc::handler(_data);

                for(auto _r : _resources_to_send){
                    /* Sending resource data to fog computing */
                    ufcity_db::resources_map::get_instance()->send_data_to_fog(_r);
                    std::cout << "\tAdded the Resource UUID " + _resource->get_uuid_resource() + " in the submit queue. " << std::endl;
                }

            }
        }else {
            /* Sending resource data to fog computing */
            ufcity_db::resources_map::get_instance()->send_data_to_fog(_resource);
            std::cout << "\tAdded the Resource UUID " + _resource->get_uuid_resource() + " in the submit queue. " << std::endl;
        }
        return 0;
    }

    int orchestrator::update_location(device * _device) const{
        return this->save_device(_device);
    }

    int orchestrator::save_device(device * _device) const{
        ufcity_db::device_data::get_instance()->save_device(_device);
        print_log("Location successfully stored! "
                  "Location: Lat. " + _device->get_location()->get_lat() +
                  ", Lng. " + _device->get_location()->get_lng() +
                  ", and Alt. " + _device->get_location()->get_alt());
        return 0;
    }

    void orchestrator::print_log(const std::string& log) {
        bool PRINT = true;
        if(PRINT) std::cout << ">> " + log << std::endl;
    }

    std::unordered_map<std::string, const ufcity::resource *> * orchestrator::get_resources_map() const{
        return ufcity_db::resources_map::get_instance()->get_resources_map();
    }

    int orchestrator::register_observer(ufcity::observer *observer) const {
        ufcity_db::observer_client::get_instance()->register_observer(observer);
        print_log("Observer client successfully registered!");
        return 0;
    }

    int orchestrator::remove_observer(ufcity::observer *observer) const {
        ufcity_db::observer_client::get_instance()->remove_observer(observer);
        print_log("Observer client successfully removed!");
        return 0;
    }

    int orchestrator::remove_observer(int id_observer) const {
        ufcity_db::observer_client::get_instance()->remove_observer(id_observer);
        print_log("Observer client successfully removed!");
        return 0;
    }

    orchestrator::~orchestrator() {
        ufcity_db::message_queue::get_instance()->set_run_state(false);
        this->save_device(nullptr);
        this->save_fog_node_address("", "");
    }

    void orchestrator::destroy() {
        ufcity_db::message_queue::get_instance()->set_run_state(false);
        delete orchestrator::instance;
    }

    void thread_publish(){
        auto * ms = new ufcity::message_sender();
        ms->running_thread_publish();
    }

    void thread_subscribe(){
        auto * mr = new ufcity::message_receiver();
        mr->running_thread_subscribe();
    }

    int orchestrator::connect_to_fog(const std::string& _fog_node_address, const std::string& _port) const {
        /* Check fog node address */
//        int _address_error = check_fog_node_address(_fog_node_address);
//        if(_address_error != 0) return _address_error;
        this->save_fog_node_address(_fog_node_address, _port);
        print_log("The fog node address '" + _fog_node_address + " and port " + _port + "' is OK and is stored!");

        /* Initializing */
        print_log("Edge Module connecting to fog node! Fog node address: " + _fog_node_address + ".");

        /* Thread to publish */
        std::thread connect_thread_publish(&thread_publish);
        connect_thread_publish.detach();
        print_log("Publishing ... OK.");

        /* Thread to subscribe */
        std::thread connect_thread_subscribe(&thread_subscribe);
        connect_thread_subscribe.detach();
        print_log("Subscribing ... OK.");

        /* Ensuring the connection time on the fog computing node. */
        std::this_thread::sleep_for(std::chrono::seconds(2));

        /* Sending device data */
        ufcity_db::device_data::get_instance()->send_to_fog();

        return 0;
    }

    void orchestrator::finish() {
        ufcity_db::message_queue::get_instance()->set_run_state(false);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Finishing the Edge Module." << std::endl;
        std::cout << "Edge Module: Bye bye." << std::endl;
    }

    bool orchestrator::alive() {
        auto _message = ufcity_db::message_queue::get_instance()->pull_queue_received_message();
        if(_message != nullptr) {
            ufcity_db::observer_client::get_instance()->receive_message(_message->get_topic(), _message->get_message());
        }

        /* In order not to fill 100% of the CPU */
        std::this_thread::sleep_for(std::chrono::microseconds (500));
        return ufcity_db::message_queue::get_instance()->get_run_state();
    }

    int orchestrator::set_config(ufcity::config *config) {
        this->config = config;
        return 0;
    }

    ufcity::config * orchestrator::get_config() const {
        return this->config;
    }


} // ufcity