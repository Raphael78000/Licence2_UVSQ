

ls: stat.c
	gcc -o $@ $^

internals.o: internals.c internals.h
	gcc -g -c $^ 
	
main_f.o: main_f.c internals.h
	gcc -g -c $^ 
	
phantom: internals.o main_f.o
	gcc -g -o $@ $^ 
	
clean: 
	rm -f internals.o
	rm -f main_f.c
