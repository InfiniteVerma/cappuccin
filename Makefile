# Compiler and compilation flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra
LDFLAGS :=

# Directories
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
WWW_DIR := www

# Source files and object files
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Executable name
EXECUTABLE := serv 

# Default target
all: $(BUILD_DIR) $(EXECUTABLE) www_files

# Create the build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

# Compile the source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Target to copy static files to the build directory
www_files:
	cp -r $(WWW_DIR) $(BUILD_DIR)/

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)

