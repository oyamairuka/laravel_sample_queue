cmake_minimum_required(VERSION 2.8)
project(laravel_sample_queue CXX)

set(Poco_INCLUDE_DIRS /usr/local/include)
set(Poco_LIBRARY_DIRS /usr/local/lib/poco)

if(NOT(${CMAKE_BUILD_TYPE} STREQUAL "Release"))
    message(STATUS "--------------------------------NOT Release Mode")
    set(Poco_LIBRARY_DIRS /usr/local/lib/poco)
endif()

set(LSQ_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)

if(WIN32)
    set(ADD_LIBRARIES
        Ws2_32.lib
        Iphlpapi.lib
    )
elseif(UNIX)
    set(CMAKE_CXX_FLAGS "-pthread")
    set(ADD_LIBRARIES
        libPocoEncodings.a
        libPocoUtil.a
        libPocoJSON.a
        libPocoNet.a
        libPocoXML.a    
        libPocoFoundation.a
    )
endif(WIN32)

# サブディレクトリを登録
add_subdirectory(src)
