add_library(RequestHandlerFactoryMod STATIC
    QueueRequestHandlerFactory.cpp
)

target_include_directories(RequestHandlerFactoryMod
  PUBLIC ${LSQ_INCLUDE_DIRS}
  PUBLIC ${Poco_INCLUDE_DIRS}
  )