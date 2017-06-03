cmake_minimum_required (VERSION 2.6)
project(datatoolkit)

message(STATUS "CMAKE_SYSTEM_NAME          = ${CMAKE_SYSTEM_NAME}"         )
message(STATUS "CMAKE_CXX_COMPILER_ID      = ${CMAKE_CXX_COMPILER_ID}"     )
message(STATUS "CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "CMAKE_COMPILER_IS_GNUCXX   = ${CMAKE_COMPILER_IS_GNUCXX}"  )

find_package(Matlab COMPONENTS MX_LIBRARY ENG_LIBRARY)

include_directories(SYSTEM "${Matlab_INCLUDE_DIRS}")
add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 11)
target_link_libraries(main ${Matlab_LIBRARIES} mat)
message("matlab: ${Matlab_MX_LIBRARY}")
