cmake_minimum_required(VERSION 3.24)

project(run LANGUAGES CXX)

# C++ settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )

include(FetchContent)

FetchContent_Declare(
  tensorstore
  URL "https://github.com/google/tensorstore/archive/refs/tags/v0.1.75.tar.gz"
)

FetchContent_MakeAvailable(tensorstore)

include_directories(include)

add_executable(run 
  main.cpp   
)

target_link_libraries(run PRIVATE 
  tensorstore::tensorstore 
  tensorstore::all_drivers 
)

