run: principal clean

principal: ea.o principal.o
	gcc -o principal ea.o principal.o -Wall
	./principal

ea.o: ea.h ea.c
	gcc -c ea.c ea.h -Wall
	
principal.o: principal.c ea.h
	gcc -c principal.c ea.h -Wall

clean: 
	rm  ea.o 
	rm  principal.o
	rm  principal
