cmake_minimum_required(VERSION 3.14)

project(
    cpp-equiv
    VERSION 0.0.1
    DESCRIPTION "A C++20 equivalence relation library"
    HOMEPAGE_URL "https://github.com/Ahajha/cpp-equiv"
    LANGUAGES CXX
)

# ---- Warning guard ----

# Protect dependents from this project's warnings if the guard isn't disabled
set(cpp-equiv_warning_guard SYSTEM)
if(cpp-equiv_INCLUDE_WITHOUT_SYSTEM)
  set(cpp-equiv_warning_guard "")
endif()

# ---- Declare library ----

add_library(cpp-equiv INTERFACE)
add_library(cpp-equiv::cpp-equiv ALIAS cpp-equiv)

target_include_directories(
    cpp-equiv
    ${cpp-equiv_warning_guard}
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(cpp-equiv INTERFACE cxx_std_20)

# ---- Install ----

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(cpp-equiv_include_directory "${CMAKE_INSTALL_INCLUDEDIR}/cpp-equiv")

install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
    DESTINATION "${cpp-equiv_include_directory}"
    COMPONENT cpp-equiv_Development
)

install(
    TARGETS cpp-equiv
    EXPORT cpp-equiv-targets
    INCLUDES DESTINATION "${cpp-equiv_include_directory}"
)

write_basic_package_version_file(
    cpp-equiv-config-version.cmake
    COMPATIBILITY SameMajorVersion
    ARCH_INDEPENDENT
)

set(cpp-equiv_install_cmakedir "${CMAKE_INSTALL_LIBDIR}/cmake/cpp-equiv")

install(
    FILES "${PROJECT_BINARY_DIR}/cpp-equiv-config-version.cmake"
    DESTINATION "${cpp-equiv_install_cmakedir}"
    COMPONENT cpp-equiv_Development
)

install(
    EXPORT cpp-equiv-targets
    FILE cpp-equiv-config.cmake
    NAMESPACE cpp-equiv::
    DESTINATION "${cpp-equiv_install_cmakedir}"
    COMPONENT cpp-equiv_Development
)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  include(CPack)
endif()
