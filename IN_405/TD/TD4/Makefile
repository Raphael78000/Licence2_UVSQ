
ls: stat.c
	gcc -o $@ $^

internals.o: internals.c internals.h
	gcc -c $< -g
	
main.o: main.c internals.h
	gcc -c $< -g
	
phantom: internals.o main.o 
	gcc -o $@ $^ -g
	
clean: 
	rm -f internals.o
	rm -f main.o

