run: principal clean

principal: ea.o principal.o token.o
	gcc -o principal ea.o token.o principal.o -Wall
	./principal

ea.o: ea.h ea.c
	gcc -c ea.c ea.h -Wall
	
token.o:token.h token.c ea.h
	gcc -c token.c token.h ea.h -Wall

principal.o: principal.c ea.h token.h
	gcc -c principal.c ea.h token.h -Wall

clean: 
	rm -f ea.o
	rm -f principal
	rm -f token.o
	rm -f ea.h.gch
	rm -f token.h.gch
