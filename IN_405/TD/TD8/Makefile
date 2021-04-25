#
# Raphael LAZZARI-ARMOUR
# 21920123
# TD04B
# Module IN405 - TD 08
#

.PHONY: all
all: client server

server: server.c
	gcc -o $@ $^ -Wall

client: client.c
	gcc -o $@ $^ -Wall
	
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
