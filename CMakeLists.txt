cmake_minimum_required(VERSION 3.10)
project(MonoCAM LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH "bin")

set(RESOURCE_C_FILE "${CMAKE_CURRENT_BINARY_DIR}/resources.c")
set(RESOURCE_H_FILE "${CMAKE_CURRENT_BINARY_DIR}/resources.h")

add_custom_command(
    OUTPUT ${RESOURCE_C_FILE}
    COMMAND glib-compile-resources --sourcedir ${CMAKE_CURRENT_SOURCE_DIR}/resources --target ${RESOURCE_C_FILE} --generate-source ${CMAKE_CURRENT_SOURCE_DIR}/resources.gresource.xml
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/resources.gresource.xml
    COMMENT "Generating resources.c from GLib..."
)

add_custom_command(
    OUTPUT ${RESOURCE_H_FILE}
    COMMAND glib-compile-resources --sourcedir ${CMAKE_CURRENT_SOURCE_DIR}/resources --target ${RESOURCE_H_FILE} --generate-header ${CMAKE_CURRENT_SOURCE_DIR}/resources.gresource.xml
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/resources.gresource.xml
    COMMENT "Generating resources.h from GLib..."
)


set(HDRS app_utils.h monocam_ux.h mono_cap.h)
set(CPPS app_utils.cc monocam_ux.cc mono_cap.cc)

find_package(PkgConfig)
pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET gtkmm-4.0)
find_package(OpenCV REQUIRED)

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
include_directories( ${GTKMM_INCLUDE_DIRS} )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_custom_target(GenerateResources DEPENDS  ${RESOURCE_C_FILE} ${RESOURCE_H_FILE})
add_executable(MonoCAM monocam.cpp ${HDRS} ${CPPS} ${RESOURCE_C_FILE} ${RESOURCE_H_FILE})
add_dependencies(MonoCAM GenerateResources)

target_link_libraries(MonoCAM PRIVATE PkgConfig::GTKMM)
target_link_libraries(MonoCAM PRIVATE ${OpenCV_LIBS} )


