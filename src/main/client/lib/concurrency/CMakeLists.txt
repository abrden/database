project(_client_concurrency)

file(GLOB SOURCES "*.cpp" "*.h")

add_library(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _concurrency)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC _definitions)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
