cmake_minimum_required(VERSION 3.16)
project(roguelike)
set(CMAKE_CXX_STANDARD 17)

set(PRODUCTION_BUILD OFF CACHE BOOL "Make this a production build" FORCE)

if(MSVC) 
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
add_compile_options(/arch:AVX2) #make sure SIMD optimizations take place
	add_compile_options(-mavx2 -mfma)
endif()


set(RAYLIB_BUILD_SHARED OFF CACHE BOOL "Build Raylib as static libraries" CMAKE_FASTBUILD_FORCE_RESPONSE_FILE)
add_subdirectory(thirdparty/raylib)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}")

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 17)



if(PRODUCTION_BUILD)

	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") 


	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1 NDEBUG) 

else()

	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0) 

endif()

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES}  "src/gameLayer/helpers.h" "src/gameLayer/helpers.cpp")


if(MSVC) 

	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)

	if(PRODUCTION_BUILD)
	
		set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") #no console
	endif()

elseif(MINGW) 
	if(PRODUCTION_BUILD)
	
		target_link_options("${CMAKE_PROJECT_NAME}" PRIVATE
			-mwindows
		)
	endif()

elseif(APPLE OR UNIX) 
	if(PRODUCTION_BUILD)
		target_link_options("${CMAKE_PROJECT_NAME}" PRIVATE -s)
	endif()
endif()


target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/gameLayer")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/platform")
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE raylib)



