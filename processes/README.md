# Understanding Process Creation with fork()

## How fork() Works

The `fork()` system call creates a new process by duplicating the calling process. After a successful call to `fork()`, two processes will exist: the parent process and the child process. Both processes continue execution from the point where `fork()` returns.

### Key Characteristics of fork():

1. **Complete Duplication**: The child process is an exact copy of the parent process, including:
   - Code segment
   - Data segment
   - Heap
   - Stack
   - File descriptors
   - Signal handlers

2. **Return Value Differences**:
   - In the parent process: `fork()` returns the PID (Process ID) of the newly created child
   - In the child process: `fork()` returns 0
   - If an error occurs: `fork()` returns -1

3. **Memory Separation**: Although the child initially has identical memory contents, it receives a separate copy. This is often implemented using Copy-on-Write (CoW) for efficiency, where memory pages are only duplicated when one process modifies them.

4. **Process Attributes**:
   - The child gets a unique PID
   - The child's parent PID (PPID) is set to the PID of the process that called `fork()`
   - Resource utilizations are reset to zero in the child

## Example Programs

### 1. Basic Fork Example (`basic_fork.cpp`)

This example demonstrates the fundamental behavior of `fork()`:
- Parent and child processes run concurrently
- Each process executes different code based on the return value of `fork()`
- Parent waits for the child to complete using `waitpid()`
- Both processes maintain their own copies of variables

### 2. Fork-Exec Pattern (`fork_exec.cpp`)

This example demonstrates a common usage pattern:
- Parent process forks a child
- Child process immediately replaces itself with a new program using `exec()`
- Parent waits for the child to complete
- This pattern is how shells typically launch new programs

## Key Differences Between Examples

1. **Process Content**:
   - In the first example, both processes run the same program but different parts of it
   - In the second example, the child process replaces its memory image with a completely new program

2. **Memory Usage**:
   - First example: Both processes share the same code but have separate copies of data
   - Second example: After `exec()`, the child has completely different code and data

3. **Common Use Cases**:
   - First approach: When you need to run parallel tasks within the same program
   - Second approach: When you need to launch external programs (like a shell does)

## Compilation and Execution

Compile the examples with:

```bash
g++ -o basic_fork basic_fork.cpp
g++ -o fork_exec fork_exec.cpp
```

Run the examples with:

```bash
./basic_fork
./fork_exec
```
