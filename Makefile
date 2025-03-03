# Common Makefile for C/C++ and Rust Projects
# Author: CODER-SIVA
# Date: March 3, 2025

# Compiler settings
CC = gcc
CXX = g++
RUSTC = rustc

# Compiler flags
CFLAGS = -Wall -Wextra -g
CXXFLAGS = -Wall -Wextra -g -std=c++11

# Directories
MALLOC_DIR = malloc_example
OOP_DIR = oop_concepts
RUST_ADD_DIR = rust_addition

# Targets
.PHONY: all clean c_examples cpp_examples rust_examples help

# Default target
all: c_examples cpp_examples rust_examples

# C Examples
c_examples: malloc_demo

malloc_demo:
	@echo "Building malloc example..."
	@$(CC) $(CFLAGS) -o $(MALLOC_DIR)/malloc_demo $(MALLOC_DIR)/malloc_demo.c
	@echo "malloc_demo built successfully!"

# C++ Examples
cpp_examples:
	@echo "Building C++ examples..."
	@if [ -d "$(OOP_DIR)" ]; then \
		$(CXX) $(CXXFLAGS) -o $(OOP_DIR)/oop_demo $(OOP_DIR)/main.cpp 2>/dev/null || echo "OOP examples skipped"; \
	fi
	@echo "C++ examples built!"

# Rust Examples
rust_examples: basic_multiplication matrix_multiplication rust_addition

basic_multiplication:
	@echo "Building basic multiplication example..."
	@$(RUSTC) basic_multiplication.rs
	@echo "basic_multiplication built successfully!"

matrix_multiplication:
	@echo "Building matrix multiplication example..."
	@$(RUSTC) matrix_multiplication.rs
	@echo "matrix_multiplication built successfully!"

rust_addition:
	@echo "Building rust addition example..."
	@if [ -d "$(RUST_ADD_DIR)" ]; then \
		cd $(RUST_ADD_DIR) && cargo build --quiet 2>/dev/null || echo "Rust addition skipped"; \
	fi
	@echo "Rust examples built!"

# Run targets
run_malloc:
	@echo "Running malloc example..."
	@$(MALLOC_DIR)/malloc_demo

run_basic_mult:
	@echo "Running basic multiplication example..."
	@./basic_multiplication

run_matrix_mult:
	@echo "Running matrix multiplication example..."
	@./matrix_multiplication

run_rust_add:
	@echo "Running rust addition example..."
	@if [ -d "$(RUST_ADD_DIR)" ]; then \
		cd $(RUST_ADD_DIR) && cargo run --quiet 2>/dev/null || echo "Rust addition not available"; \
	else \
		echo "Rust addition directory not found"; \
	fi

# Clean up
clean:
	@echo "Cleaning up..."
	@rm -f $(MALLOC_DIR)/malloc_demo
	@rm -f $(OOP_DIR)/oop_demo
	@rm -f basic_multiplication
	@rm -f matrix_multiplication
	@if [ -d "$(RUST_ADD_DIR)" ]; then \
		cd $(RUST_ADD_DIR) && cargo clean --quiet 2>/dev/null; \
	fi
	@echo "Clean up complete!"

# Help
help:
	@echo "Available targets:"
	@echo "  all            - Build all examples (default)"
	@echo "  c_examples     - Build C examples"
	@echo "  cpp_examples   - Build C++ examples"
	@echo "  rust_examples  - Build Rust examples"
	@echo "  malloc_demo    - Build malloc example"
	@echo "  basic_multiplication - Build basic multiplication Rust example"
	@echo "  matrix_multiplication - Build matrix multiplication Rust example"
	@echo "  rust_addition  - Build Rust addition example"
	@echo "  run_malloc     - Run malloc example"
	@echo "  run_basic_mult - Run basic multiplication example"
	@echo "  run_matrix_mult - Run matrix multiplication example"
	@echo "  run_rust_add   - Run Rust addition example"
	@echo "  clean          - Remove all built files"
	@echo "  help           - Display this help message"
