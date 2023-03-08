all: 
	@gcc ./utils/utils.c -Wall -pedantic-errors -c
	@gcc main.c -Wall -pedantic-errors -c
	@gcc utils.o main.o -Wall -pedantic-errors -o programa

run:
	./programa
