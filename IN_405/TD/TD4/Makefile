
phantom: internals.o main.o api.o
	gcc -o $@ $^ -g -Wall

internals.o: internals.c internals.h
	gcc -c $< -g -Wall

main.o: main.c api.h
	gcc -c $< -g -Wall

api.o: api.c api.h
	gcc -c $< -g -Wall

.PHONY: clean
clean: 
	rm -f internals.o
	rm -f main.o
	rm -f api.o
	
NOM= LAZZARI-ARMOUR_Raphael_TD04B
.PHONY: tar
tar: $(NOM).tar clean

$(NOM).tar: *.c *.h Makefile README.md
	rm -rf $(NOM)
	mkdir $(NOM)
	cp *.c *.h Makefile README.md $(NOM)
	tar -zcvf $@ $(NOM)
	rm -rf $(NOM)


