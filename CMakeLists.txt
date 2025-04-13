cmake_minimum_required(VERSION 3.10)
project(CPP_Projects VERSION 1.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

# Define directories
set(MALLOC_DIR ${CMAKE_SOURCE_DIR}/malloc_example)
set(OOP_DIR ${CMAKE_SOURCE_DIR}/oop_concepts)
set(PROCESSES_DIR ${CMAKE_SOURCE_DIR}/processes)

# Check if directories exist
if(EXISTS ${MALLOC_DIR})
    # Add C examples
    add_executable(malloc_demo ${MALLOC_DIR}/malloc_demo.c)
endif()

if(EXISTS ${OOP_DIR})
    # Add C++ OOP examples
    if(EXISTS ${OOP_DIR}/main.cpp)
        add_executable(oop_demo ${OOP_DIR}/main.cpp)
    endif()
endif()

# Add Process examples
if(EXISTS ${PROCESSES_DIR})
    # Basic fork example
    if(EXISTS ${PROCESSES_DIR}/basic_fork.cpp)
        add_executable(basic_fork ${PROCESSES_DIR}/basic_fork.cpp)
    endif()
    
    # Fork exec example
    if(EXISTS ${PROCESSES_DIR}/fork_exec.cpp)
        add_executable(fork_exec ${PROCESSES_DIR}/fork_exec.cpp)
    endif()
    
    # vfork example
    if(EXISTS ${PROCESSES_DIR}/vfork_example.cpp)
        add_executable(vfork_example ${PROCESSES_DIR}/vfork_example.cpp)
    endif()
    
    # posix_spawn example
    if(EXISTS ${PROCESSES_DIR}/posix_spawn_example.cpp)
        add_executable(posix_spawn_example ${PROCESSES_DIR}/posix_spawn_example.cpp)
    endif()
    
    # system example
    if(EXISTS ${PROCESSES_DIR}/system_example.cpp)
        add_executable(system_example ${PROCESSES_DIR}/system_example.cpp)
    endif()
    
    # popen example
    if(EXISTS ${PROCESSES_DIR}/popen_example.cpp)
        add_executable(popen_example ${PROCESSES_DIR}/popen_example.cpp)
    endif()
    
    # clone example
    if(EXISTS ${PROCESSES_DIR}/clone_example.cpp)
        add_executable(clone_example ${PROCESSES_DIR}/clone_example.cpp)
    endif()
endif()

# Note: Rust examples are not included in CMake as they use Cargo for building
# For Rust examples, we'll need to use Cargo directly

# Install targets
install(TARGETS 
    RUNTIME DESTINATION bin
)

# Custom targets for Rust examples
add_custom_target(basic_multiplication
    COMMAND rustc ${CMAKE_SOURCE_DIR}/basic_multiplication.rs
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Building basic multiplication example..."
    VERBATIM
)

add_custom_target(matrix_multiplication
    COMMAND rustc ${CMAKE_SOURCE_DIR}/matrix_multiplication.rs
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Building matrix multiplication example..."
    VERBATIM
)

# Add a custom target for building all Rust examples
add_custom_target(rust_examples
    DEPENDS basic_multiplication matrix_multiplication
    COMMENT "Building all Rust examples..."
)

# Add a custom target for cleaning Rust examples
add_custom_target(clean_rust
    COMMAND rm -f ${CMAKE_SOURCE_DIR}/basic_multiplication ${CMAKE_SOURCE_DIR}/matrix_multiplication
    COMMENT "Cleaning Rust examples..."
    VERBATIM
)

# Add a custom target for building all examples
add_custom_target(all_examples
    DEPENDS malloc_demo oop_demo basic_fork fork_exec vfork_example posix_spawn_example system_example popen_example clone_example rust_examples
    COMMENT "Building all examples..."
)

# Add a custom target for cleaning all examples
add_custom_target(clean_all
    DEPENDS clean_rust
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMENT "Cleaning all examples..."
    VERBATIM
)

# Create a README.cmake file with instructions
file(WRITE ${CMAKE_SOURCE_DIR}/README.cmake "
# Building with CMake

This project uses CMake as its build system. Here's how to build and run the examples:

## Building

1. Create a build directory and navigate to it:
   ```
   mkdir build
   cd build
   ```

2. Configure the project:
   ```
   cmake ..
   ```

3. Build all targets:
   ```
   cmake --build .
   ```

4. Build specific targets:
   ```
   cmake --build . --target basic_fork
   cmake --build . --target fork_exec
   ```

5. Build all examples (including Rust):
   ```
   cmake --build . --target all_examples
   ```

## Running

After building, you can run the examples from the build directory:

```
./basic_fork
./fork_exec
./vfork_example
./posix_spawn_example
./system_example
./popen_example
./clone_example
```

For Rust examples, run from the project root:

```
./basic_multiplication
./matrix_multiplication
```

## Cleaning

To clean all build artifacts:
```
cmake --build . --target clean
```

To clean Rust examples:
```
cmake --build . --target clean_rust
```

To clean everything:
```
cmake --build . --target clean_all
```
")
