cmake_minimum_required(VERSION 2.8)
project(laravel_sample_queue CXX)

#set(Poco_INCLUDE_DIRS C:/poco-1.10.1-include)
#set(Poco_LIBRARY_DIRS C:/poco-1.10.1/cmake-build/lib/Release)
#
#if(NOT(${CMAKE_BUILD_TYPE} STREQUAL "Release"))
#    message(STATUS "--------------------------------NOT Release Mode")
#    set(Poco_LIBRARY_DIRS C:/poco-1.10.1/cmake-build/lib/debug)
#endif()

set(LSQ_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)

#if(WIN32)
#    set(ADD_LIBRARIES
#        Ws2_32.lib
#        Iphlpapi.lib
#    )
#endif(WIN32)

# サブディレクトリを登録
add_subdirectory(src)
