add_library(RequestHandlerMod STATIC
            BulkRequestHandler.cpp
            LaterOnRequestHandler.cpp
            LaterRequestHandler.cpp
            PopRequestHandler.cpp
            PushOnRequestHandler.cpp
            PushRawRequestHandler.cpp
            PushRequestHandler.cpp
            SizeRequestHandler.cpp
)

target_include_directories(RequestHandlerMod
  PUBLIC ${LSQ_INCLUDE_DIRS}
  PUBLIC ${Poco_INCLUDE_DIRS}
  )
