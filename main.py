# -*- coding: utf-8 -*-
"""
Name: BrainF Interpreter
Author: Sanket Tarafder
Date: 31.06.2021
"""

import numpy as np
import sys
from pathlib import Path


def validator(code):
    '''
    

    Parameters
    ----------
    code : String
        The BrainF code read from the file.
        
    The function checks the code if it has valid loops or not and exits the
    execution if it finds any wrong loops.

    Returns
    -------
    None.

    '''
    
    stk = []
    
    for e in code:
        if e =="[":
            stk.append(e)
        elif e == "]":
            try:
                stk.pop()
            except:
                print("The code has extra \"]\"")
                sys.exit()
                
    if len(stk) > 0:
        print("The code has extra \"[\"")
        sys.exit()
           

def get_pairs(code):
    '''
    

    Parameters
    ----------
    code : String
        The BrainF code read from the file.
        
    The function determines the starting and ending position of the loops and
    make pairs of them.

    Returns
    -------
    pairs : Dictionary
        A dictionary having the loop start index as key and ending as value.

    '''
    
    pairs = dict()
    
    position = 0
    index = 0
    
    startb = 0
    endb = 0
    
    while index < len(code):
        if code[index] == "[":
            start, position = index, index + 1
        
        count = 0
        
        while position < len(code):
            if code[position] == "[":
                    count += 1
                    startb += 1
                    
            elif code[position] == "]":
                if count % 2 == 0:
                    if startb == endb:
                        pairs[start] = position
                        break
                    else:
                        endb += 1
                else:
                    count += 1
                    endb += 1
                    
            position += 1
            
        index += 1
        
    return pairs
        
    
def compilR(code, pairs):
    '''
    

    Parameters
    ----------
    code : String
        The BrainF code read from the file.
    pairs : Dictionary
        A dictionary having the loop start index as key and ending as value.
        
    Compiles the BrainF code.

    Returns
    -------
    None.

    '''
    
    tape = np.zeros(30000, dtype=np.uint8) # Allocating the memory strip for all the operations
    pos = [] # List behaving as a stack to store the loops starting indices
    index = 0 # Index in the tape array
    position = 0 # Position of the pointer in the code
    
    while(position < len(code)):
        e = code[position]
        
        if e == "+":
            tape[index] += 1
        elif e == "-":
            tape[index] -= 1
        elif e == ">":
            index += 1
        elif e == "<":
            index -= 1
        elif e == ".":
            print(chr(tape[index]),end="")
        elif e == ",":
            tape[index] = np.uint8(ord(input()))            
        elif e == "[":            
            if tape[index] != 0:
                pos.append(position)
            else:
                position = pairs[position]                
        elif e == "]":
            position = pos.pop()
            continue
            
        position += 1
        
        
def get_code():
    '''
    
    
    The function asks user for the path of the BrainF code file and reads the
    code in it and returns it.
    
    Returns
    -------
    String
        The BrainF code read from the file.

    '''
    
    path = Path(input("Enter full the path to the BrainF file: "))
    
    if path.exists:
        with open(path, mode="r") as file:
            code = file.read()
    else:
        print("No file exist")
        
    return code.strip()
    

def main():
    code = get_code()
    validator(code)
    pairs = get_pairs(code)
    compilR(code, pairs)
    
   
if __name__=="__main__":
    main()
