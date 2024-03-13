cmake_minimum_required(VERSION 3.21)
project(TowerDefenseProject LANGUAGES CXX)


include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE) 
FetchContent_MakeAvailable(json)


add_executable(${CMAKE_PROJECT_NAME} src/main.cpp "include/TD_attacker.cpp")

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sfml-graphics sfml-audio sfml-window sfml-system nlohmann_json::nlohmann_json)

set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)


if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${FETCHCONTENT_BASE_DIR}/sfml-src/extlibs/bin/x64/openal32.dll $<TARGET_RUNTIME_DLLS:${CMAKE_PROJECT_NAME}> $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif()
install(TARGETS ${CMAKE_PROJECT_NAME})

# Set the path to your .clang-tidy file
set(CMAKE_CXX_CLANG_TIDY "${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy")
# Add the sources to the target
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})