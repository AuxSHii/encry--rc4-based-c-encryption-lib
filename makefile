all: encry example

example: example.o
	gcc encry.dll example.o -o example.exe -Wall -O2

example.o: example.c
	gcc -c -O2 -Wall example.c

encry: encry.o
	gcc encry.o -o encry.dll -O2 -Wall -shared

encry.o: encry.c
	gcc -c -O2 -Wall encry.c

clean:
	del /q *.o *.dll example.exe
