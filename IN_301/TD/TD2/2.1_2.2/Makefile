visu: stat.pdf clean
	evince stat.pdf &


stat.pdf:  stat.gplt test_tri
	gnuplot stat.gplt 

test_tri: tri_bulle  tri_fusion
	./tri_bulle
	./tri_fusion
	
	
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
	rm -f tri_bulle.o
	rm -f tri_fusion.o
	rm -f tri_bulle
	rm -f tri_fusion
