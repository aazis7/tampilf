#!/bin/sh

# Compiler and flags
CC=gcc
CFLAGS="-Wall -Wextra"

# Source, header, object files, static and dynamic libraries, and binary
SOURCE="src/tampilf.c src/pindaif.c"
HEADER="src/tampilf.h src/pindaif.h"
OBJECT="build/tampilf.o"
LIBRARY="build/libtampilf.a"    # Static library file name
LIBRARY_SO="build/libtampilf.so" # Dynamic library file name (optional)
BIN="bin/tampilf"                # Executable binary name

# Installation locations for library and headers
PREFIX_LIB="/usr/lib" # Set your desired location (e.g., $PREFIX)
PREFIX_INCLUDE="/usr/include" # Set your desired location (e.g., $PREFIX)

# Create necessary directories if they don't exist
mkdir -p build bin

# Compile source code into object files
echo "Compiling $SOURCE..."
$CC $CFLAGS -c $SOURCE -o $OBJECT

# Create static library
echo "Creating static library..."
ar rcs $LIBRARY $OBJECT

# Create the executable program
echo "Creating executable..."
$CC $CFLAGS $OBJECT -o $BIN

# Create dynamic library (optional)
echo "Creating shared library..."
$CC $CFLAGS -shared -o $LIBRARY_SO $SOURCE

# Installation target: Install the library and headers
install() {
    echo "Installing library and headers..."
    # Copy static library to system's library folder
    cp $LIBRARY $PREFIX_LIB
    # If you also want to install the dynamic library, copy it here as well
    cp $LIBRARY_SO $PREFIX_LIB
    # Create the destination directory for headers
    mkdir -p $PREFIX_INCLUDE
    # Copy header file to system's include folder
    cp $HEADER $PREFIX_INCLUDE
}

# Clean up generated files (object files, binaries, libraries)
clean() {
    echo "Cleaning up generated files..."
    rm -rf build/* bin/*
}

# Handle command-line arguments
case "$1" in
    install) install ;;
    clean) clean ;;
    *) echo "Usage: $0 {install|clean}" ;;
esac
