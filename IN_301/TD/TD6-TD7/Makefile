# Définitions de macros
CC = gcc
CFLAGS = -c -Wall
LDFLAGS = -lm
CSRC = *.c
HSRC = *.h
OBJS = principal.o\
	exo_39.o exo_41.o exo_41.o exo_42.o\
	exo_43.o exo_44-45.o exo_46-47.o\
	exo_48.o


# $@ : nom de la cible.
# $? : liste des noms des dépendances plus récentes que la cible.
# $< : nom de la première dépendance.
# $^ : liste des noms de toutes les dépendances.

# .PHONY run :pour dire que même s'il y a un fichier run,
# on en tient pas compte
.PHONY: run
run: principal
#	echo $(CSRC)
	./principal

# $@ : nom de la cible.
# $^ : liste des noms de toutes les dépendances.
principal: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
	

principal.o: principal.c $(HSRC)
	$(CC) $(CFLAGS) $<


# Cible générique pour compiler les fichiers .c qui ont un .h
# $< : nom de la première dépendance.
%.o: %.c %.h
	$(CC) $(CFLAGS) $<

# Cible générique pour compiler les fichiers .c qui N'ont PAS de .h
# $< : nom de la première dépendance.
%.o: %.c
	$(CC) $(CFLAGS) $<


.PHONY: clean
clean:
	rm -f *.o
	rm -f principal
	ls -l


DOSSIER = BLOC7-8
.PHONY: zip
zip:
	rm -rf $(DOSSIER)
	rm -f $(DOSSIER).zip
	mkdir $(DOSSIER)
	cp *.c *.h Makefile $(DOSSIER)
	zip -r $(DOSSIER).zip $(DOSSIER)
	rm -rf $(DOSSIER)
	ls -l
	
