# Compiler and compilation flags
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra
BUILD_DIR := build
LDFLAGS := -L$(BUILD_DIR) -llogger

# Directories
SRC_DIR := src
INCLUDE_DIRS := src external/logger  # Add submodule headers path here
WWW_DIR := www
TESTS_DIR := tests
SUBMODULE_DIR:=external/logger

# Source files and object files
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Library name
LIBRARY_NAME := libcappuccin.a

# Library and submodule targets
SUBMODULE_LIB := $(BUILD_DIR)/liblogger.so  # Assuming the .so file is named liblogger.so

# Default target
all: $(BUILD_DIR) $(SUBMODULE_LIB) $(OBJECTS) $(LIBRARY_NAME) www_files tests

# Create the build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build the submodule library
$(SUBMODULE_LIB):
	cd $(SUBMODULE_DIR) && $(MAKE)  # Run `make` in the submodule directory
	cp $(SUBMODULE_DIR)/liblogger.so $(BUILD_DIR)  # Copy the built .so file to the build directory

# Build the static library (if needed)
$(LIBRARY_NAME): $(OBJECTS)
	ar rcs $@ $(OBJECTS)

# Compile the source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(foreach dir,$(INCLUDE_DIRS),-I$(dir)) -c $< -o $@

# Target to copy static files to the build directory
www_files:
	cp -r $(WWW_DIR) $(BUILD_DIR)/

# Build and run the tests
tests: $(BUILD_DIR) $(OBJECTS) $(TESTS_DIR)/*.cpp
	$(CXX) $(CXXFLAGS) $(foreach dir,$(INCLUDE_DIRS),-I$(dir)) -I$(TESTS_DIR) $(TESTS_DIR)/*.cpp $(OBJECTS) $(LDFLAGS) -o $(BUILD_DIR)/tests
	LD_LIBRARY_PATH=$(BUILD_DIR) ./$(BUILD_DIR)/tests

# Clean build files
clean:
	cd $(SUBMODULE_DIR) && $(MAKE) clean
	rm -rf $(BUILD_DIR) $(LIBRARY_NAME)

