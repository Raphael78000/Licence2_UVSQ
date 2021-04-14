
.PHONY: all
all: client server

server: server.c
	gcc -o $@ $^

client: client.c
	gcc -o $@ $^
	
.PHONY: clean
clean: 
	rm -f client
	rm -f server
	
NOM= LAZZARI-ARMOUR_Raphael_TD04B
.PHONY: tar
tar: $(NOM).tar clean

$(NOM).tar: *.c Makefile README.md
	rm -rf $(NOM)
	mkdir $(NOM)
	cp *.c Makefile README.md $(NOM)
	tar -zcvf $@ $(NOM)
	rm -rf $(NOM)
