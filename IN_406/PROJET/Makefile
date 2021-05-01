run: compile
	./eval "1.1"
	./eval "(1=>(NON(1+0).1)"
	./eval "1.0+1"
	./eval "1.(0+1)"

compile: eval.c
	gcc -o eval eval.c -Wall -g
