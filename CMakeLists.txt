cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(QuanolaGame)

set(HEADERS include/CliRenderer.hpp 
            include/GameManager.hpp
            include/GameState.hpp
            include/IRenderer.hpp 
            include/Node.hpp 
            include/Event.hpp
            include/Option.hpp
            include/Serializer.hpp
            )

set(SOURCES src/quanola.cpp
            src/CliRenderer.cpp
            src/GameManager.cpp
            src/Node.cpp
            src/Option.cpp
            src/Serializer.cpp
            )

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                                                  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                                  $<INSTALL_INTERFACE:include>)

find_package(jsoncpp REQUIRED)
target_link_libraries(${PROJECT_NAME} JsonCpp::JsonCpp)
