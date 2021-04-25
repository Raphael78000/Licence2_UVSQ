run: principal
	./principal

# Edition de lien
principal: ea.o token.o token_ea.o principal.o 
	gcc -o principal ea.o token.o token_ea.o principal.o


# Compil sans édition de lien
principal.o: principal.c ea.h
	gcc -c -Wall principal.c

# Compil sans édition de lien
ea.o: ea.c ea.h
	gcc -c -Wall ea.c
	
# Compil sans édition de lien
token.o: token.c token.h
	gcc -c -Wall token.c

# Compil sans édition de lien
token_ea.o : ea.h token.h  token_ea.h token_ea.c
	gcc -c -Wall token_ea.c


clean:
	rm -f token_ea.o
	rm -f token.o
	rm -f ea.o
	rm -f principal.o
	rm -f principal
	ls -l


DIRNAME=TD_EA
TD_EA.zip: *.c *.h Makefile
	rm -rf $(DIRNAME)
	mkdir $(DIRNAME)
	cp *.c *.h Makefile $(DIRNAME)
	zip -r TD_EA.zip $(DIRNAME)
	rm -rf $(DIRNAME)
	ls -l TD_EA.zip
