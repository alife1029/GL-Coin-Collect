# Dependencies
set(DEPENDENCIES)
set(DEPENDENCIES_DIR ${CMAKE_SOURCE_DIR}/Dependencies)
if(MSVC)
    # GLFW
    set(GLFW_DIR ${DEPENDENCIES_DIR}/GLFW)
    include_directories(${GLFW_DIR}/include)
    list(APPEND DEPENDENCIES ${GLFW_DIR}/lib-vc2019/glfw3.lib)

    # Freetype
    set(FT_DIR ${DEPENDENCIES_DIR}/freetype)
    include_directories(${FT_DIR}/include)
    list(APPEND DEPENDENCIES ${FT_DIR}/lib/freetype.lib)

    # OpenAL
    set(AL_DIR ${DEPENDENCIES_DIR}/OpenAL)
    include_directories(${AL_DIR}/include)
    list(APPEND DEPENDENCIES ${AL_DIR}/lib/OpenAL32.lib)

    # Sound File
    set(SNDFILE_DIR ${DEPENDENCIES_DIR}/sndfile)
    include_directories(${SNDFILE_DIR}/include)
    list(APPEND DEPENDENCIES ${SNDFILE_DIR}/lib/sndfile.lib)
elseif(UNIX)
    find_package(glfw3 3.3.4 REQUIRED)
    find_package(OpenAL 1.21.1 REQUIRED)
    list(APPEND DEPENDENCIES glfw)
endif()
include_directories(
    ${DEPENDENCIES_DIR}/stb 
    ${DEPENDENCIES_DIR}/glad/include)

file(GLOB PROJECT_SOURCES
        ${PROJECT_DIR}/src/*.cpp
        ${PROJECT_DIR}/src/Application/*.cpp
        ${PROJECT_DIR}/src/Components/*.cpp
        ${PROJECT_DIR}/src/Entity/*.cpp
        ${PROJECT_DIR}/src/Exception/*.cpp
        ${PROJECT_DIR}/src/Graphics/*.cpp
        ${PROJECT_DIR}/src/Input/*.cpp
        ${PROJECT_DIR}/src/Math/*.cpp
        ${PROJECT_DIR}/src/Sound/*.cpp

        # GLAD sources
        ${DEPENDENCIES_DIR}/glad/src/*.c
        )

include_directories(${PROJECT_DIR}/include)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} ${DEPENDENCIES})

target_compile_definitions(${PROJECT_NAME} PRIVATE -DENGINE_BUILD_SHARED_LIB -DSTB_IMAGE_IMPLEMENTATION)

if(MSVC)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_DIR}/GLshaders/
                ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>/GLshaders/
        COMMAND ${CMAKE_COMMAND} -E copy
                ${FT_DIR}/lib/freetype.dll
                ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>/freetype.dll
        COMMAND ${CMAKE_COMMAND} -E copy
                ${AL_DIR}/bin/OpenAL32.dll
                ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>/OpenAL32.dll
        COMMAND ${CMAKE_COMMAND} -E copy
                ${SNDFILE_DIR}/bin/sndfile.dll
                ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>/sndfile.dll)
else()
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_DIR}/GLshaders/
                ${CMAKE_CURRENT_BINARY_DIR}/GLshaders/)
endif()
