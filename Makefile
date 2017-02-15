snake : main.o sprite.o graph.o
	gcc  -lm main.o sprite.o graph.o -lncurses -o snake

main.o : main.c
	gcc -Wall -c main.c -o main.o

algorithm.o : sprite.c sprite.h
	gcc -Wall -c sprite.c -o sprite.o

array.o : graph.c graph.h
	gcc -Wall -c graph.c  -o graph.o


.PHONY : clean


clean: 
	rm -f main.o graph.o sprite.o


