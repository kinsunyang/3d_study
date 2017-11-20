cmake_minimum_required(VERSION 3.4)
project (renderer)
#sub_directories
message(STATUS ${PROJECT_SOURCE_DIR})
message(STATUS ${PROJECT_BINARY_DIR})
message(STATUS ${CMAKE_SYSTEM_NAME})

include_directories(${PROJECT_SOURCE_DIR})
set(SRC common/log.cpp	\ 
	common/utils.cpp	\ 
	renderer.cpp	\ 	
	command_buffer.cpp	\ 
	app.cpp	
	)
set(OPENGL opengl/gl_device_context.cpp \ 
	opengl/gl_render_context.cpp 	\ 
	opengl/gl_renderer.cpp
	)
set(TEST test.cpp)

set(LIBS "")
if(WIN32)
	find_library(result opengl32)
	message(STATUS ${result})
	if(result)
		list(APPEND LIBS ${result})
	endif(result)
endif(WIN32)
if(WIN32)
	set(entry win32/main.cpp) 
	list(APPEND OPENGL win32/wgl_context.cpp)
	message(STATUS ${OPENGL})
	message(STATUS ${LIBS})
	add_definitions(-DOS_WINDOWS -D_CRT_SECURE_NO_WARNINGS)
elseif(Darwin)
endif(WIN32)

add_executable(renderer ${entry} ${SRC} ${OPENGL} ${TEST} )
target_link_libraries(renderer ${LIBS})

if( ${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	message(STATUS "--------hello world----------")
endif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
