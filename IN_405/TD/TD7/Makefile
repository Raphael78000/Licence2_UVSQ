
run: aff new
	echo ready
	
aff: aff.c cst.h
	gcc -c aff.c
	gcc -o aff aff.o
	
new: new.c cst.h
	gcc -c new.c
	gcc -o new new.o
	
clean: 
	rm new
	rm aff
	rm *.o
