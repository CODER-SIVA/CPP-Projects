// Basic Multiplication Calculator in Rust
use std::io;

fn main() {
    println!("===== Basic Multiplication Calculator =====");
    
    // Get first number
    println!("Enter the first number:");
    let mut num1 = String::new();
    io::stdin()
        .read_line(&mut num1)
        .expect("Failed to read input");
    
    let num1: f64 = match num1.trim().parse() {
        Ok(num) => num,
        Err(_) => {
            println!("Invalid input! Using default value 0.");
            0.0
        }
    };
    
    // Get second number
    println!("Enter the second number:");
    let mut num2 = String::new();
    io::stdin()
        .read_line(&mut num2)
        .expect("Failed to read input");
    
    let num2: f64 = match num2.trim().parse() {
        Ok(num) => num,
        Err(_) => {
            println!("Invalid input! Using default value 0.");
            0.0
        }
    };
    
    // Calculate and display result
    let result = multiply(num1, num2);
    
    println!("\nCalculation Result:");
    println!("{} × {} = {}", num1, num2, result);
}

// Function to multiply two numbers
fn multiply(a: f64, b: f64) -> f64 {
    a * b
}
