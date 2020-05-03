add_library(RequestHandlerMod STATIC
            PopRequestHandler.cpp
            PushRequestHandler.cpp
            SizeRequestHandler.cpp
            CommandRequestHandler.cpp
)

target_include_directories(RequestHandlerMod
  PUBLIC ${LSQ_INCLUDE_DIRS}
  PUBLIC ${Poco_INCLUDE_DIRS}
  )
