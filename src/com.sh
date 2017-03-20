#!/bin/bash

echo "Compiling..."
make clean
make
./Interpreter <input1.txt> output.txt
cat output.txt

