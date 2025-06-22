cmake_minimum_required(VERSION 3.16)

project(VideoWall VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GSTREAMER_ROOT "D:/gstreamer/1.0/msvc_x86_64")

include_directories(${GSTREAMER_ROOT}/include
                    ${GSTREAMER_ROOT}/include/gstreamer-1.0
                    ${GSTREAMER_ROOT}/include/gstreamer-1.0/gst/video
                    ${GSTREAMER_ROOT}/include/gstreamer-1.0/gst/rtsp
                    ${GSTREAMER_ROOT}/include/glib-2.0
                    ${GSTREAMER_ROOT}/lib/glib-2.0/include)
 link_directories(${GSTREAMER_ROOT}/lib)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(VideoWall
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        bus_callback.cpp
        bus_callback.h
        cameralistwidget.cpp
        cameralistwidget.h
        graphicsview.cpp
        graphicsview.h GStreamerData.h
        handlergstreamer.cpp
        handlergstreamer.h
        ibuscallback.cpp
        ibuscallback.h
        igstreamerdataprovider.cpp
        igstreamerdataprovider.h
        isettingsmanager.cpp
        isettingsmanager.h
        mainwindow.cpp
        mainwindow.h
        player.cpp
        player.h
        rtspinputdisplay.cpp
        rtspinputdisplay.h


        screenaddsettings.cpp
        screenaddsettings.h
        screenpartitionbuttons.cpp
        screenpartitionbuttons.h
        settingsmanager.cpp
        settingsmanager.h
        signaltransmitter.cpp
        signaltransmitter.h
        singletontransmitter.cpp
        singletontransmitter.h
        streamconfig.cpp
        streamconfig.h
        videoplayer.cpp
        videoplayer.h
        worksreens.cpp
        worksreens.h
        covermanager.h covermanager.cpp
        constants.h
        esckeyfilter.h esckeyfilter.cpp
        resource.qrc
        loadingwidget.h loadingwidget.cpp
        streamcontext.h streamcontext.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET VideoWall APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(VideoWall SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(VideoWall
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(VideoWall PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    gstreamer-1.0.lib
    gobject-2.0.lib
    glib-2.0.lib
    gstvideo-1.0.lib
    gstrtsp-1.0.lib
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.VideoWall)
endif()
set_target_properties(VideoWall PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS VideoWall
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(VideoWall)
endif()
