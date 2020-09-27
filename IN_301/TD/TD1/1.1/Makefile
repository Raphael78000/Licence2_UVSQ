run: genere algos clean
	
genere: genere.c constantes.h
	gcc genere.c -o genere
	./genere 

algos: algos.c constantes.h
	gcc algos.c -o algos
	./algos
	
clean:
	rm -f genere 
	rm -f algos 
	rm -f nombres.data 
	rm -f nombres-verif.data
	

