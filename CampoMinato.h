#ifndef CAMPOMINATO_H
#define CAMPOMINATO_H

#include <ncurses.h>

struct cella {
    int visitato;
    int bomba;
    int bandiera;
    int bombeVicine;
    
    int r;
    int c;
};
typedef struct cella cella;

struct nodoS {
    struct cella *elem;
    struct nodoS *next;
};
typedef struct nodoS* PilaS;

int push(PilaS *pl, cella *elem);
int pop(PilaS *pl, cella *elem);
int is_empty(PilaS pila);

struct campo{
    int righe;
    int colonne;
    int bombeTotali;
    cella** mycampo;
    
    int quantoAnnullare;
    int quanteBandiereMesse;
    int quantiAnnullamentiMassimi;
    PilaS pilaMosse;
};
typedef struct campo campo;


void esci();
int main();



void menuPrincipale();
void SelectMenuPrincipale(int i);



void menuDifficolta();
void SelectMenuDifficolta(int i);
int scegliQuantoAnnullare();



void menuGioco(campo* matrice);
void stampaCasella(WINDOW *h, campo* matrice, int width, int i, int j);
void stampaMatrice(WINDOW *h, campo* matrice);
void stampaInfo(WINDOW *info, int height, campo* matrice);
void stampaLeg(WINDOW *leg, int height);
int mostraMessaggioAnnulla();



void mostraMessaggioVintoOPerso(int vintoOPerso);
void menuUscita(int i);


void menuCreazione();
void SelectMenuCreazione(int i,campo* matrice);



campo* creaMatriceACaso(int righe, int colonne, int bombe, int annullamenti);
void svuotaMatrice(campo* matrice);
cella** crea_campo(int righe, int colonne);



void caricaNumeroBombe(campo* matrice);
int checkVittoria(campo* matrice);
void scopriCampo(campo *matrice, int i, int j);
void annullaMossa(campo* matrice);
void copriCampo(campo *matrice, int i, int j);

int salvaSuFile(campo* mat);
int caricaFilePersonalizzato();


#endif