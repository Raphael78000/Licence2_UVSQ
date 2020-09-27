run: exo8 fichier clean

exo8: exo8.c
	gcc exo8.c -o exo8
	./exo8
		
clean:
	rm -f exo8

fichier: 
	sort -n  -o nombres_tries.data nombres.data
	uniq nombres_tries.data nombres_uniq.data
