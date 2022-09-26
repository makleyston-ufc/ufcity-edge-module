//
// Created by makleyston on 23/09/22.
//

#include <string>
#include <iostream>
#include <mqtt/callback.h>
#include <mqtt/async_client.h>
#include "../../in_memory_storage/common/fog_node_address.h"
#include "../lib/mqtt_settings.h"
#include "../../error/error_list.h"
const int	N_RETRY_ATTEMPTS = 5;

namespace ufcity_mqtt {

    class action_listener : public virtual mqtt::iaction_listener
    {
        std::string name_;

        void on_failure(const mqtt::token& tok) override {
            std::cout << name_ << " failure";
            if (tok.get_message_id() != 0)
                std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
            std::cout << std::endl;
        }

        void on_success(const mqtt::token& tok) override {
            std::cout << name_ << " success";
            if (tok.get_message_id() != 0)
                std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
            auto top = tok.get_topics();
            if (top && !top->empty())
                std::cout << "\ttoken topic: '" << (*top)[0] << "', ..." << std::endl;
            std::cout << std::endl;
        }

    public:
        action_listener(const std::string& name) : name_(name) {}
    };

/////////////////////////////////////////////////////////////////////////////

/**
 * Local callback & listener class for use with the client connection.
 * This is primarily intended to receive messages, but it will also monitor
 * the connection to the broker. If the connection is lost, it will attempt
 * to restore the connection and re-subscribe to the topic.
 */
    class callback : public virtual mqtt::callback,
                     public virtual mqtt::iaction_listener

    {
        // Counter for the number of connection retries
        int nretry_;
        // The MQTT client
        mqtt::async_client& cli_;
        // Options to use if we need to reconnect
        mqtt::connect_options& connOpts_;
        // An action listener to display the result of actions.
        action_listener subListener_;

        // This deomonstrates manually reconnecting to the broker by calling
        // connect() again. This is a possibility for an application that keeps
        // a copy of it's original connect_options, or if the app wants to
        // reconnect with different options.
        // Another way this can be done manually, if using the same options, is
        // to just call the async_client::reconnect() method.
        void reconnect() {
            std::this_thread::sleep_for(std::chrono::milliseconds(2500));
            try {
                cli_.connect(connOpts_, nullptr, *this);
            }
            catch (const mqtt::exception& exc) {
                std::cerr << "Error: " << exc.what() << std::endl;
                exit(1);
            }
        }

        // Re-connection failure
        void on_failure(const mqtt::token& tok) override {
            std::cout << "Connection attempt failed" << std::endl;
            if (++nretry_ > N_RETRY_ATTEMPTS)
                exit(1);
            reconnect();
        }

        // (Re)connection success
        // Either this or connected() can be used for callbacks.
        void on_success(const mqtt::token& tok) override {}

        // (Re)connection success
        void connected(const std::string& cause) override {
            std::cout << "\nConnection success" << std::endl;
            std::cout << "\nSubscribing to topic '" << ufcity::get_topic_receive_commands() << "'\n"
                      << "\tfor client " << ufcity::get_sub_client_id()
                      << " using QoS" << ufcity::QOS << "\n"
                      << "\nPress Q<Enter> to quit\n" << std::endl;

            cli_.subscribe(ufcity::get_topic_receive_commands(), ufcity::QOS, nullptr, subListener_);
        }

        // Callback for when the connection is lost.
        // This will initiate the attempt to manually reconnect.
        void connection_lost(const std::string& cause) override {
            std::cout << "\nConnection lost" << std::endl;
            if (!cause.empty())
                std::cout << "\tcause: " << cause << std::endl;

            std::cout << "Reconnecting..." << std::endl;
            nretry_ = 0;
            reconnect();
        }

        // Callback for when a message arrives.
        void message_arrived(mqtt::const_message_ptr msg) override {
            std::cout << "Message arrived" << std::endl;
            std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
            std::cout << "\tpayload: '" << msg->to_string() << "'\n" << std::endl;
        }

        void delivery_complete(mqtt::delivery_token_ptr token) override {}

    public:
        callback(mqtt::async_client& cli, mqtt::connect_options& connOpts)
                : nretry_(0), cli_(cli), connOpts_(connOpts), subListener_("Subscription") {}
    };


