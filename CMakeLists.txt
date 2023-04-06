# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

project("ufcity")

set(SOURCE_FILES
        ufcity_interface.h ufcity_interface.cpp

        client_demo/main.cpp
        client_demo/ext/json_data_sample.hpp
        client_demo/example2.h client_demo/example1.h client_demo/menu.h

        orchestrator/orchestrator.h orchestrator/orchestrator.cpp

        parser/parser_json.h parser/parser_json.cpp

        model/device.h model/device.cpp
        model/resource.h model/resource.cpp

        in_memory_storage/common/fog_node_address.h in_memory_storage/common/fog_node_address.cpp
        in_memory_storage/resources_map/resources_map.h in_memory_storage/resources_map/resources_map.cpp
        in_memory_storage/device_data/device_data.h in_memory_storage/device_data/device_data.cpp

        communication/message_sender/message_sender.h communication/message_sender/message_sender.cpp
        communication/message_receiver/message_receiver.h communication/message_receiver/message_receiver.cpp
        in_memory_storage/device_data/location.h in_memory_storage/device_data/location.cpp

        pre_processing/pre_processing.h pre_processing/pre_processing.cpp

        processing/processing.h processing/processing.cpp

        util/util.h util/util.cpp
        in_memory_storage/message_queue.cpp in_memory_storage/message_queue.h
        model/message.cpp model/message.h
        model/observer/observer.h
        model/observer/subject.h
        in_memory_storage/observer/observer_client.cpp in_memory_storage/observer/observer_client.h)

find_package(Threads REQUIRED)

add_executable(main ${SOURCE_FILES})
target_link_libraries(main paho-mqttpp3 paho-mqtt3as ssl crypto ${CMAKE_THREAD_LIBS_INIT})
