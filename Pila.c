#include <stdlib.h>
#include <stdio.h>
#include "CampoMinato.h"

int push(PilaS *pl, cella *elem){
	PilaS new;
	new = (PilaS)malloc(sizeof (struct nodoS));
	if (new){
		new -> elem = elem;
		new -> next = *pl;
		*pl = new;
		return 1;
	}else {
		return 0;
	}
}

int pop(PilaS *pl, cella *elem){
    if(*pl)
    {
        PilaS copia = *pl;
        elem = copia -> elem;
        *pl = copia -> next;
        free(copia);
        return 1;
    }
    else
        return 0;
}

int is_empty(PilaS pila){
    return (pila == NULL);
}