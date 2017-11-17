cmake_minimum_required(VERSION 3.4)
project (renderer)
#sub_directories
message(STATUS ${PROJECT_SOURCE_DIR})
message(STATUS ${PROJECT_BINARY_DIR})
message(STATUS ${CMAKE_SYSTEM_NAME})

include_directories(${PROJECT_SOURCE_DIR})
set(SRC common/log.cpp
	
	)
if(WIN32)
	set(entry win32/main.cpp) 
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
elseif(Darwin)
endif(WIN32)

add_executable(renderer ${entry} ${SRC})

if( ${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	message(STATUS "--------hello world----------")
endif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
