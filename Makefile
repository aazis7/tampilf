CC = gcc
CFLAGS = -Wall -Wextra
SOURCE = src/tampilf.c
HEADER = src/tampilf.h
OBJECT = build/tampilf.o
LIBRARY = build/libtampilf.a  # Static library file name
LIBRARY_SO = build/libtampilf.so  # Dynamic library file name (optional)
BIN = bin/tampilf
PREFIX_LIB = /data/data/com.termux/files/usr/lib  # Set your desired location (e.g., $PREFIX)
PREFIX_INCLUDE = /data/data/com.termux/files/usr/include  # Set your desired location (e.g., $PREFIX)

# Default target: build both the library and the program
all: $(LIBRARY) $(LIBRARY_SO) $(BIN)

# Compile the source code into object files
$(OBJECT): $(SOURCE) $(HEADER)
	$(CC) $(CFLAGS) -c $(SOURCE) -o $(OBJECT)

# Create the static library
$(LIBRARY): $(OBJECT)
	ar rcs $(LIBRARY) $(OBJECT)

# Create the executable program
$(BIN): $(OBJECT)
	$(CC) $(CFLAGS) $(OBJECT) -o $(BIN)

# Create the dynamic library (optional)
$(LIBRARY_SO): $(SOURCE)
	$(CC) $(CFLAGS) -shared -o $(LIBRARY_SO) $(SOURCE)

# Installation target: Install the library and headers
install: $(LIBRARY)
	# Copy the static library to the system's library folder
	cp $(LIBRARY) $(PREFIX)
	# If you also want to install a dynamic library, copy it here as well
	cp $(LIBRARY_SO) $(PREFIX)
	# Create the destination directory for headers
	mkdir -p $(PREFIX_INCLUDE)
	# Copy the header file to the system's include folder
	cp $(HEADER) $(PREFIX_INCLUDE)

# Clean up generated files (object files, binaries, libraries)
clean:
	rm -rf build/* && rm -rf bin/*
