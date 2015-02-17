project(Project3Donut)
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

find_package(Qt5Xml REQUIRED)
include_directories(${Qt5Xml_INCLUDES} src/Scene)

SET(QT_USE_QTOPENGL TRUE)
# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDES} src src/ImageCreator src/Scene src/Tools src/Window)

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(-std=c++11)
ADD_DEFINITIONS(${QT_DEFINITIONS})


# Executables fail to build with Qt 5 in the default configuration
# without -fPIE. We add that here.
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
  
file(GLOB_RECURSE source_files src/*.cpp)
file(GLOB_RECURSE header_files src/*.hpp)

add_executable(${PROJECT_NAME} ${source_files} ${header_files})

find_package(OpenGL)
include_directories( ${OPENGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

target_link_libraries(${PROJECT_NAME} ${Qt5Gui_LIBRARIES} ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} Qt5::OpenGL)
target_link_libraries(${PROJECT_NAME} ${Qt5Xml_LIBRARIES})
