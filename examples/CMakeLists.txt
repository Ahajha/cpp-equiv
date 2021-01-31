cmake_minimum_required(VERSION 3.14)

project(cpp-equiv-examples CXX)

include(FetchContent)
FetchContent_Declare(root SOURCE_DIR "${PROJECT_SOURCE_DIR}/..")
FetchContent_MakeAvailable(root)

# Target that runs all the examples
add_custom_target(run)

add_executable(kruskal kruskal.cpp)
target_link_libraries(kruskal PRIVATE cpp-equiv::cpp-equiv)
target_compile_features(kruskal PRIVATE cxx_std_20)

add_custom_target(
    run_kruskal
    COMMAND "$<TARGET_FILE:kruskal>"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
)
add_dependencies(run run_kruskal)
