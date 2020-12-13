all: additionneur
	
test: additionneur
	./additionneur 0x1 0x1
	./additionneur 0xffff 0x1
	./additionneur 1
	./additionneur azerty 1
	./additionneur ffffffff 1

	
additionneur: additionneur.c
	gcc -o additionneur additionneur.c -lm

clean:
	rm additionneur
