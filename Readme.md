# Glypho Interpreter

This is the homework for the Formal Languages and Automata Theory Course. ([the problem statement](./problem_statement.pdf)).

## Table of Contents

- [Glypho Interpreter](#glypho-interpreter)
  - [Table of Contents](#table-of-contents)
  - [Prerequisites](#prerequisites)
  - [Project Structure](#project-structure)
  - [Application overview](#application-overview)
  - [Build and Run](#build-and-run)

## Prerequisites

The following tools are required to compile the program.

- gcc (version 8 or newer, tested on 9.3.0)
- make (tested on 4.2.1)

## Project Structure

- Interpreter - contains the logic for the Glypho interpreter
- Input Parser - parses the input files/code (.gly)
- Instruction - definitions Glypho instructions
- Stack - the stack for a Glypho program
- Helpers - helper functions, used mostly to display errors and stop the program

## Application overview

This interpreter will load code from the specified `.gly` files, and run the program.
In the first step, the data is parsed, splitting it into *4 char groups*. At this step, we can check for invalid instructions (incomplete instructions), if we find a group that has less than 4 characters (`syntactic error`).

After this step, the instructions are converted from the char format into `Instruction` objects, multithreaded. The instructions are added to a list (*the program*), linked to one another, and the `braces` are checked (the other type of `syntactic error`).

If the program was successfully loaded, we can run the code. After a instruction is executed, we get the `ID` of the next instruction. **The next id** is usually the current instructions `ID` + 1, with a few exceptions, more specifically, `executes` and `braces`.

- when a instruction is _generated from the stack_, its `ID` will be the smallest one available, not the one immediately next to the `Execute` instruction. After that instruction is ran, the next instruction ID will be equal to the `parent id` (the id of the execute instruction that generated it)
- in the case of the braces, they use both a _next instruction id_ and a _jump id_. If the top of the stack is **equal** to 0, a `L-brace` will use the jump id (to jump to the `R-Brace`), while the `R-Brace` does the jump if the top is **not equal** to 0.

The way instructions work is documented in the [problem statement](./problem_statement.pdf) and the code itself. For many instructions, the actual logic is implemented in the `Stack`.

The `Stack` is implemented using a `std::vector` that stores _long long_ integers. When a value is _pushed_ onto the `Stack`, it is added at the back of the _vector_. This means that the _top_ of the stack is actually the _back_ of the vector and vice-versa.

One thing to note is the fact that initially, the stack used `Integer` objects to store the numbers. `Integer` was an implementation for big numbers, but it was removed, as some operations (multiplication, modulus) were too inefficient/slow. It used `int8` arrays to store the digits of the numbers.

## Build and Run

The `Makefile` defines different rules used for compilation, debugging, running the code, etc.:

- build - compiles the program
- run - executes the program, providing two arguments to it - `input` (the `.gly` file) and `base` (the base of the numbers that will be read from `stdin`)
- clean - removes the binary, object files and some other unnecessary files
- beauty - code-styling for the program
- memory - runs **valgrind** to check the program for memory leaks, used for debugging
- gitignore - creates/adds rules to the .gitignore files
- archive - creates the homework archive

© 2021 Grama Nicolae, 332CA
