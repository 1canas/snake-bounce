all: 
	@gcc utils.c -Wall -pedantic-errors -c
	@gcc main_temp.c -Wall -pedantic-errors -c
	@gcc utils.o main_temp.o -Wall -pedantic-errors -o programa

run:
	./programa
