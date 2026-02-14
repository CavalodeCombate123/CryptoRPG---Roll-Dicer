cmake_minimum_required(VERSION 3.16)

project(CryptoRPG VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

qt_add_executable(CryptoRPG
    MANUAL_FINALIZATION

    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    diceengine.cpp
    diceengine.h

    roomserver.cpp
    roomserver.h
    roomclient.cpp
    roomclient.h
    roomprotocol.h

    resource.qrc
    style.qss
    startwindow.h startwindow.cpp startwindow.ui
    solowindow.h solowindow.cpp solowindow.ui
    hostsetupwindow.h hostsetupwindow.cpp hostsetupwindow.ui
    joinsetupwindow.h joinsetupwindow.cpp joinsetupwindow.ui
    theme.h
)

target_link_libraries(CryptoRPG PRIVATE
    Qt6::Widgets
    Qt6::Network
)

set_target_properties(CryptoRPG PROPERTIES
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CryptoRPG
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(CryptoRPG)
