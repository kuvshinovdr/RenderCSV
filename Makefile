# Makefile for a clean, organized, and portable C++23 modules project

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++23 -fmodules

# --- Directory Definitions ---
# Use variables for output directories for easy configuration
BIN_DIR := bin
OBJ_DIR := obj
GCM_DIR := gcm.cache

# --- Target Definition ---
# The final executable will be placed in the BIN_DIR
TARGET := $(BIN_DIR)/my_program

# --- Automatic Source File Discovery ---
MAIN_SRC := main.cpp
MODULE_INTERFACES := $(wildcard *.cppm)
MODULE_IMPLS := $(wildcard *.cpp)
MODULE_IMPLS := $(filter-out $(MAIN_SRC), $(MODULE_IMPLS))

# --- Object and Module File Name Generation ---
# Prepend the OBJ_DIR to all object file paths
MAIN_OBJ := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(MAIN_SRC))
MODULE_IF_OBJS := $(patsubst %.cppm,$(OBJ_DIR)/%.if.o,$(MODULE_INTERFACES))
MODULE_IMPL_OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.impl.o,$(MODULE_IMPLS))
STD_OBJ := $(OBJ_DIR)/std.o

# A list of all object files that need to be linked
OBJS := $(MAIN_OBJ) $(MODULE_IF_OBJS) $(MODULE_IMPL_OBJS)

# Prepend the GCM_DIR to all compiled module interface file paths
MODULE_GCM_FILES := $(patsubst %.cppm,$(GCM_DIR)/%.gcm,$(MODULE_INTERFACES))
STD_GCM_FILE := $(GCM_DIR)/std.gcm

# --- Build Rules ---

.PHONY: all clean

# Default target
all: $(TARGET)

# Rule to link the final executable
# Depends on all object files and ensures the bin directory exists
$(TARGET): $(OBJS) | $(BIN_DIR)
	@echo "==> Linking executable: $@"
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to compile the main source file
# Depends on its source and the .gcm files it imports
$(OBJ_DIR)/%.o: %.cpp $(MODULE_GCM_FILES) $(STD_GCM_FILE) | $(OBJ_DIR)
	@echo "==> Compiling main source: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile module interface files (*.cppm)
# This multi-target rule creates a .gcm file and a .if.o object file
# from a single .cppm source file.
$(GCM_DIR)/%.gcm $(OBJ_DIR)/%.if.o: %.cppm | $(GCM_DIR) $(OBJ_DIR)
	@echo "==> Compiling module interface: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $(patsubst %.cppm,$(OBJ_DIR)/%.if.o,$<)

# Rule to compile module implementation files (*.cpp)
# Depends on its source and its corresponding .gcm file
$(OBJ_DIR)/%.impl.o: %.cpp $(GCM_DIR)/%.gcm | $(OBJ_DIR)
	@echo "==> Compiling module implementation: $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Portable rule for building the 'std' module interface
# Creates the std.gcm file and a std.o object file
$(STD_GCM_FILE): | $(GCM_DIR) $(OBJ_DIR)
	@echo "==> Compiling the 'std' module interface (this may take a moment)..."
	$(CXX) $(CXXFLAGS) -fsearch-include-path -c bits/std.cc -o $(STD_OBJ)
	@echo "==> 'std' module compiled successfully."

# --- Directory Creation and Cleanup ---

# Rule to create all necessary directories
# This is an order-only prerequisite for rules that need them
$(BIN_DIR) $(OBJ_DIR) $(GCM_DIR):
	@mkdir -p $@

# Rule to clean up all generated files and directories
clean:
	@echo "==> Cleaning up build artifacts..."
	rm -rf $(BIN_DIR) $(OBJ_DIR) $(GCM_DIR)
	@echo "==> Done."