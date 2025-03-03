# C++ STL List Example: Task Manager

This project demonstrates the usage of `std::list` container from the C++ Standard Template Library (STL).

## Overview

The program implements a simple Task Manager system that showcases various operations and capabilities of the `std::list` container. The `std::list` is a doubly-linked list container that allows constant time insertion and removal of elements from anywhere in the container.

## Key Features Demonstrated

1. **Basic Operations**:
   - Adding elements at the beginning (`push_front`)
   - Adding elements at the end (`push_back`)
   - Removing elements (`erase`)

2. **Advanced Operations**:
   - Sorting (`sort`)
   - Merging sorted lists (`merge`)
   - Reversing (`reverse`)
   - Splicing (`splice`)

3. **Iterator Usage**:
   - Finding elements
   - Traversing the list

4. **Custom Class Storage**:
   - Storing user-defined objects
   - Custom comparison for sorting

## Time Complexity

- Insertion/Removal at any position: O(1)
- Access to arbitrary element: O(n)
- Finding an element: O(n)
- Sorting: O(n log n)

## Advantages of std::list

- Efficient insertion and deletion at any position
- No invalidation of iterators when modifying the list (except when erasing)
- Bidirectional iteration
- Specialized member functions like `splice` for efficient list manipulation

## Disadvantages of std::list

- No random access (cannot use `[]` operator)
- Higher memory overhead per element (stores pointers to next and previous elements)
- Poor cache locality due to non-contiguous memory storage
- Slower traversal compared to contiguous containers like `std::vector`

## Compilation and Execution

```bash
g++ -std=c++11 list_examples.cpp -o list_examples
./list_examples
```

## When to Use std::list

- When you need frequent insertions and deletions at arbitrary positions
- When you need to move elements from one container to another without copying (using `splice`)
- When you don't need random access to elements
- When iterator/reference stability is important during insertions and deletions
