# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project("ufcity")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

#add_library( # Sets the name of the library.
#        ufcity
#
#        # Sets the library as a shared library.
#        SHARED
#
#        # Provides a relative path to your source file(s).
#        native-lib.cpp
#        client_demo/main.cpp)

set(SOURCE_FILES
        client_demo/main.cpp
        ufcity_interface.cpp ufcity_interface.h
        model/resource.cpp model/resource.h
        observer/observer.h
        orchestrator/orchestrator.cpp orchestrator/orchestrator.h
        model/device.cpp model/device.h
        parser/parser_json.cpp parser/parser_json.h
        in_memory_storage/spatial_context_data/spatial_context_data.cpp in_memory_storage/spatial_context_data/spatial_context_data.h
        client_demo/ext/json_data_sample.hpp
        in_memory_storage/resources_map/resources_map.cpp in_memory_storage/resources_map/resources_map.h
        semantic_annotation/semantic_annotation.cpp semantic_annotation/semantic_annotation.h
        pre_pocessing/pre_processing.cpp pre_pocessing/pre_processing.h
        processing/processing.cpp processing/processing.h
        communcation/message_sender/message_sender.cpp
        communcation/message_sender/message_sender.h
        communcation/communication_interface/communication_interface.h
        communcation/communication_interface/communication_interface.cpp
        communcation/message_receiver/message_receiver.cpp
        communcation/message_receiver/message_receiver.h
        security/security.cpp security/security.h
        observer/subject.h
        error/error_list.h
        client_demo/ext/observer_client.h
        client_demo/ext/publish.cpp client_demo/ext/publish.h
        communcation/lib/mqtt_settings.h
        util/util.h
        in_memory_storage/common/fog_node_address.cpp
        in_memory_storage/common/fog_node_address.h communcation/communication_interface/mqtt_subscribe.h client_demo/ext/cod_for_text.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.


#find_library( # Sets the name of the path variable.
        #log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        #log
        #)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

#target_link_libraries( # Specifies the target library.
#        ufcity

        # Links the target library to the log library
        # included in the NDK.
#        ${log-lib})

add_executable(main ${SOURCE_FILES})
target_link_libraries(main paho-mqttpp3 paho-mqtt3as ssl crypto)