# Compiler and compilation flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra
LDFLAGS :=

# Directories
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
WWW_DIR := www
TESTS_DIR := tests

# Source files and object files
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Library name
LIBRARY_NAME := libmy_http_server.a

# Default target
all: $(BUILD_DIR) $(LIBRARY_NAME) www_files tests

# Create the build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build the static library
$(LIBRARY_NAME): $(OBJECTS)
	ar rcs $@ $(OBJECTS)

# Compile the source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Target to copy static files to the build directory
www_files:
	cp -r $(WWW_DIR) $(BUILD_DIR)/

# Build and run the tests
tests: $(BUILD_DIR) $(OBJECTS) $(TESTS_DIR)/*.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -I$(TESTS_DIR) $(TESTS_DIR)/*.cpp $(OBJECTS) $(LDFLAGS) -o $(BUILD_DIR)/tests
	$(BUILD_DIR)/tests

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(LIBRARY_NAME)

