cmake_minimum_required(VERSION 3.15)
project(plc_emulator)

set(CMAKE_CXX_STANDARD 17)
set(Protobuf_PROTOC_EXECUTABLE /usr/bin/protoc)

find_package(Protobuf 3.11.0 REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR})

set(ProtobufTestsProtoSources
        config.proto
        mem_access.proto
        system_specification.proto)

set(ProtobufTestsSources
        library.cpp library.h mem_unit.h pc_logger.h
        ${ProtobufTestsProtoSources}
        )

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${ProtobufTestsProtoSources})

add_library(plc_emulator SHARED ${ProtobufTestsSources} ${PROTO_SRCS} ${PROTO_HDRS})

target_link_libraries(plc_emulator ${PROTOBUF_LIBRARY})
