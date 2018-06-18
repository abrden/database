project(tests)

file(GLOB SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC Catch)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _definitions)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _entities)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _server_concurrency)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _client_concurrency)
ParseAndAddCatchTests(${PROJECT_NAME})

