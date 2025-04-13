
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
