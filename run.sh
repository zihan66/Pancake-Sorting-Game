#!/bin/bash

make clean
make
javac Pancake.java Main.java 
java Main & ./main