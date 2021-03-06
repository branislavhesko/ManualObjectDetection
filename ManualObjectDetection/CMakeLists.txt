cmake_minimum_required(VERSION 3.5)
project(ManualObjectDetection)

IF (WIN32)
set(OpenCV_DIR  "C:/Users/Branislav Hesko/Documents/git/opencv-4.1.0/build")
ELSE()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lstdc++fs")
ENDIF()

find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
    message("Opencv has been found!")
endif()
# set(OpenCV_FOUND 1)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

SET (CMAKE_MODULE_LINKER_FLAGS ${CMAKE_MODULE_LINKER_FLAGS_INIT} $ENV{LDFLAGS}
     CACHE STRING "Flags used by the linker during the creation of modules.")

include_directories(${OpenCV_DIR})

set(SOURCE_FILES ManualObjectDetection.cpp include/Application.h src/Application.cpp
        src/ClassLoader.cpp include/ClassLoader.h include/cvui.h include/LoadImagesFromVideo.h src/LoadImagesFromVideo.cpp include/mouseCallback.h
        src/pch.cpp include/pch.h src/Writer.cpp include/Writer.h src/LoadImagesFromDirectory.cpp include/LoadImagesFromDirectory.h src/LoadImages.cpp include/LoadImages.h)
add_executable(ManualObjectDetection ${SOURCE_FILES})

target_link_libraries(ManualObjectDetection ${OpenCV_LIBS})

if (NOT WIN32)
target_link_libraries(ManualObjectDetection /usr/lib/gcc/x86_64-linux-gnu/8/libstdc++fs.a)
endif()