run: genere algos
	./genere 
	./algos
	
genere: genere.c constantes.h
	gcc genere.c -o genere

algos: algos.c constantes.h
	gcc algos.c -o algos
	
clean:
	rm -f genere 
	rm -f algos 
	rm -f nombres.data 
	rm -f nombres-verif.data
	

