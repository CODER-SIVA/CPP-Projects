# CPP-Projects

A collection of C/C++ and Rust programming examples and projects.

## Projects

### 1. Memory Allocation Example (C)

A program demonstrating how `malloc()` works in C programming, including:
- Basic memory allocation
- Array allocation
- Memory alignment
- Proper memory management
- Address visualization

#### Building and Running
```bash
cd malloc_example
gcc -o malloc_demo malloc_demo.c
./malloc_demo
```

### 2. Number Addition (Rust)

A simple Rust program that demonstrates basic input/output operations and number addition.

#### Features
- Takes two numbers as input from the user
- Handles both integer and decimal numbers (using f64)
- Provides error handling for invalid inputs
- Displays the sum with formatted output

#### Building and Running
```bash
# Install Rust (if not installed)
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

# Run the program
cd rust_addition
cargo run
```

### 3. Basic Multiplication (Rust)

A simple Rust program that demonstrates multiplication of two numbers.

#### Features
- Takes two numbers as input from the user
- Handles both integer and decimal numbers (using f64)
- Provides error handling for invalid inputs
- Displays the product with formatted output

#### Building and Running
```bash
# Compile and run
rustc basic_multiplication.rs
./basic_multiplication
```

### 4. Matrix Multiplication (Rust)

A more advanced Rust program that demonstrates matrix multiplication.

#### Features
- Creates two matrices with user input
- Performs matrix multiplication
- Validates matrix dimensions for multiplication
- Displays the resulting matrix
- Demonstrates Rust's vector handling capabilities

#### Building and Running
```bash
# Compile and run
rustc matrix_multiplication.rs
./matrix_multiplication
```

## Repository Structure
```
.
├── malloc_example/
│   └── malloc_demo.c
├── rust_addition/
│   ├── src/
│   │   └── main.rs
│   └── Cargo.toml
├── basic_multiplication.rs
└── matrix_multiplication.rs
```
