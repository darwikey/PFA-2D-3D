project(Model_Viewer)
cmake_minimum_required(VERSION 2.8)


  # Tell CMake to run moc when necessary:
  set(CMAKE_AUTOMOC ON)
  # As moc files are generated in the binary dir, tell CMake
  # to always look for includes there:
  set(CMAKE_INCLUDE_CURRENT_DIR ON)

FIND_PACKAGE( Qt5OpenGL REQUIRED )
IF( Qt5OpenGL_FOUND )
    MESSAGE( STATUS "Qt5 OpenGL module FOUND!" )
ELSE()
    MESSAGE( WARNING "Qt5 OpenGL module NOT FOUND!" )
ENDIF()


find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

SET(QT_USE_QTOPENGL TRUE)
  # The Qt5Widgets_INCLUDES also includes the include directories for
  # dependencies QtCore and QtGui
  include_directories(${Qt5Widgets_INCLUDES})

  # We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
  add_definitions(${Qt5Widgets_DEFINITIONS})

  # Executables fail to build with Qt 5 in the default configuration
  # without -fPIE. We add that here.
  set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
aux_source_directory(. SRC_LIST)

ADD_DEFINITIONS(${QT_DEFINITIONS})


add_executable(${PROJECT_NAME} ${SRC_LIST})


  target_link_libraries(${PROJECT_NAME} ${Qt5Gui_LIBRARIES} ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} Qt5::OpenGL )
