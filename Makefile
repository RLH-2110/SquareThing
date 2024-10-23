
all:
	gcc *.c argParse/*.c -o tables

.PHONY: clear clean run

run: all
	./tables -x 3 5 1 -y 1 7 4 

runa: all
	./tables -a -x 2 3 7 6 -y 5 13 

clear:
	rm tables

clean: clear