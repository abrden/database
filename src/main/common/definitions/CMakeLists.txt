project(_definitions)

file(GLOB SOURCES "*.h" "*.cpp")

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)