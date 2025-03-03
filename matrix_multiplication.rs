// Matrix Multiplication in Rust
use std::io::{self, Write};

// Define a type alias for a matrix
type Matrix = Vec<Vec<f64>>;

fn main() {
    println!("===== Matrix Multiplication Program =====");
    
    // Create first matrix
    println!("\nFirst Matrix (A):");
    let matrix_a = create_matrix(2, 3);
    print_matrix(&matrix_a);
    
    // Create second matrix
    println!("\nSecond Matrix (B):");
    let matrix_b = create_matrix(3, 2);
    print_matrix(&matrix_b);
    
    // Check if matrices can be multiplied
    if matrix_a[0].len() != matrix_b.len() {
        println!("Error: Cannot multiply these matrices!");
        println!("Number of columns in first matrix must equal number of rows in second matrix.");
        return;
    }
    
    // Multiply matrices
    println!("\nCalculating A × B...");
    let result = multiply_matrices(&matrix_a, &matrix_b);
    
    // Display result
    println!("\nResult Matrix (A × B):");
    print_matrix(&result);
}

// Function to create a matrix with user input
fn create_matrix(rows: usize, cols: usize) -> Matrix {
    let mut matrix = vec![vec![0.0; cols]; rows];
    
    println!("Creating a {}×{} matrix:", rows, cols);
    println!("Enter values or press Enter for default values (0.0):");
    
    for i in 0..rows {
        for j in 0..cols {
            print!("Enter value for position [{},{}]: ", i, j);
            io::stdout().flush().expect("Failed to flush stdout");
            
            let mut input = String::new();
            io::stdin()
                .read_line(&mut input)
                .expect("Failed to read input");
            
            // If input is empty (just Enter), use default value 0.0
            if input.trim().is_empty() {
                continue;
            }
            
            // Parse input
            matrix[i][j] = match input.trim().parse() {
                Ok(num) => num,
                Err(_) => {
                    println!("Invalid input! Using default value 0.0.");
                    0.0
                }
            };
        }
    }
    
    matrix
}

// Function to print a matrix
fn print_matrix(matrix: &Matrix) {
    for row in matrix {
        print!("[ ");
        for &value in row {
            print!("{:.1} ", value);
        }
        println!("]");
    }
}

// Function to multiply two matrices
fn multiply_matrices(a: &Matrix, b: &Matrix) -> Matrix {
    let a_rows = a.len();
    let a_cols = a[0].len();
    let b_cols = b[0].len();
    
    // Initialize result matrix with zeros
    let mut result = vec![vec![0.0; b_cols]; a_rows];
    
    // Perform matrix multiplication
    for i in 0..a_rows {
        for j in 0..b_cols {
            let mut sum = 0.0;
            for k in 0..a_cols {
                sum += a[i][k] * b[k][j];
            }
            result[i][j] = sum;
        }
    }
    
    result
}
