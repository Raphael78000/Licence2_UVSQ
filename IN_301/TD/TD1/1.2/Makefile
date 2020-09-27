run: exo8
	./exo8

exo8: exo8.c
	gcc exo8.c -o exo8
		
clean: 
	rm -f nombres.data
	rm -f nombres_tries.data
	rm -f nombres_uniq.data
	rm -f nombres-verif.data
	rm -f exo8

fichier: 
	sort -n  -o nombres_tries.data nombres.data
	uniq nombres_tries.data nombres_uniq.data
