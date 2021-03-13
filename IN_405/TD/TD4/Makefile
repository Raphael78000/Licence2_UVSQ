
ls: stat.c
	gcc -o $@ $^

internals.o: internals.c internals.h
	gcc -c $<
	
main.o: main.c internals.h
	gcc -c $<
	
phantom: internals.o main.o 
	gcc -o $@ $^
	
clean: 
	rm -f internals.o
	rm -f main.o

