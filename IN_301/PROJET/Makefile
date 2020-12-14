CC = gcc
OPT = -Wall -c 
LDFLAGS = -lm
OFILES = main.o tableaux.o ABR.o AVL.o recherche.o chrono.o

.PHONY : run
run: dico 
	./dico pg31469.txt 
	mv Resultat.txt Resultat_aléatoire.txt
	./dico pg31469.txt a mot lol i 
	mv Resultat.txt Resultat_ciblé.txt
	geany Resultat_ciblé.txt
	geany Resultat_aléatoire.txt

dico: $(OFILES)
	$(CC) -o $@ $^
	
main.o: main.c *.h
	$(CC) $(OPT) $< $(LDFLAGS)

%o: %.c %.h
	$(CC) $(OPT) $<
	
clean: 
	rm -f *.o
	rm -f dico
	rm -f TL.txt
	rm -f MC.txt
	rm -f Contenu_Arbre.txt
	rm -f Contenu_Noeud.txt
	rm -f Resultat_ciblé.txt
	rm -f Resultat_aléatoire.txt

FILE = LIRZIN_LAZZARI-ARMOUR
zip:
	rm -rf $(FILE)
	mkdir $(FILE)
	cp *.c *.h Makefile $(FILE)
	zip -r $(FILE).zip $(FILE)
	rm -rf $(FILE)
	ls -l

	
