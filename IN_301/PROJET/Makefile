CC = gcc
OPT = -Wall -c 
LDFLAGS = -lm
PTL = ./Library/
HFILES = $(PTL)tableaux/tableaux.h $(PTL)ABR/ABR.h $(PTL)AVL/AVL.h $(PTL)recherche/recherche.h $(PTL)chrono/chrono.h
OFILES = main.o tableaux.o ABR.o AVL.o recherche.o chrono.o
TXTFILES = TL.txt MC.txt Contenu_Arbre.txt Contenue_Noeud.txt Resultat_ciblé.txt Resultat_aléatoire.txt

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
	
main.o: main.c $(HFILES)
	$(CC) $(OPT) $< $(LDFLAGS)

tableaux.o: $(PTL)tableaux/tableaux.c $(PTL)tableaux/tableaux.h
	$(CC) $(OPT) $<
	
ABR.o: $(PTL)ABR/ABR.c $(PTL)ABR/ABR.h
	$(CC) $(OPT) $<
	
AVL.o: $(PTL)AVL/AVL.c $(PTL)AVL/AVL.h
	$(CC) $(OPT) $<
	
recherche.o: $(PTL)recherche/recherche.c $(PTL)recherche/recherche.h
	$(CC) $(OPT) $<
	
chrono.o: $(PTL)chrono/chrono.c $(PTL)chrono/chrono.h
	$(CC) $(OPT) $<

#J'attends un mail de la prof pour faire la cible %.o
#En attendant, on met chaque cible o

clean: 
	rm -f *.o
	rm -f dico
	rm -f $(TXTFILES)

FILE = LIRZIN_LAZZARI-ARMOUR
zip:
	rm -rf $(FILE)
	mkdir $(FILE)
	cp *.c *.h Makefile $(FILE)
	zip -r $(FILE).zip $(FILE)
	rm -rf $(FILE)
	ls -l
