project(_server_entities)

file(GLOB SOURCES "*.cpp" "*.h")

add_library(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _server_concurrency)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _entities)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _sigint_handler)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _signal_handler)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
