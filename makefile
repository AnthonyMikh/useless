utils.o: src/utils.c headers/utils.h headers/shared.h
	gcc -c src/utils.c
useless.o: src/useless.c headers/utils.h
	gcc -c src/useless.c
useless: useless.o utils.o
	gcc *.o -o useless
