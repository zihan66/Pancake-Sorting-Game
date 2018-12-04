#!/bin/bash

make clean
make
javac -Xlint:unchecked Pancake.java Setup.java highScores.java highScores1.java  Startmenu.java
java Startmenu & ./main