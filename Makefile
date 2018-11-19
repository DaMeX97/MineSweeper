CampoMinato : CampoMinato.o Gioco.o Pila.o
	gcc -std=gnu89 -pedantic -Wall CampoMinato.o Gioco.o Pila.o -lncurses -o CampoMinato

Pila.o : Pila.c CampoMinato.h
	gcc -c -std=gnu89 -pedantic -Wall Pila.c -o Pila.o

Gioco.o : Gioco.c CampoMinato.h
	gcc -c -std=gnu89 -pedantic -Wall Gioco.c -o Gioco.o

CampoMinato.o : CampoMinato.c CampoMinato.h
	gcc -c -std=gnu89 -pedantic -Wall CampoMinato.c -o CampoMinato.o
