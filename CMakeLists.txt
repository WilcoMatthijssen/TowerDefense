cmake_minimum_required(VERSION 3.21)
project(TowerDefenseProject LANGUAGES CXX)


set(CMAKE_CXX_CLANG_TIDY
  clang-tidy;
  -checks=*;
  -warnings-as-errors=*;)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)


add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sfml-graphics)
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)


if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${CMAKE_PROJECT_NAME}> $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif()
install(TARGETS ${CMAKE_PROJECT_NAME})
