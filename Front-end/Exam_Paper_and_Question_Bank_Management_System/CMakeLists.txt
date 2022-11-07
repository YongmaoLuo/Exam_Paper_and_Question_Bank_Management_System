cmake_minimum_required(VERSION 3.5)

project(Exam_Paper_and_Question_Bank_Management_System VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        admindialog.cpp
        admindialog.h
        logindialog.cpp
        logindialog.h
        ownInterface.h
        paperproductiondialog.cpp
        paperproductiondialog.h
        rulemakerdialog.cpp
        rulemakerdialog.h
        ui_admindialog.h
        ui_logindialog.h
        ui_mainwindow.h
        ui_paperproductiondialog.h
        ui_rulemakerdialog.h
        ui_signupdialog.h
        tcpclientsocket.h
        tcpclientsocket.cpp

        admindialog.ui
        logindialog.ui
        paperproductiondialog.ui
        rulemakerdialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Exam_Paper_and_Question_Bank_Management_System
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Exam_Paper_and_Question_Bank_Management_System APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Exam_Paper_and_Question_Bank_Management_System SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Exam_Paper_and_Question_Bank_Management_System
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Exam_Paper_and_Question_Bank_Management_System PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Exam_Paper_and_Question_Bank_Management_System PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Exam_Paper_and_Question_Bank_Management_System
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Exam_Paper_and_Question_Bank_Management_System)
endif()
