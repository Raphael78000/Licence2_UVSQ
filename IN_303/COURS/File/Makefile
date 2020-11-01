run: File clean

File: file.o main.o
	gcc -o File main.o file.o

file.o: file.c file.h
	gcc -c file.c file.h
	
main.o:file.h
	gcc -c main.c file.h

clean:
	rm -f file.o
	rm -f main.o

