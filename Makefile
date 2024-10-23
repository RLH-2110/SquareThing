
all:
	gcc *.c argParse/*.c -o tables

.PHONY: clear clean run

run: all
	./tables -x 3 5 1 -y 1 7 4 

clear:
	rm tables

clean: clear