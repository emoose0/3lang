# 3lang
An attempt at an esoteric language inspired by brainfuck

# About
My first esoteric language, heavily inspired by brainfuck, the main difference is that while brainfuck gives you an unlimited amount of "cells", 3lang gives you 3 variables called `a`, `b`, and `c` (hence the name 3lang).

# Actions
| Command | Usage |
| --- | --- |
| + | Increment current referenced variable by 1 |
| - | Decrement current referenced variable by 1 |
| ( | Set current referenced variable to `b` |
| [ | Set current referenced variable to `c` |
| ) and ] | Set current referenced variable to `a` |
| { | Start loop `(while currentVariable != 0)` |
| } | End loop |
| . | Input |
| , | Output ascii value of current referenced variable to stdout |

Any character that is not part of the above actions will be ignored and treated as a comment
By default `a` is referenced first

# Interpreter
Using the interpreter is pretty simple, after building using `make`, you can interpret a file with a .3 extension by typing in `3l [file].3`. Additionally you have the option add a `-r` to the end of the arguments to print the final values of each variable

# Referencing variables
By default, the current referenced variable is `a`, you can change the variable being currently referenced to b or c by wrapping actions inside `[]` and `()`

Example:
```
+++ set a to 3
(+++) set current referenced variable to b then add 3 to b and then set the current referenced variable to a again
[+++] set current referenced variable to c then add 3 to c and then set the current referenced variable to a again
```


# Loops
Loops work relatively the same as they do in brainfuck. Wrapping `[]` or `()` around a loop changes the variable being compared to 0

Example:

```
{+} infinite loop that increments a
```
```
[{+}] loop that increments c
```

However, it is still possible to change which variable is being checked while the loop is still running. Example:

```
{++[} loop that increments a by 2 and then sets the variable currently being referenced to c
      while this loop's conditions start as (while a != 0)
      after the interpreter passes the `[` the conditions then become (while c != 0)
```

## Note that wrapping `{}` around `[]` or `()` is NOT the same as wrapping `[]` or `()` around `{}`.
Example:

```
[{+}] is an infinite loop that increments c by 1; additionally this loop is the equivalent of (while c!= 0)
{[+]} is an infinite loop that increments c by 1 BUT the loop is the equivalent of (while a!= 0)
```

I recommend using a as your loop variable because it produces (more) readable code compared to using `b` or `c`. Example:
```
{[+] (++) -} loop that increments c by 1 b by 2 and then decrements a

({[+] ++ (-}) loop that increments c by 1 a by 2 and then decrements b
```

Loops are very important to programming in 3lang, anything can be done with a loop.

## Program that prints out "HI"
```
+++++++++ set a to 9
{(++++++++) [++++++++] -} [+]  increment b and c by 8 for every iteration of the loop this is done until both b and c are 72 after which c is incremented by 1
                               at the end of every iteration a is incremented by 1
(,) [,] print ascii values of b and c
({-[-](}) [-] set b and c to 0
```

## Program that checks `if(c != b)`
```
(.) input for b
[.] input for c

({[-( - }) make b and c 0 if b and c are 0 then theyre equal

+ set a to 1 for loop for else clause

[{ if c == b
	{-} set c equal to 0
	]+++++++++++ set a equal to 12

	{[++++] -} set c equal to "0"

	[, print c

	{-} set c equal to 0 to exit
}]



{
	+++++++++++ set a to 12
	{[++++] -} [+ set c to "1"
	, {-} print and then set c to 0
	]{-}
}
```

# Notes
## Using ] and )
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

A `[` or `(` does not require a corresponding `]` or `)`. However, every `{` (loop start) requires a `}` to be interpreted without errors
## Formatting code
The interpreter ignores all tabs, spaces, and newlines. Because of this I recommend putting effort into formatting your code so it's easier to read
[Take this if statement made in 3lang](https://github.com/emoose0/3lang/tree/main#program-that-checks-ifc--b).

This is the same code without spaces, newlines, indents, or comments
```
(.)[.]({[-(-})+[{{-}]+++++++++++{[++++]-}[,{-}}]{+++++++++++{[++++]-}[+,{-}]{-}}
```
I will admit, the shortform version looks way cooler but reading it is a pain. For more complex programs formatting is very important
