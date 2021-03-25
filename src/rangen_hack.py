#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Sep 17 19:23:34 2018

@author: nate
"""
import sys
import random
import os

# The idea here is to generate lines of c instead of using a jump table.
# It should write the output directly to dynamic.c  when invoked by a button
# in the GUI. This should be more reliable than the other methods I've tried. 

# !o to refer to either x or y, chosen at random.
# !c to refer to a random constant between 1 and 512.
operations = [
    "a = a + !o;",
    "a = a - !o;",
    "a = ~a;",
    "a = a * !o;",
    "a = a | !o;",
    "a = a & !o;",
    "a = a ^ !o;",
    "a = a * 2;",
    "a = __builtin_popcountll(a);",
    "a = cl_mul(a, !o);",
    "a = cl_mul(a, a);",
    "a = a * 3;",
    "a = a + 1;",
    "a = a - 1;",
    "a = (~a)+1;",
    "a = 0 - a;",
    "a = (!o * 2) ^ !o;"
    # use these three to compute tropical polynomials
    #"a = a + !o;",
    #"a = a < !o? a : !o;",
    #"a = a + !c;"
]



def gen_prog(n):
    
    random.seed(None)
    prog = []
    
    
    used_x = False;
    used_y = False;
    
    for i in range(0, n):
        r = random.randint(0,len(operations)-1)
        o = random.randint(0,1)
        op = ""
        
        if(o == 1):
            op = "x"
            used_x = True
        else:
            op = "y"
            used_y = True
            
        line = "  "+operations[r] + "\n"
        line = line.replace("!o",op)
        line = line.replace("!c", str(random.randint(1,512)))
        prog.append(line)

    # If it doesn't use both x and y, regen the program
    if(used_x and used_y):    
        return prog
    elif(n < 2):
        return prog
    else:
        return gen_prog(n)

def write_c(n, toggle_pop=False):
    source = ""
    with open("./src/dynamic.c (template)","r") as f:
        source = f.readlines()
    
    output = []
    
    for i in source:
        
        output.append(i)
        if(i.find("begin") != -1):
            output.extend(gen_prog(n))
    
    for i in output:
        print(i[:-1])
                
if(len(sys.argv) == 2):
    write_c(int(sys.argv[1]))    































