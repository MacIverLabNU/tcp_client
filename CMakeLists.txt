cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

project(pufferbot_client
        VERSION 2019.1.0
        DESCRIPTION "add basic planning capabilities to agents"
        LANGUAGES CXX)

string(APPEND CMAKE_CXX_FLAGS " -fno-strict-aliasing -pthread ")

####
#### DEPENDENCIES
####

find_package (Dependencies QUIET)

if (NOT ${Dependencies_FOUND})
    if (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/DependenciesConfig.cmake)
        file(DOWNLOAD https://raw.githubusercontent.com/germanespinosa/dependencies/main/DependenciesConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/DependenciesConfig.cmake)
    endif()
    set(Dependencies_DIR "${CMAKE_CURRENT_BINARY_DIR}")
    find_package (Dependencies REQUIRED)
endif()

####
#### END DEPENDENCIES
####

string(APPEND CMAKE_CXX_FLAGS " -pthread ")
install_git_dependency(Easy-tcp https://github.com/germanespinosa/easy-tcp
        CMAKE_PROJECT
        IMPORT_TARGETS easy-tcp)

install_git_dependency(Cellworld https://github.com/germanespinosa/cellworld
        CMAKE_PROJECT
        IMPORT_TARGETS cellworld json-cpp)

add_executable(client main.cpp)
target_link_libraries( client
        LINK_PUBLIC
        easy-tcp)