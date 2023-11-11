# 3lang
An attempt at an esoteric language inspired by brainfuck

# About
My first esoteric language, heavily inspired by brainfuck, the main difference is that while brainfuck gives you an unlimited amount of "cells", 3lang gives you 3 variables called a, b, and c (hence the name 3lang).

# Actions
| Command | Usage |
| --- | --- |
| + | Increment current referenced variable by 1 |
| - | Decrement current referenced variable by 1 |
| ( | Set current referenced variable to b |
| [ | Set current referenced variable to c |
| ) and ] | Set current referenced variable to a |
| { | Start loop (while currentVariable != 0) |
| } | End loop |
| . | Input |
| , | Output ascii value of current referenced variable to stdout |
