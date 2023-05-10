all: 
	@gcc main.c -Wall -pedantic-errors -c
	@gcc main.o -Wall -pedantic-errors -o main

run:
	./main
