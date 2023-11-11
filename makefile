flags = -c -Wall
sources = $(wildcard *.c)
headers = $(wildcard *.h)
objects = $(sources:.c=.o$)
exec = 3l.exe

main:
	gcc $(flags) $(sources) $(headers)
	gcc $(objects) -o $(exec)

clean:
	del /f *.o
	del /f *.h.gch
	del /f $(exec)