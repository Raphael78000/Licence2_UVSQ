run: principal
	./principal


principal: principal.o exo_39.o exo_40.o exo_41.o exo_42.o exo_43.o
	gcc -Wall -o principal principal.o exo_39.o exo_40.o exo_41.o exo_42.o exo_43.o


principal.o: principal.c *.h
	gcc -Wall -c principal.c

exo_39.o: exo_39.c exo_39.h
	gcc -Wall -c exo_39.c

exo_40.o: exo_40.c exo_40.h
	gcc -Wall -c exo_40.c

exo_41.o: exo_41.c exo_41.h
	gcc -Wall -c exo_41.c

exo_42.o: exo_42.c exo_42.h
	gcc -Wall -c exo_42.c

exo_43.o: exo_43.c exo_43.h
	gcc -Wall -c exo_43.c


clean:
	rm -f *.o
	rm -f principal
	ls -l
	
