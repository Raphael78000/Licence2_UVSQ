run: dico 
	./dico pg31469.txt

tableaux.o: tableaux.c tableaux.h
	gcc -Wall -c tableaux.c

main.o: main.c tableaux.h
	gcc -Wall -c main.c
	
ABRAVL.o : ABRAVL.c ABRAVL.h
	gcc -Wall -c ABRAVL.c

dico: tableaux.o main.o ABRAVL.o
	gcc -o dico tableaux.o main.o ABRAVL.o -Wall
	
clean: 
	rm -f main.o
	rm -f tableaux.o
	rm -f ABRAVL.o
	rm -f dico
	rm -f TL.txt
	rm -f MC.txt
