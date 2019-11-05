cmake_minimum_required(VERSION 3.15)
project(plc_emulator)

set(CMAKE_CXX_STANDARD 17)
set(Protobuf_PROTOC_EXECUTABLE /usr/bin/protoc)

find_package(Protobuf 3.11.0 REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})

set(ProtobufTestsProtoSources
        config.proto
        mem_access.proto
        system_specification.proto)

set(ProtobufTestsSources
        library.cpp library.h mem_unit.h logger.h
        ${ProtobufTestsProtoSources} datatype.h elementary_datatypes.h datatype_registry.h resource.h variable.h pou_container.h utils.h synchronized_queue.h executor.h clock.h task.h functions_registry.h kronos_api.h resource_registry.h config.h resource_manager.h sfb/tof.h instruction_registry.h sfb/sfb.h sfb/ton.h sfb/tp.h sfb_registry.h sfc/sfc.h sfc_registry.h)

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${ProtobufTestsProtoSources})

add_library(plc_emulator SHARED
        ${ProtobufTestsSources}
        ${PROTO_SRCS} ${PROTO_HDRS})

target_link_libraries(plc_emulator ${PROTOBUF_LIBRARY})
