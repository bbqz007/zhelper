cmake_minimum_required(VERSION 3.12)

project(hiredispp-sample)
set(BOOST_INCLUDEDIR /usr/include/boost169)
set(BOOST_LIBRARYDIR /usr/lib64/boost169)

find_package(Boost 1.69 EXACT COMPONENTS program_options system serialization)
include_directories(.
				${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
link_libraries(${Boost_LIBRARIES} -lhiredis -lev)
add_executable(hiex async_example.cpp
					hiredispp.cpp)
add_executable(hiex11 async_example_cpp11.cpp
					hiredispp.cpp
					hiredispp.h
					hiredispp_async.h)

