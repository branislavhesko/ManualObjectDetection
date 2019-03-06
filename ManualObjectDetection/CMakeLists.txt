cmake_minimum_required(VERSION 3.5)
project(ManualObjectDetection)


find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
    message("Opencv has been found!")
endif()
# set(OpenCV_FOUND 1)
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lstdc++fs")

SET (CMAKE_MODULE_LINKER_FLAGS ${CMAKE_MODULE_LINKER_FLAGS_INIT} $ENV{LDFLAGS}
     CACHE STRING "Flags used by the linker during the creation of modules.")

include_directories(${OpenCV_DIR})

set(SOURCE_FILES ManualObjectDetection.cpp Application.h Application.cpp
        ClassLoader.cpp ClassLoader.h cvui.h FrameLoader.h FrameLoader.cpp mouseCallback.h
        pch.cpp pch.h Writer.cpp Writer.h)
add_executable(ManualObjectDetection ${SOURCE_FILES})

target_link_libraries(ManualObjectDetection ${OpenCV_LIBS} )
target_link_libraries(ManualObjectDetection /usr/lib/gcc/x86_64-linux-gnu/8/libstdc++fs.a)
