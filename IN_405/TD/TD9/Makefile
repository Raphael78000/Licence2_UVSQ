threads: threads.c
	gcc -o $@ $< -pthread

reduc: reduc.c
	gcc -o$@ $< -pthread

run_threads: threads
	./threads

run_reduc: reduc
	./reduc 4 5 max
