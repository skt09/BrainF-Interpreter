import numpy as np
import sys

name = sys.argv[1]

try:
    file = open(name) # will search in the current directory, not the directory containing brainf.py
except Exception as e:
    print(e)
    exit()

buffer = file.read() # the actual brainf code
file.close()

memsize = 1024 # bytes of memory that will be allocated for brainf computation

stk = [] # stack for calculating the position of each pair and their corresponding pairs
pairs = {} # storing those corresponding pairs for the jumps
tape = np.zeros(memsize, dtype=np.int8) # the memory is allocated for brainf computation

i = 0

# to keep track of the cursor in the brainf code
line_count = 1
char_count = 1

# searching the corresponding pairs in the brainf code and validating the brainf code
for c in buffer:
    
    if c == '\n':
        line_count += 1
        char_count = 1

    elif c == '[':
        stk.append(i)
        
    elif c == ']':
        try:
            temp = stk.pop()
        except:
            print(f'\nSyntax error: Unexpected closing bracket in line {line_count} char {char_count}.')
            exit()
        else:
            pairs.update({temp: i})
            pairs.update({i: temp})
    
    char_count += 1
    i += 1

if len(stk) != 0:
    print(f'\nSyntax error: Unclosed bracket in line {line_count} char {char_count}.')
    exit()

i = 0
j = 0

# interpreting the brainf code
while i < len(buffer):

    c = buffer[i]

    if c == '+':
        tape[j] += 1

    elif c == '-':
        tape[j] -= 1
    
    elif c == '>':
        j += 1
    
    elif c == '<':
        j -= 1
    
    elif c == '[':
        if tape[j] == 0:
            i = pairs[i]
    
    elif c == ']':
        if tape[j] != 0:
            i = pairs[i]
    
    elif c == ".":
        print(chr(tape[j]), end='')

    elif c == ",":
        tape[j] = np.int8(ord(input()))      
    
    i += 1
