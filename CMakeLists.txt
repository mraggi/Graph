cmake_minimum_required(VERSION 3.1)

project(Graph) 

set(CMAKE_BUILD_TYPE Release)

option(BUILD_VISUALIZER "Build visualizer (requires SFML)" ON)
option(BUILD_TESTS "Build unit tests (requires gtest)" ON)

set(BUILD_SHARED_LIBS ON)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

link_directories (${PROJECT_BINARY_DIR})
include_directories(graph)
include_directories(graph/utils)

# Add cpp files that have to do with graphs here
add_library(graph graph/Graph.cpp
				  graph/CommonGraphs.cpp
				  graph/MinSpanningTree.cpp)

if (${BUILD_TESTS})
	find_package(GTest REQUIRED)
	find_package(Threads REQUIRED)
	enable_testing()
	include_directories(${GTEST_INCLUDE_DIRS})
	set(PROJECT_TEST_NAME graph_test)
	
	# Add test source files here
	add_executable(${PROJECT_TEST_NAME} tests/main.cpp 
										tests/basic_tests.cpp)
	
	target_link_libraries(${PROJECT_TEST_NAME} ${GTEST_BOTH_LIBRARIES} Threads::Threads graph)
	add_test(AllTests ${PROJECT_TEST_NAME})
endif()

add_executable(playground main.cpp)
target_link_libraries(playground graph)

if (${BUILD_VISUALIZER})
# 	find_package(SFML REQUIRED)
	add_definitions(-DUSE_SFML)
	
	file(GLOB GEOMETRY_FILES visualizer/Geometry/*.cpp)
	add_library(geometry ${GEOMETRY_FILES})
	
	add_executable(visualizer 	visualizer/main.cpp
								visualizer/GUIPanel.cpp
								visualizer/RichText.cpp
								visualizer/GraphApp.cpp
								visualizer/PhysicalGraph.cpp)
								
	target_link_libraries(visualizer graph geometry sfml-window sfml-graphics sfml-system)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/SourceCodePro-Regular.ttf ${CMAKE_CURRENT_BINARY_DIR}/font-mono.ttf COPYONLY)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Lato-Medium.ttf ${CMAKE_CURRENT_BINARY_DIR}/font.ttf COPYONLY)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/NotoSerif-Regular.ttf ${CMAKE_CURRENT_BINARY_DIR}/font-serif.ttf COPYONLY)
endif()