    int subscribe(){
        // A subscriber often wants the server to remember its messages when its
        // disconnected. In that case, it needs a unique ClientID and a
        // non-clean session.

        mqtt::async_client cli(ufcity::get_fog_node_address(), ufcity::get_sub_client_id());

        mqtt::connect_options connOpts;
        connOpts.set_clean_session(false);

        // Install the callback(s) before connecting.
        callback cb(cli, connOpts);
        cli.set_callback(cb);

        // Start the connection.
        // When completed, the callback will subscribe to topic.

        try {
            std::cout << "Connecting to the MQTT server..." << std::flush;
            cli.connect(connOpts, nullptr, cb);
        }
        catch (const mqtt::exception& exc) {
            std::cerr << "\nERROR: Unable to connect to MQTT server: '"
                      << ufcity::get_fog_node_address() << "'" << exc << std::endl;
            return 1; //TODO put code error correctly
        }
//
//        // Just block till user tells us to quit.
//
//        while (std::tolower(std::cin.get()) != 'q')
//            ;

        // Disconnect

        try {
            std::cout << "\nDisconnecting from the MQTT server..." << std::flush;
            cli.disconnect()->wait();
            std::cout << "OK" << std::endl;
        }
        catch (const mqtt::exception& exc) {
            std::cerr << exc << std::endl;
            return 1;
        }

        return 0;
    }


//
//    class callback : public virtual mqtt::callback {
//    public:
//        void connection_lost(const std::string &cause) override {
//            std::cout << "\nConnection lost" << std::endl;
//            if (!cause.empty())
//                std::cout << "\tcause: " << cause << std::endl;
//        }
//
//        void delivery_complete(mqtt::delivery_token_ptr tok) override {
//            std::cout << "\tDelivery complete for token: "
//                      << (tok ? tok->get_message_id() : -1) << std::endl;
//        }
//    };
//
//    void wait_message(mqtt::async_client* cli){
//
//        // Consume messages
//        // This just exits if the client is disconnected.
//        // (See some other examples for auto or manual reconnect)
//        std::cout << "Waiting for messages." << "'" << std::endl;
//        while (true) {
//            std::cout << " &&&&& Aqui" << std::endl;
//            auto msg = cli->consume_message();
//            if (!msg) break;
//            std::cout << msg->get_topic() << ": " << msg->to_string() << std::endl;
//        }
//        std::cout << " &&&&& Aqui" << std::endl;
//        // If we're here, the client was almost certainly disconnected.
//        // But we check, just to make sure.
//        if (cli->is_connected()) {
//            std::cout << "\nShutting down and disconnecting from the MQTT server..." << std::flush;
//            cli->unsubscribe(ufcity::get_topic_receive_commands())->wait();
//            cli->stop_consuming();
//            cli->disconnect()->wait();
//            std::cout << "OK" << std::endl;
//        } else {
//            std::cout << "\nClient was disconnected" << std::endl;
//        }
//    }
//
//
//    int subscribe() {
//        std::string _address = ufcity::get_fog_node_address();
//        std::cout << "Initializing for server '" << _address << "'..." << std::endl;
////        auto cli = std::make_shared<mqtt::async_client>(_address, ufcity::get_sub_client_id());
//        mqtt::async_client cli(_address, ufcity::get_sub_client_id());
//
//        auto connOpts = mqtt::connect_options_builder()
//                .clean_session(false)
//                .finalize();
//
//        try {
//            // Start consumer before connecting to make sure to not miss messages
//            cli.start_consuming();
//
//            // Connect to the server
//
//            std::cout << "Connecting to the MQTT server..." << std::flush;
//            auto tok = cli.connect(connOpts);
//
//            // Getting the connect response will block waiting for the
//            // connection to complete.
//            auto rsp = tok->get_connect_response();
//
//            // If there is no session present, then we need to subscribe, but if
//            // there is a session, then the server remembers us and our
//            // subscriptions.
//            if (!rsp.is_session_present())
//                cli.subscribe(ufcity::get_topic_receive_commands(), ufcity::QOS)->wait();
//
//            std::cout << "OK" << std::endl;
//
////            std::thread subscribe_thread(wait_message, &cli);
////            wait_message(&cli);
////            subscribe_thread.join();
//
//            std::cout << "Waiting for messages on topic: '" << ufcity::get_topic_receive_commands() << "'" << std::endl;
//
//            while (true) {
//                auto msg = cli.consume_message();
//                if (!msg) break;
//                std::cout << msg->get_topic() << ": " << msg->to_string() << std::endl;
//            }
//
//            // If we're here, the client was almost certainly disconnected.
//            // But we check, just to make sure.
//
//            if (cli.is_connected()) {
//                std::cout << "\nShutting down and disconnecting from the MQTT server..." << std::flush;
//                cli.unsubscribe(ufcity::get_topic_receive_commands())->wait();
//                cli.stop_consuming();
//                cli.disconnect()->wait();
//                std::cout << "OK" << std::endl;
//            }
//            else {
//                std::cout << "\nClient was disconnected" << std::endl;
//            }
//        }
//        catch (const mqtt::exception& exc) {
//            std::cerr << "\n  " << exc << std::endl;
//            return 1;
//        }
//
//        return  0;
//    }
}