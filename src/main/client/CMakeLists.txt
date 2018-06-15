project(client)

add_subdirectory(lib)

set(SOURCES
        "main.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _concurrency)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _client_entities)