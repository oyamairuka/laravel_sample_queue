add_library(SubsystemsMod STATIC
    LSQServer.cpp
    LSQQueue.cpp
    LSQConsole.cpp
)

target_include_directories(SubsystemsMod
  PUBLIC ${LSQ_INCLUDE_DIRS}
  PUBLIC ${Poco_INCLUDE_DIRS}
  )
