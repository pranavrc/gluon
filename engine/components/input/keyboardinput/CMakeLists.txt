cmake_minimum_required(VERSION 2.8)

if(NOT GLUON_BUILD_ALL)
    find_package(GluonInput REQUIRED)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GLUON_INPUT_INCLUDES})

set(keyboardinputcomponent_SRCS
    keyboardinputcomponent.cpp
)

qt4_automoc(${keyboardinputcomponent_SRCS})
add_library(gluon_component_keyboardinput SHARED ${keyboardinputcomponent_SRCS})

if(GLUON_BUILD_ALL)
    add_dependencies(gluon_component_keyboardinput GluonEngine GluonInput)
endif()

set_target_properties(gluon_component_keyboardinput PROPERTIES VERSION ${GLUON_VERSION_STRING} SOVERSION ${GLUON_VERSION_STRING} DEFINE_SYMBOL MAKE_GLUON_COMPONENT_KEYBOARDINPUT_LIB)
target_link_libraries(gluon_component_keyboardinput GluonEngine ${GLUON_INPUT_LIBS})

install(
    TARGETS
    gluon_component_keyboardinput
    DESTINATION
    ${LIB_INSTALL_DIR}/gluon
)
