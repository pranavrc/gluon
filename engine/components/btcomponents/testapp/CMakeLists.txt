project(btcomponents_testapp)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_INSTALL_PREFIX}/share/kde4/apps/cmake/modules/)

if(NOT GLUON_BUILD_ALL)
    find_package(Qt4 REQUIRED)
    find_package(GluonCore REQUIRED)
    find_package(GluonEngine REQUIRED)
endif()

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_SOURCE_DIR} ${GLUON_ENGINE_INCLUDES} ${GLUON_CORE_INCLUDES})

set(btcomponents_testapp_SRCS btcomponents-testapp.cpp main.cpp)
qt4_automoc(${btcomponents_testapp_SRCS})
add_executable(btcomponents_testapp ${btcomponents_testapp_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(btcomponents_testapp GluonEngine GluonCore)
endif()

target_link_libraries(btcomponents_testapp GluonCore GluonEngine ${GLUON_CORE_LIBS} ${GLUON_ENGINE_LIBS} ${QT_QTCORE_LIBRARY})
