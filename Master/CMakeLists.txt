cmake_minimum_required(VERSION 3.5)

project(collector_master LANGUAGES CXX)

set(libs)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin)

set(PROTO_FILES
    ${CMAKE_SOURCE_DIR}/../proto/message_slave_device.proto
    ${CMAKE_SOURCE_DIR}/../proto/json.proto
)
find_package(Protobuf REQUIRED)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

find_package(Qt5 COMPONENTS Core Quick QuickControls2 Network REQUIRED)

set(INCLUDE_PATHS
    ${Protobuf_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
    )
include_directories(${INCLUDE_PATHS})
set(HEADERS
    src/infomanager.h
    src/infomodel.h
    src/zsplugin.hpp
    src/singleton.hpp
    )
set(SOURCES
    src/main.cpp
    src/infomanager.cpp
    src/infomodel.cpp
    )
set(RESOURCES
    collector.qrc
    )
set(SRC
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
    ${PROTO_SRCS}
    ${PROTO_HDRS}
    )
list(APPEND libs ${Protobuf_LIBRARIES})
list(APPEND libs Qt5::Core Qt5::Quick Qt5::Network Qt5::QuickControls2)
add_executable(${PROJECT_NAME} ${SRC})
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE ${libs})
