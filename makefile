CC = gcc
INCLUDES = include
SOURCES = source/*.c
BINARY = ./main
PROG = main.c
FLAGS = -g -lm -Wall -Werror -std=c99 
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full -s

all: clear
	@$(CC) -o $(BINARY) $(PROG) $(SOURCES) -I$(INCLUDES) $(FLAGS)
run: all 
	$(BINARY)
valgrind: all clear 
	valgrind $(VFLAGS) $(BINARY) 
clean:
	rm $(BINARY); rm *.zip
clear:
	clear
debug: all clear
	gdb $(BINARY)
