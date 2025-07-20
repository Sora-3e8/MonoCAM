cmake_minimum_required(VERSION 3.10)
project(MonoCAM)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH "bin")

set(HDRS app_utils.h monocam_ux.h mono_cap.h)
set(CPPS app_utils.cc monocam_ux.cc mono_cap.cc)

find_package(PkgConfig)
pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET gtkmm-4.0)
find_package(OpenCV REQUIRED)

include_directories( ${GTKMM_INCLUDE_DIRS} )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(MonoCAM monocam.cpp ${HDRS} ${CPPS})

target_link_libraries(MonoCAM PRIVATE PkgConfig::GTKMM)
target_link_libraries(MonoCAM PRIVATE ${OpenCV_LIBS} )


