cmake_minimum_required(VERSION 3.14)
project(IpScanner)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Concurrent Network)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(UI_FILES
    IpScannerDialog.ui
)

set(SOURCE_FILES
    main.cpp
    MainWindow.cpp
    IpScannerDialog.cpp
    IpScannerWorker.cpp
)

set(HEADER_FILES
    MainWindow.h
    IpScannerDialog.h
    IpScannerWorker.h
)

add_executable(IpScanner ${SOURCE_FILES} ${HEADER_FILES} ${UI_FILES})

target_link_libraries(IpScanner Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network Qt6::Concurrent)
