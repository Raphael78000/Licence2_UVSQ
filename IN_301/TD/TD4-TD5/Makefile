run: principal

principal: ea.o principal.o token.o
	gcc -o principal ea.o token.o principal.o -Wall
	./principal

ea.o: ea.h ea.c
	gcc -c ea.c ea.h -Wall
	
token.o: token.h token.c
	gcc -c token.c token.h -Wall

principal.o: principal.c ea.h token.h
	gcc -c principal.c -Wall

