run: main clean

exo_xx.o: exo_xx.c exo_xx.h
	gcc -c exo_xx.c
	
main.o: main.c 
	gcc -c main.c

main: main.o exo_xx.o
	gcc -o main main.o exo_xx.o
	./main

clean: 
	rm -f exo_xx.o
	rm -f main.o
