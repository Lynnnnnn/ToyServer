cmake_minimum_required(VERSION 3.8)
project(ToyServer)

set(CMAKE_CXX_STANDARD 11)
set(BOOST_ROOT "/usr/local/Cellar/boost/1.66.0")
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

aux_source_directory(. DIR_SRCS)
add_executable(ToyServer ${DIR_SRCS})

target_link_libraries(ToyServer boost_system)