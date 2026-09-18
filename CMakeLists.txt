cmake_minimum_required(VERSION 3.28)
project(librkg)

# Compiler and flags
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Flags
set(COMMON_CXX_FLAGS
        -fshort-wchar
        -Wall
        -Werror
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
        -Wsign-conversion
        -Wold-style-cast
        -Wcast-align
        -Wuseless-cast
        -Wdouble-promotion
        -Wsuggest-override
)

# Source files
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/source/*.cpp"
)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/tests/*.cpp"
)

add_library(librkg STATIC ${SOURCE_FILES})
set_target_properties(librkg PROPERTIES OUTPUT_NAME "rkg")
target_include_directories(librkg PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_compile_options(librkg PRIVATE ${COMMON_CXX_FLAGS})
target_compile_features(librkg PUBLIC cxx_std_23)

add_executable(rkg ${TEST_SOURCES})
target_link_libraries(rkg PRIVATE librkg)
target_compile_options(rkg PRIVATE ${COMMON_CXX_FLAGS})