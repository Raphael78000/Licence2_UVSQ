CC = gcc
CFLAGS = -c -Wall
OBJS = principal.o tas.o

# $@ : nom de la cible.
# $? : liste des noms des dépendances plus récentes que la cible.
# $< : nom de la première dépendance.
# $^ : liste des noms de toutes les dépendances.

.PHONY: run
run: principal
	./principal

principal: $(OBJS)
	$(CC) -o $@ $(OBJS)


principal.o: principal.c tas.h
	$(CC) $(CFLAGS) $<

tas.o: tas.c tas.h
	$(CC) $(CFLAGS) $<


.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f principal
	ls -l

NOM = TD_TAS
.PHONY: zip
zip: $(NOM).zip clean

$(NOM).zip: *.c *.h Makefile
	rm -rf $(NOM)
	mkdir $(NOM)
	cp *.c *.h Makefile $(NOM)
	zip -r $@ $(NOM)
	rm -rf $(NOM)

