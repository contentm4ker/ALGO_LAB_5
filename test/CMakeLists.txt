set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

include_directories("../include")
include_directories("../googletest/googletest/include")

find_library(GTEST
    NAMES "gtest"
    PATHS ${PROJECT_SOURCE_DIR}/googletest/googletest/build
    NO_DEFAULT_PATH
)

add_executable(example
    example.cpp
)

target_link_libraries(example ${GTEST} pthread)