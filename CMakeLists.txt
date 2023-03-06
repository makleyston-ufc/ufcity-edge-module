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
        ufcity_interface.h ufcity_interface.cpp

        client_demo/main.cpp
        client_demo/ext/json_data_sample.hpp

        orchestrator/orchestrator.h orchestrator/orchestrator.cpp

        parser/parser_json.h parser/parser_json.cpp

        model/device.h model/device.cpp
        model/resource.h model/resource.cpp

        in_memory_storage/common/fog_node_address.h in_memory_storage/common/fog_node_address.cpp
        in_memory_storage/resources_map/resources_map.h in_memory_storage/resources_map/resources_map.cpp
        in_memory_storage/device_data/device_data.h in_memory_storage/device_data/device_data.cpp

        communcation/message_sender/message_sender.h communcation/message_sender/message_sender.cpp
        communcation/communication_interface/communication_interface.h communcation/communication_interface/communication_interface.cpp
        communcation/message_receiver/message_receiver.h communcation/message_receiver/message_receiver.cpp

        semantic_annotation/semantic_annotation.h semantic_annotation/semantic_annotation.cpp

        pre_pocessing/pre_processing.h pre_pocessing/pre_processing.cpp

        processing/processing.h processing/processing.cpp

        util/util.h util/util.cpp)

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

#set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
#set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(main ${SOURCE_FILES})
target_link_libraries(main paho-mqttpp3 paho-mqtt3as ssl crypto ${CMAKE_THREAD_LIBS_INIT})
