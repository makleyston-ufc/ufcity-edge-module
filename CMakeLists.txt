# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

project("ufcity")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/libfolder")

set(SOURCE_FILES
        ufcity_interface.h ufcity_interface.cpp

        client_demo/main.cpp
        client_demo/ext/json_data_sample.hpp
        client_demo/example2.h client_demo/example1.h client_demo/menu.h

        orchestrator/orchestrator.h orchestrator/orchestrator.cpp
        util/util.h util/util.cpp
        parser/parser_json.h parser/parser_json.cpp

        in_memory_storage/common/fog_node_address.h in_memory_storage/common/fog_node_address.cpp
        in_memory_storage/resources_map/resources_map.h in_memory_storage/resources_map/resources_map.cpp
        in_memory_storage/device_data/device_data.h in_memory_storage/device_data/device_data.cpp
        in_memory_storage/device_data/location.h in_memory_storage/device_data/location.cpp
        in_memory_storage/message_queue.cpp in_memory_storage/message_queue.h
        in_memory_storage/observer/observer_client.cpp in_memory_storage/observer/observer_client.h
        in_memory_storage/buffer/buffer.cpp in_memory_storage/buffer/buffer.h

        communication/message_sender/message_sender.h communication/message_sender/message_sender.cpp
        communication/message_receiver/message_receiver.h communication/message_receiver/message_receiver.cpp

        pre_processing/pre_processing.h pre_processing/pre_processing.cpp

        model/device.h model/device.cpp
        model/resource.h model/resource.cpp
        model/message.cpp model/message.h
        model/observer/observer.h
        model/observer/subject.h
        model/service.cpp model/service.h
        model/service_data.cpp model/service_data.h
        model/config/config.cpp model/config/config.h
        model/config/data_aggregation_config.cpp model/config/data_aggregation_config.h
        model/config/data_grouping_config.cpp model/config/data_grouping_config.h
        model/config/remove_outliers_config.cpp model/config/remove_outliers_config.h
        model/config/missing_data_config.cpp model/config/missing_data_config.h
        model/config/methods.h

        processing/missing_data.cpp processing/missing_data.h
        processing/remove_outliers.cpp processing/remove_outliers.h
        processing/processing.cpp processing/processing.h
        )

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} paho-mqttpp3 paho-mqtt3as ssl crypto ${CMAKE_THREAD_LIBS_INIT})
