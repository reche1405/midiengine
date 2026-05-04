cmake_minimum_required(VERSION 3.23)
set(CMAKE_TOOLCHAIN_FILE "C:/Users/reche/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(midiengine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(SOURCE_FILES
    ./include/midiengine.h

    ./include/backends/backendfactory.h
    ./include/backends/windows/midiservicebackend.h
    ./include/backends/windows/winmmbackend.h
    ./include/backends/midibackend.h

    ./include/common/listener.h
    ./include/common/midiconfig.h
    ./include/common/midiendpoint.h
    ./include/common/midievent.h
    ./include/common/midiprocessor.h
    ./include/common/midiqueue.h

    ./include/router/route.h
    ./include/router/router.h


    ./src/main.cpp
    ./src/midiengine.cpp

    ./src/common/midievent.cpp
)
if(WIN32)
find_package(microsoft-windows-devices-midi2 CONFIG REQUIRED)
endif(WIN32)

add_executable(MIDI_ENGINE ${SOURCE_FILES})
if(WIN32)
   target_link_libraries(MIDI_ENGINE PRIVATE
        windowsapp.lib   # Provides WinRT activation functions
        winmm.lib
    )

    target_include_directories(MIDI_ENGINE PRIVATE

        ${CMAKE_CURRENT_BINARY_DIR}/vcpkg_installed/x64-windows/include
    )
endif(WIN32)

target_compile_features(MIDI_ENGINE PRIVATE cxx_std_20)