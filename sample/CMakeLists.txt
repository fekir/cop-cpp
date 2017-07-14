cmake_minimum_required(VERSION 3.2)

project(cop_sample CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(catch REQUIRED)

include_directories(SYSTEM ${CATCH_INCLUDE_DIRS})

# include_directories where cop is located
include_directories("..")

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME}
	main.cpp
	EqualityComparable.cpp
	LessThanComparable.cpp
)

