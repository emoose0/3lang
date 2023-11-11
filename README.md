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

Any character that is not part of the above actions will be ignored and treated as a comment

# Interpreter
Using the interpreter is pretty simple, after building using `make`, you can interpret a file with a .3 extension by typing in `3l [file].3`. Additionally you have the option add a `-r` to the end of the arguments to print the final values of each token

# Notes
Because `]` and `)` do not check what the current variable being referenced is they can be used in combination with `[` and `(` without affecting the code's interpretation (though, I recommend not doing this for readability purposes)

Example: 
```
(++++) ++ set b to 4 and set a to 2
```

and

```
(++++] ++ set b to 4 and set a to 2
```
will yield the same results and won't return an error

A `[` or `(` does not require a corresponding `]` or `)`. However, creating every `{` (loop start) requires a `}` to be interpreted without errors
