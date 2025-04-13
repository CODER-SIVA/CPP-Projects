#!/bin/bash
# Build script for CPP_Projects
# Author: CODER-SIVA
# Date: March 18, 2025

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Print header
echo -e "${BLUE}=======================================${NC}"
echo -e "${BLUE}   CPP_Projects Build System          ${NC}"
echo -e "${BLUE}=======================================${NC}"

# Check if CMake is installed
if ! command -v cmake &> /dev/null; then
    echo -e "${YELLOW}CMake is not installed. Would you like to install it? (y/n)${NC}"
    read -r install_cmake
    
    if [[ "$install_cmake" == "y" ]]; then
        echo -e "${GREEN}Installing CMake...${NC}"
        if command -v brew &> /dev/null; then
            brew install cmake
        else
            echo -e "${RED}Homebrew is not installed. Please install CMake manually:${NC}"
            echo "Visit https://cmake.org/download/ to download and install CMake"
            exit 1
        fi
    else
        echo -e "${YELLOW}Proceeding with alternative build method...${NC}"
        # Fallback to direct compilation
        USE_DIRECT_COMPILATION=1
    fi
fi

# Function to build C++ files
build_cpp_file() {
    local source_file=$1
    local output_name=$2
    local directory=$3
    
    echo -e "${GREEN}Building ${output_name}...${NC}"
    g++ -Wall -Wextra -g -std=c++11 -o "${directory}/${output_name}" "${directory}/${source_file}"
    echo -e "${GREEN}${output_name} built successfully!${NC}"
}

# Function to build C files
build_c_file() {
    local source_file=$1
    local output_name=$2
    local directory=$3
    
    echo -e "${GREEN}Building ${output_name}...${NC}"
    gcc -Wall -Wextra -g -o "${directory}/${output_name}" "${directory}/${source_file}"
    echo -e "${GREEN}${output_name} built successfully!${NC}"
}

# Function to build Rust files
build_rust_file() {
    local source_file=$1
    
    echo -e "${GREEN}Building ${source_file}...${NC}"
    rustc "${source_file}"
    echo -e "${GREEN}${source_file} built successfully!${NC}"
}

# Build all targets
build_all() {
    # Build C examples
    if [ -d "malloc_example" ]; then
        build_c_file "malloc_demo.c" "malloc_demo" "malloc_example"
    fi
    
    # Build C++ OOP examples
    if [ -d "oop_concepts" ] && [ -f "oop_concepts/main.cpp" ]; then
        build_cpp_file "main.cpp" "oop_demo" "oop_concepts"
    fi
    
    # Build process examples
    if [ -d "processes" ]; then
        if [ -f "processes/basic_fork.cpp" ]; then
            build_cpp_file "basic_fork.cpp" "basic_fork" "processes"
        fi
        
        if [ -f "processes/fork_exec.cpp" ]; then
            build_cpp_file "fork_exec.cpp" "fork_exec" "processes"
        fi
        
        if [ -f "processes/vfork_example.cpp" ]; then
            build_cpp_file "vfork_example.cpp" "vfork_example" "processes"
        fi
        
        if [ -f "processes/posix_spawn_example.cpp" ]; then
            build_cpp_file "posix_spawn_example.cpp" "posix_spawn_example" "processes"
        fi
        
        if [ -f "processes/system_example.cpp" ]; then
            build_cpp_file "system_example.cpp" "system_example" "processes"
        fi
        
        if [ -f "processes/popen_example.cpp" ]; then
            build_cpp_file "popen_example.cpp" "popen_example" "processes"
        fi
        
        if [ -f "processes/clone_example.cpp" ]; then
            build_cpp_file "clone_example.cpp" "clone_example" "processes"
        fi
    fi
    
    # Build Rust examples
    if [ -f "basic_multiplication.rs" ]; then
        build_rust_file "basic_multiplication.rs"
    fi
    
    if [ -f "matrix_multiplication.rs" ]; then
        build_rust_file "matrix_multiplication.rs"
    fi
}

# Clean all targets
clean_all() {
    echo -e "${GREEN}Cleaning up...${NC}"
    
    # Clean C examples
    if [ -f "malloc_example/malloc_demo" ]; then
        rm -f "malloc_example/malloc_demo"
    fi
    
    # Clean C++ OOP examples
    if [ -f "oop_concepts/oop_demo" ]; then
        rm -f "oop_concepts/oop_demo"
    fi
    
    # Clean process examples
    if [ -d "processes" ]; then
        rm -f processes/basic_fork
        rm -f processes/fork_exec
        rm -f processes/vfork_example
        rm -f processes/posix_spawn_example
        rm -f processes/system_example
        rm -f processes/popen_example
        rm -f processes/clone_example
    fi
    
    # Clean Rust examples
    rm -f basic_multiplication
    rm -f matrix_multiplication
    
    # Clean build directory
    if [ -d "build" ]; then
        rm -rf build/*
    fi
    
    echo -e "${GREEN}Clean up complete!${NC}"
}

# Parse command line arguments
if [ "$#" -eq 0 ]; then
    # No arguments, show help
    echo -e "${YELLOW}Usage: $0 [OPTION]${NC}"
    echo "Options:"
    echo "  build       Build all targets"
    echo "  clean       Clean all targets"
    echo "  cmake       Use CMake to build (if available)"
    echo "  help        Show this help message"
    exit 0
fi

case "$1" in
    build)
        if [ -z "$USE_DIRECT_COMPILATION" ] && command -v cmake &> /dev/null; then
            echo -e "${GREEN}Building with CMake...${NC}"
            mkdir -p build
            cd build
            cmake ..
            cmake --build .
        else
            echo -e "${GREEN}Building directly...${NC}"
            build_all
        fi
        ;;
    clean)
        if [ -z "$USE_DIRECT_COMPILATION" ] && command -v cmake &> /dev/null && [ -d "build" ]; then
            echo -e "${GREEN}Cleaning with CMake...${NC}"
            cd build
            cmake --build . --target clean
            cd ..
        fi
        clean_all
        ;;
    cmake)
        if command -v cmake &> /dev/null; then
            echo -e "${GREEN}Building with CMake...${NC}"
            mkdir -p build
            cd build
            cmake ..
            cmake --build .
        else
            echo -e "${RED}CMake is not installed. Please install it first.${NC}"
            exit 1
        fi
        ;;
    help)
        echo -e "${YELLOW}Usage: $0 [OPTION]${NC}"
        echo "Options:"
        echo "  build       Build all targets"
        echo "  clean       Clean all targets"
        echo "  cmake       Use CMake to build (if available)"
        echo "  help        Show this help message"
        ;;
    *)
        echo -e "${RED}Unknown option: $1${NC}"
        echo -e "${YELLOW}Usage: $0 [OPTION]${NC}"
        echo "Options:"
        echo "  build       Build all targets"
        echo "  clean       Clean all targets"
        echo "  cmake       Use CMake to build (if available)"
        echo "  help        Show this help message"
        exit 1
        ;;
esac

exit 0
