test: clean compile
	./eval "1.0"
	./eval "(1=>(NON(1+0).1)"
	./eval "1.0+1"
	./eval "1.(0+1)"
	
compile: eval.c
	gcc -o eval eval.c -Wall -g
	
clean:
	rm -f eval
	
FILE = LAZZARI-ARMOUR_Raphael-POULIQUEN_Chloe
zip:
	rm -rf $(FILE)
	mkdir $(FILE)
	cp eval.c Makefile CR.pdf CR.tex $(FILE)
	zip -r $(FILE).zip $(FILE)
	rm -rf $(FILE)
