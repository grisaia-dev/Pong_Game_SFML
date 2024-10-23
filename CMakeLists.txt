cmake_minimum_required(VERSION 3.8)
project(GAME)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")

find_package(SFML REQUIRED COMPONENTS window graphics system)

include_directories("${CMAKE_SOURCE_DIR}/include")

set("Cpp_files"
	${CMAKE_SOURCE_DIR}/src/main.cpp
	${CMAKE_SOURCE_DIR}/src/Game.cpp
	${CMAKE_SOURCE_DIR}/src/Entity.cpp
)

add_executable(${PROJECT_NAME} ${Cpp_files})

#target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-window sfml-graphics sfml-system)

if(CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
	set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
	set_property(TARGET ${PROJECT_NAME} PROPERTY EXPORT_COMPILE_COMMANDS ON)
endif()