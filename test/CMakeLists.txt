cmake_minimum_required(VERSION 3.14)

project(cpp-equiv-tests CXX)

# ---- Dependencies ----

set(cpp-equiv_INCLUDE_WITHOUT_SYSTEM YES CACHE INTERNAL "")

include(FetchContent)
FetchContent_Declare(root SOURCE_DIR "${PROJECT_SOURCE_DIR}/..")
FetchContent_MakeAvailable(root)

# ---- Test ----

if(MSVC)
  target_compile_options(cpp-equiv INTERFACE /W4 /permissive-)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(cpp-equiv INTERFACE -Wall -Wextra -Wpedantic)
else()
  message(AUTHOR_WARNING "Unknown compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

enable_testing()

foreach(name IN ITEMS er hash store)
  set(target "test_${name}")
  add_executable("${target}" "${target}.cpp")
  target_link_libraries("${target}" PRIVATE cpp-equiv::cpp-equiv)
  target_compile_features("${target}" PRIVATE cxx_std_20)
  add_test(NAME "${name}" COMMAND "${target}")
endforeach()
