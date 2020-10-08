visu: stat.pdf
	evince stat.pdf &


stat.pdf: tri_bulle stat.gplt test_tri_bulle.data
	gnuplot stat.gplt

test_tri: tri_bulle tri_fusion
	./tri_bulle
	./tri_fusion

run: tri_bulle tri_fusion
	time ./tri_bulle 10000
	time ./tri_fusion 10000
	time ./tri_bulle 100000
	time ./tri_fusion 100000
	time ./tri_bulle 200000
	time ./tri_fusion 200000
	
tri_bulle: tri_bulle.o tabint.o
	gcc -Wall -o tri_bulle tri_bulle.o tabint.o

tri_bulle.o: tri_bulle.c tabint.h stat.h
	gcc -Wall -c tri_bulle.c
	
tri_fusion: tri_fusion.o tabint.o
	gcc -Wall -o tri_fusion tri_fusion.o tabint.o
	
tri_fusion.o: tri_fusion.c tabint.h stat.h
	gcc -Wall -c tri_fusion.c


# La bibliothèque de manipulation de tableaux
tabint.o: tabint.c tabint.h
	gcc -Wall -c tabint.c

clean:
	rm -f tabint.o
	rm -f tri_bulle.o tri_bulle
	rm -f stat.pdf
	rm -f test_tri_bulle.data
	ls -l
