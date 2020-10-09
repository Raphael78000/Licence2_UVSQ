run: all
	 ./tri_mot romeoetjuliette

all: tri_mot


tri_mot: main.o tableau.o chrono.o tri.o
	gcc -Wall -g main.o tableau.o chrono.o tri.o -o tri_mot -g

tri.o: tri.c tableau.h
	gcc -Wall -g -c tri.c -g -O2

main.o: main.c tableau.h chrono.h
	gcc -Wall -g -c main.c -g -O2

tableau.o: tableau.c tableau.h
	gcc -Wall -g -c tableau.c -g -O2

chrono.o: chrono.c
	gcc -Wall -g -c chrono.c -g -O2

clean:
	rm -f *.o
	rm -f tri_mot
	ls -l
