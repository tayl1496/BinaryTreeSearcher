project(Project7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

add_executable(proj7
  main.cpp
  PrecondViolatedExcep.cpp
  NotFoundException.cpp)
