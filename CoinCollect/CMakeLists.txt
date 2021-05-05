file(GLOB PROJECT_SOURCES ${PROJECT_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} Engine Scripts)

if(MSVC)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_DIR}/anim/
                ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>/anim/
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_DIR}/assets/
                ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>/assets/
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_DIR}/fonts/
                ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>/fonts/
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_DIR}/sound/
                ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>/sound/)
else()
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_DIR}/anim/
                ${CMAKE_CURRENT_BINARY_DIR}/anim/
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_DIR}/assets/
                ${CMAKE_CURRENT_BINARY_DIR}/assets/
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_DIR}/fonts/
                ${CMAKE_CURRENT_BINARY_DIR}/fonts/
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_DIR}/sound/
                ${CMAKE_CURRENT_BINARY_DIR}/sound/)
endif()
