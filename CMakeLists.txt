cmake_minimum_required(VERSION 3.5.1)
project(shell4cpp)

add_library(shell4cpp INTERFACE)
target_include_directories(shell4cpp INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(WARNINGS "-Werror" "-Wall")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(WARNINGS "-Werror" "-Wall")
elseif(MSVC)
    set(WARNINGS "/WX" "/W4")
endif()
target_compile_options(shell4cpp INTERFACE ${WARNINGS})

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})

include(GNUInstallDirs)

set(SHELL4CPP_INC_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}")
set(SHELL4CPP_CMAKE_CONFIG_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/shell4cpp/cmake")
set(SHELL4CPP_ADDITIONAL_FILES_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/shell4cpp")

# Install target
install(TARGETS shell4cpp EXPORT shell4cppTargets
  INCLUDES DESTINATION ${SHELL4CPP_INC_INSTALL_DIR}
)

# Install headers
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
	DESTINATION ${SHELL4CPP_INC_INSTALL_DIR}
)

# Make cmake config files for all targets
install(EXPORT  shell4cppTargets
  DESTINATION ${SHELL4CPP_CMAKE_CONFIG_INSTALL_DIR}
  FILE shell4cpp-config.cmake
)

# Install readme and license
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE" "${CMAKE_CURRENT_SOURCE_DIR}/README.md"
  DESTINATION ${SHELL4CPP_ADDITIONAL_FILES_INSTALL_DIR})

endif()

if (SHELL4CPP_TESTS)
  add_subdirectory(test)
endif()
