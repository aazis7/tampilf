# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name
project(tampilf VERSION 0.0.1)

# Set C standard to C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Define the source files
set(SOURCE_FILES
    src/tampilf.c
)

# Define the header files (optional for documentation)
set(HEADER_FILES
    src/tampilf.h
)

# Create the executable
add_executable(tampilf ${SOURCE_FILES} ${HEADER_FILES})

# Include the directories
target_include_directories(tampilf PRIVATE include)

# Set compiler flags (optional)
if(MSVC)
    # MSVC-specific settings (if needed)
else()
    # Add flags for other compilers
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
endif()

# Optional: Install target (for easy deployment)
install(TARGETS tampilf DESTINATION /usr/local/bin)

# Optional: Set up testing (if you want to add tests later)
enable_testing()
add_test(NAME tampilf_test COMMAND tampilf)

# Optional: If using external libraries or dependencies, use find_package or add_subdirectory for integration
