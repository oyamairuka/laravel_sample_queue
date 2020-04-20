# サブディレクトリを登録
add_subdirectory(RequestHandler)
add_subdirectory(RequestHandlerFactory)
add_subdirectory(ServerApplication)
add_subdirectory(Element)

add_executable(LaravelSampleQueue main.cpp)

target_link_directories(LaravelSampleQueue
                        PUBLIC ${Poco_LIBRARY_DIRS})
target_link_libraries(LaravelSampleQueue
                        ServerApplicationMod
                        SubsystemsMod
                        RequestHandlerFactoryMod
                        RequestHandlerMod
                        QueueElementMod
                        ${ADD_LIBRARIES}
                        )
