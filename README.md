# BrainF Interpreter
#### Sanket Tarafder

BrainF is an [esoteric programming language](https://en.wikipedia.org/wiki/Esoteric_programming_language) by Urban Müller. It is created in 1993.


Notable for its extreme minimalism, the language consists of only eight simple commands and an instruction pointer. While it is fully Turing complete, it is not intended for practical use, but to challenge and amuse programmers. Brainfuck simply requires one to break commands into microscopic steps.

The language's name is a reference to the slang term brainfuck, which refers to things so complicated or unusual that they exceed the limits of one's understanding.

### History

In 1992, Urban Müller, a Swiss physics student, took over a small online archive for Amiga software. The archive grew more popular, and was soon mirrored around the world. Today, it is the world's largest Amiga archive, known as Aminet.

Müller designed Brainfuck with the goal of implementing the smallest possible compiler, inspired by the 1024-byte compiler for the FALSE programming language. Müller's original compiler was implemented in machine language and compiled to a binary with a size of 296 bytes. He uploaded the first Brainfuck compiler to Aminet in 1993. The program came with a "Readme" file, which briefly described the language, and challenged the reader "Who can program anything useful with it? :)". Müller also included an interpreter and some quite elaborate examples. A second version of the compiler used only 240 bytes.

As Aminet grew, the compiler became popular among the Amiga community, and in time it was implemented for other platforms.

### Language design

The language consists of eight commands, listed below. A brainfuck program is a sequence of these commands, possibly interspersed with other characters (which are ignored). The commands are executed sequentially, with some exceptions: an instruction pointer begins at the first command, and each command it points to is executed, after which it normally moves forward to the next command. The program terminates when the instruction pointer moves past the last command.

The brainfuck language uses a simple machine model consisting of the program and instruction pointer, as well as a one-dimensional array of at least 30,000 byte cells initialized to zero; a movable data pointer (initialized to point to the leftmost byte of the array); and two streams of bytes for input and output (most often connected to a keyboard and a monitor respectively, and using the ASCII character encoding).

## Commands

The **[C](https://en.wikipedia.org/wiki/C_(programming_language))** equivalents of the instructions are

| BrainF Command | C Equivalent|
| :---------:    |  :--------  |
|(Program Start) | char array[30000] = {0}; char *ptr = array;|
|>| ++ptr;|
|<| --ptr;|
|+| ++*ptr;|
|-| --*ptr;|
|.| putchar((char)tape\[i\]);|
|,|*ptr = getchar();|
|\[|while (*ptr) {|
|]|}|

For further knowledge referred to the [Wikipedia](https://en.wikipedia.org/wiki/Brainfuck) page and you can find more Brainf Codes in this url[\(just click here\)](http://copy.sh/brainfuck/).

## My Implementation

The repository contains 2 files and 2 directory:

1. <code>main.py</code>: A Python script containing a BrainF Interpreter.
2. <code>BrainF.ipynb</code>: A Jupyter Notebook containing the Python script with detailed explaination and some explaination. This file can also be viwed properly with nbviwer from this [link](https://nbviewer.jupyter.org/github/skt09/BrainF-Interprter/blob/main/BrainF.ipynb).
3. <code>c/brainf/source</code>: Contains BrainF Interpreter written in C and also the makefile to compile it.
4. <code>Samples</code>: This folder contains some sample codes writen in BrainF.

### main.py

The file has four functions:

1. get_code: The function asks user for the path of the BrainF code file and reads the
    code in it and returns it.
2. validator: The function checks the code if it has valid loops or not and exits the
    execution if it finds any wrong loops.
3. get_pairs: The function determines the starting and ending position of the loops and
    make pairs of them.
4. compilR: Compiles the BrainF code.

### c/brainf/source

The folder contains the C implementation for this Interpreter with a diferent approach and in a optimized way. This is the most optimised interpreter in this repository. The code is contributed by Soham Malakar.

The directory contains the needed custom C files for this project and the main driver program is situated in the <code>main.c</code> file.

In order to run the program you have to open the Linux/mac terminal in the directory and run the make command beacause the directory includes a <code>Makefile</code> and then run **./brain** with the <code>filename</code> as command line argument.

### Samples

The folder contains 9 sample BrainF codes.

1. beers.b
2. chars.b
3. hellom.b
4. manderbolt.b
5. oobrain.b
6. piCal.b
7. random.b
8. squares.b
9. triangle.b

