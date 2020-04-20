add_subdirectory(Subsystems)

add_library(ServerApplicationMod STATIC
    LSQApplication.cpp
)

target_include_directories(ServerApplicationMod
  PUBLIC ${LSQ_INCLUDE_DIRS}
  PUBLIC ${Poco_INCLUDE_DIRS}
)
#target_link_libraries(ServerApplicationMod
#                      SubsystemsMod)