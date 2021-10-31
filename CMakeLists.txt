# CMakeList.txt : CMake project for CPPBank, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CPPBank" VERSION 1.0.0)


# Add source to this project's executable.
add_executable (CPPBank CPPBank.cpp CPPBank.h
						"utilities/src/display.cpp"
 "utilities/inc/user.h" "utilities/src/user.cpp" 
 "utilities/inc/fileIO.h" "utilities/src/fileIO.cpp" 
 "utilities/inc/admin.h" "utilities/src/admin.cpp")

target_include_directories(CPPBank PUBLIC 
	${CMAKE_SOURCE_DIR}/utilities/inc
)


# TODO: Add tests and install targets if needed.
