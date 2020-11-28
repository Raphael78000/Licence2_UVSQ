
run : principal clean

principal : principal.o ea.o token.o
	gcc principal.o ea.o token.o -o principal
	./principal

principal.o : ea.h principal.c
	gcc -Wall -c principal.c

ea.o : ea.h ea.c
	gcc -Wall -c ea.c

token.o : token.h token.c
	gcc -Wall -c token.c

clean :
	rm -f principal.o
	rm -f ea.o
	rm -f token.o
	rm -f principal
	ls -l
