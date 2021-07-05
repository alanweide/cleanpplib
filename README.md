# Clean++ Component Library
### Alan Weide, Paolo A.G. Sivilotti, and Murali Sitaraman

## Introduction

This library contains a (small) collection of software components written in the Clean++ Discipline.
All of the types in this library are mutable.

Clean++ is a programming discipline that leverages C++ move semantics to ensure code is readable, efficient, and—most importantly—sound to reason about in a local, modular fashion.
The three driving principles of Clean++ are:

1. Preserving the soundness of local reasoning
2. Preservation of good object-oriented programming practices
3. Familiarity to seasoned C++ programmers

For a detailed dive into the Clean++ discipline, see [this paper][paper link] about it.

## Building and Testing the library

The library can be built using GNU Make (see the included Makefile in the project's root directory for descriptions of the various targets).
The command `make libcleanpp.a` generates a static library that can be included and linked into another project.
To compile a simple, standalone Clean++ program, invoke the make target `%.o`. 
To run the included tests, you must have CMake installed; they can be built and run via the `test` target of the Makefile by using the command `make test` or manually by invoking CMake directly from the `cleanpp-gtest` directory.

## Using the library

Once the library is build, the static library can be placed on your system's includepath, or it can be explicitly linked at compile-time.
For examples of explicit linking, see the Makefile target `%.o`.

## List of Components in this Library

This list is arranged in alphabetical order, with each implementing class for a comonent identified as a sub-bullet below the abstract description of the component.

* `cleanpp::integer`: an unbounded* integer that supports simple arithmetic operations
    - `cleanpp::nn_integer`: implemented as a layer on top of `cleanpp::natural_number`
	- `cleanpp::vector_integer`: implemented using a C++ `vector` as the underlying data type
* `cleanpp::list`: a traversable (ordered) list of items of arbitrary type
	- `cleanpp::stack_based_list`: implemented as a layer on top of `cleanpp::stack`
* `cleanpp::map`: a set of key-value pairs of arbitrary type
	- `cleanpp::map_on_set`: implemented as a layer on top of `cleanpp::set`
* `cleanpp::natural_number`: an unbounded* natural number (*i.e.*, a nonnegative integer) that supports simple arithmetic operations
	- `cleanpp::bounded_nn`: implemented as a layer on top of `long`
	- `cleanpp::stack_nn`: implemented as a layer on top of `cleanpp::stack`
* `cleanpp::queue`: a FIFO queue with entries of an arbitrary type
	- `cleanpp::array_queue`: implemented using resizing array
	- `cleanpp::linked_queue`: implemented as a doubly-linked list
* `cleanpp::set`: a finite set of elements of an arbitrary type
	- `cleanpp::set_on_queue`: implemented using a `cleanpp::queue` as the underlying data structure
* `cleanpp::stack`: a LIFO stack with entries of an arbitrary type
	- `cleanpp::array_stack`: implemented using resizing array
	- `cleanpp::linked_stack`: implemented using a singly-linked list

\* The implementation type `cleanpp::bounded_nn` produces a `cleanpp::natural_number` that is bounded by the range of `long` (and, therefore, a `cleanpp::integer` that is similarly bounded if used as the basis for the `cleanpp::nn_integer` implementation). 
However, it's super fast when values are in its range.

[paper link]: tbd