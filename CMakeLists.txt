# Minimum cmake version
cmake_minimum_required (VERSION 3.0.0)

set (SEQAN_INCLUDE_PATH "${CMAKE_CURRENT_LIST_DIR}/ThirdParty/seqan/include")

project (inputModule C CXX)

find_package (ZLIB)

set (SeqAn_DIR "ThirdParty/seqan/share/cmake/seqan")

find_package (SeqAn REQUIRED)

set(SEQAN_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/ThirdParty/seqan/include")

include_directories (${SEQAN_INCLUDE_DIRS})

add_definitions (${SEQAN_DEFINITIONS})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SEQAN_CXX_FLAGS}")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14 -fPIC -fopenmp -W -Wall -pedantic")

set(LDFLAGS "-lrt -lpthread -lbz2 -lz")

file(GLOB SOURCES "src/*.cpp" "main.cpp")

include_directories("include")

add_executable(inputModule ${SOURCES})

target_link_libraries (inputModule ${SEQAN_LIBRARIES})
