add_library(QueueElementMod STATIC
            QueueElement.cpp
)

target_include_directories(QueueElementMod
  PUBLIC ${LSQ_INCLUDE_DIRS}
  PUBLIC ${Poco_INCLUDE_DIRS}
  )