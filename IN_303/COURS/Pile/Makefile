run: Pile clean

Pile: pile.o main.o
	gcc -o Pile main.o pile.o

pile.o: pile.c pile.h
	gcc -c pile.c pile.h
	
main.o:pile.h
	gcc -c main.c pile.h

clean:
	rm -f pile.o
	rm -f main.o
