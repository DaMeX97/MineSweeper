#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <ncurses.h>
#include "CampoMinato.h"


/* MENU PRINCIPALE */

void menuPrincipale()
{ 
    int flag = 1;
    int MenuElements = 12;
    char list[12][51] = { "              ____ _ ____ ____ ____              ", "              | __ | |  | |    |__|              ","              |__] | |__| |___ |  |              ", "                                                  ", "               ____ ____ ____ ____             ", "               |    |__] |___ |__|             ",  "               |___ |  ) |___ |  |             ",  "                                                  ", "                ____ ____ ____ _            ", "                |___ [__  |    |            ", "                |___ ___] |___ |            ", "                                    "}; /* Array delle scritte a schermo */
    char item[51];
    int ch, i = 0;
    
    int row, col;
    
    WINDOW *titolo;
    WINDOW *w;
 
    /* Inizializzo NCURSES */
    initscr();
    start_color();
    getmaxyx(stdscr, row, col);
    
    /* creo una nuova finestra */
    
    attron(A_BOLD);
    titolo = newwin( 8, 73, 5, col/2 - 73/2); 
    
    /* metto i colori */
    
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(9, COLOR_BLACK, COLOR_YELLOW);
    
    /* Stampo il titolo in alto */
    mvwprintw( titolo, 1, 1, "    ______                               __  __ _             __       "); 
    mvwprintw( titolo, 2, 1, "   / ____/___ _____ ____ _____ _____    /  |/  (_)____ ______/ /_______"); 
    mvwprintw( titolo, 3, 1, "  / /   / __  / __ `__  / __  / __  /  / /|_/ / / __  / __  / __/ __  /"); 
    mvwprintw( titolo, 4, 1, " / /___/ /_/ / / / / / / /_/ / /_/ /  / /  / / / / / / /_/ / /_/ /_/ / "); 
    mvwprintw( titolo, 5, 1, "/____//___,_/_/ /_/ /_/ ____/_____/  /_/  /_/_/_/ /_/___,_/___/_____/  "); 
    mvwprintw( titolo, 6, 1, "                     /_/                                               "); 
    
    box(titolo, 0,0); /* creo il bordo */
    wbkgd(titolo, COLOR_PAIR(9)); /* metto il colore di sfondo */
    
    wrefresh(titolo);
    
    /* creo finestra del menù */
    w = newwin(14, 53, row/2 - 14/2, col/2 - 53/2); 
    
    /* Coloro lo sfondo della finestra */
    
    wbkgd(w, COLOR_PAIR(1));

    /* Metto bordo alla finestra */
    
    box( w, 0, 0 ); 
     
    /* Stampo gli elementi e sottolineo il primo */
    for( i=0; i< MenuElements; i++ ) {
        if(i < 4) 
            wattron( w, A_STANDOUT );
        else
            wattroff( w, A_STANDOUT );
        sprintf(item, "%-51s",  list[i]);
        mvwprintw( w, i+1, 1, "%s", item );
    }
    
    /* Refresho il terminale */
 
    wrefresh( w );
 
    i = 0;
    
    /* Disabilito stampa caratteri */
    
    noecho();
    /* Abilito i tasti */
    keypad(w, TRUE);
    
    /* Disabilito cursore */
    curs_set( 0 ); 
    
    /* Prendo gli input dei tasti */
    flag = 1;
    while(flag && ( ch = wgetch(w))){ 
        beep(); /* Beep per far capire che mi son mosso */
        /* Per disabilitare questa sottolineatura ci ristampo sopra */
        sprintf(item, "%-51s",  list[i]); 
        mvwprintw( w, i+1,1, "%s", item ); 
        
        sprintf(item, "%-51s",  list[i+1]); 
        mvwprintw( w, i+2,1, "%s", item ); 
        
        sprintf(item, "%-51s",  list[i+2]); 
        mvwprintw( w, i+3,1, "%s", item ); 
        
        sprintf(item, "%-51s",  list[i+3]); 
        mvwprintw( w, i+4,1, "%s", item ); 
        
        /* controllo che tasto ha premuto */
        switch( ch ) {
            case KEY_UP: /* freccia in su */
                i-=4;
                i = ( i<0 ) ? MenuElements-4 : i;
                break;
            case KEY_DOWN: /* freccia in giù */
                i+=4;
                i = ( i > (MenuElements-1) ) ? 0 : i;
                break;
            case 10: /* invio */
                flag = 0;
                break;
        }
        /* Sottolineo menù nuovo */
        wattron( w, A_STANDOUT ); 
        sprintf(item, "%-51s",  list[i]); 
        mvwprintw( w, i+1,1, "%s", item ); 
        
        sprintf(item, "%-51s",  list[i+1]); 
        mvwprintw( w, i+2,1, "%s", item ); 
        
        sprintf(item, "%-51s",  list[i+2]); 
        mvwprintw( w, i+3,1, "%s", item ); 
        
        sprintf(item, "%-51s",  list[i+3]); 
        mvwprintw( w, i+4,1, "%s", item ); 
        
        wattroff( w, A_STANDOUT );
    }
    
    /* cancello questa finestra */
    delwin(w);
    delwin(titolo);
    endwin();
    clear();
    refresh();
    
    SelectMenuPrincipale(i/4); /* Vediamo in quale selezione ha premuto */
}

/* Dove ha premuto invio nella sezione principale? */
void SelectMenuPrincipale(int i)
{    
    /* menù principale */
    switch(i)
    {
        case 0:
            /* Ho premuto GIOCA */
            menuDifficolta();
            break;
        case 1:
            /* Ho premuto GENERA */
            menuCreazione();
            break;
        case 2:
            /* Ho premuto ESCI */
            esci();
            break;
    }
}

/* INIZIA MENU DELLE DIFFICOLTA */

void menuDifficolta()
{    
    int DiffElements = 20;
    char list[20][76] = { "                         ____ ____ ____ _ _    ____                        ", "                         |___ |__| |    | |    |___                        ", "                         |    |  | |___ | |___ |___                        ", "                                                                           ","                           _  _ ____ ___  _ ____                           ", "                           |][| |___ |  ] | |  |                           ", "                           |  | |___ |__] | |__|                           ", "                                                                           ","                    ___  _ ____ ____ _ ____ _ _    ____                    ", "                    |  ] | |___ |___ | |    | |    |___                    ", "                    |__] | |    |    | |___ | |___ |___                    ", "                                                                           ","     ___  ____ ____ ____ ____ _  _ ____ _    _ ___  ___  ____ ___ ____     ", "     |__] |___ |__] [__  |  | | /| |__| |    |   /    /  |__|  |  |  |     ", "     |    |___ |  ) ___] |__| |/ | |  | |___ |  /__  /__ |  |  |  |__|     ", "                                                                           ","                      _ _  _ ___  _ ____ ___ ____ ____                     ", "                      | | /| |  ] | |___  |  |__] |  |                     ", "                      | |/ | |__] | |___  |  |  ) |__|                     ", "                                                                           "}; /* Array stampe selezioni */
    
    /* inizializzo variabili */
    char item[76];
    int ch, i = 0;
    
    int row, col;
    
    int flag = 1;
    
    WINDOW *titolo;
    WINDOW *diff;

    getmaxyx(stdscr, row, col);
    
    /* creo finestra titolo */
    titolo = newwin( 8, 47, 5, col/2 - 47/2);
    
    init_pair(2, COLOR_BLACK, COLOR_GREEN); /* colori */
    init_pair(10, COLOR_BLACK, COLOR_YELLOW);
    
    
    /* stampo titolo */
    mvwprintw( titolo, 1, 1, "    _____ _ ______  _            ____   ___ "); 
    mvwprintw( titolo, 2, 1, "   / __  (_) __/ _/(_)__________/ / /___)__)"); 
    mvwprintw( titolo, 3, 1, "  / / / / / /_/ /_/ / ___/ __  / / __/ __  /"); 
    mvwprintw( titolo, 4, 1, " / /_/ / / __/ __/ / /__/ /_/ / / /_/ /_/ / "); 
    mvwprintw( titolo, 5, 1, "/_____/_/_/ /_/ /_/____/_____/_/___/___,_/  "); 
    mvwprintw( titolo, 6, 1, "                                            "); 
    
    /* metto box e colore di sfondo */
    box(titolo, 0,0);
    wbkgd(titolo, COLOR_PAIR(10));
    wrefresh(titolo);
    
    /* creo una nuova finestra */
    
    diff = newwin(22, 78, row/2 - 22/2, col/2 - 78/2); 
    
    /* Coloro lo sfondo della finestra */
    
    wbkgd(diff, COLOR_PAIR(2));

    /* Metto bordo alla finestra */
    
    box( diff, 0, 0 ); 
     
    /* Stampo gli elementi e sottolineo il primo */
    for( i=0; i< DiffElements; i++ ) {
        if( i < 4 ) 
            wattron( diff, A_STANDOUT );
        else
            wattroff( diff, A_STANDOUT );
        sprintf(item, "%-76s",  list[i]);
        mvwprintw( diff, i+1, 1, "%s", item );
    }
    
    /* Refresho il terminale */
 
    wrefresh(diff);
 
    i = 0;
    
    /* Disabilito stampa caratteri */
    
    noecho();
    /* Abilito i tasti */
    keypad(diff, TRUE);
    
    /* Disabilito cursore */
    curs_set( 0 ); 
    
    /* Prendo gli input dei tasti */
    flag = 1;
    while(flag && ( ch = wgetch(diff))){
        beep(); /* Beep per far capire che mi son mosso */
        
        /* Per disabilitare questa sottolineatura */
        sprintf(item, "%-76s",  list[i]); 
        mvwprintw( diff, i+1,1, "%s", item ); 
        
        sprintf(item, "%-76s",  list[i+1]); 
        mvwprintw( diff, i+2,1, "%s", item ); 
        
        sprintf(item, "%-76s",  list[i+2]); 
        mvwprintw( diff, i+3,1, "%s", item ); 
        
        sprintf(item, "%-76s",  list[i+3]); 
        mvwprintw( diff, i+4,1, "%s", item );
        /* Che tasto ha premuto? */
        switch( ch ) {
            case KEY_UP: /* Freccia su */
                i-= 4;
                i = ( i<0 ) ? DiffElements-4 : i;
                break;
            case KEY_DOWN: /* Giù */
                i+= 4;
                i = ( i > (DiffElements-1) ) ? 0 : i;
                break;
            case 10: /* Invio */
                flag = 0;
                break;
        }

        /* Sottolineo menù nuovo */
        wattron(diff, A_STANDOUT );    
        
        sprintf(item, "%-76s",  list[i]); 
        mvwprintw( diff, i+1,1, "%s", item ); 
        
        sprintf(item, "%-76s",  list[i+1]); 
        mvwprintw( diff, i+2,1, "%s", item ); 
        
        sprintf(item, "%-76s",  list[i+2]); 
        mvwprintw( diff, i+3,1, "%s", item ); 
        
        sprintf(item, "%-76s",  list[i+3]); 
        mvwprintw( diff, i+4,1, "%s", item ); 
        
        wattroff( diff, A_STANDOUT );
    }
    
    wrefresh(diff);
    
    /* Cancello la window e vado a vedere cosa ho premuto */
    delwin(diff);
    delwin(titolo);
    endwin();
    clear();
    refresh();
    
    SelectMenuDifficolta(i/4);
}

void SelectMenuDifficolta(int i)
{    
    /* menù difficoltà */
    campo* mat;
    switch(i)
    {
        case 0:
            /* Ho premuto facile */
            mat = creaMatriceACaso(10, 10, 15, 5);
            menuGioco(mat);
            break;
        case 1:
            /* Medio */
            mat = creaMatriceACaso(15, 15, 30, 5);
            menuGioco(mat);
            break;
        case 2:
            /* Difficile */
            mat = creaMatriceACaso(25, 25, 75, 5);
            menuGioco(mat);
            break;
        case 3:
            /* Personalizzato */
            mat = (campo*)malloc(sizeof(campo));
            caricaFilePersonalizzato(mat);
            menuGioco(mat);
            break;
        case 4:
            /* Indietro */
            menuPrincipale();
            break;
    }
}

int scegliQuantoAnnullare() /* Finestra che chiede quanto deve annullare */
{
    /* creo una nuova finestra */
    
    int annullamenti = -1;
    
    /* creo finestra */
    WINDOW *chiedi = newwin(8, 132, LINES/2-8/2, COLS/2 - 132/2); 
    
    init_pair(11, COLOR_BLACK, COLOR_GREEN); /* Colori */
    wbkgd(chiedi, COLOR_PAIR(11));
    
    box(chiedi, 0,0); /* bordo */
    
    echo();
    /* Abilito i tasti*/
    keypad(chiedi, TRUE);
    
    /* Abilito cursore */
    curs_set(1); 
    
    /* stampo scritte */
    mvwprintw(chiedi, 1, 1, "____ _  _ ____ _  _ ___ _    ____ _  _ _  _ _  _ _    _    ____ _  _ ____ _  _ ___ _    _ _ _  _ ____ _    ____ ____ ____ ____ __ ");
    mvwprintw(chiedi, 2, 1, "|  | |  | |__| | /|  |  |    |__| | /| | /| |  | |    |    |__| |][| |___ | /|  |  |    | | |  | |  | |    |___ |__| |__/ |___  _]");
    mvwprintw(chiedi, 3, 1, "|_,| |__| |  | |/ |  |  |    |  | |/ | |/ | |__| |___ |___ |  | |  | |___ |/ |  |  |     V  |__| |__| |    |    |  | |  ) |___  . ");
    mvwprintw(chiedi, 4, 1, "                                                           (da 0 a 10)                                                            ");
    
    wrefresh(chiedi);
    
    /* Chiedo quanto vuole annullare */
    do{
        mvwprintw(chiedi, 6, 132/2 - 1, "                ");
        mvwscanw(chiedi, 6, 132/2 - 1, "%d", &annullamenti);
    }while(annullamenti < 0 || annullamenti > 10);
    
    curs_set(0); /* Disabilito cursore */
    
    /* Ridisabilito stampa */
    noecho();
    
    /* cancello window e ritorno il quanto vuole annullare */
    delwin(chiedi);
    endwin();
    clear();
    refresh();
    
    return annullamenti;
}

/* GIOCO */


void menuGioco(campo* matrice) /* Grafica di gioco */
{
    /* Inizializzo variabili */
    int ch, i = 0;
    
    int j;
    
    int row, col;
    
    int height, width;
    
    WINDOW *h, *leg, *info;
    
    int flag = 1;
    int vintoOPerso = 0;
    int cosaDevoFare = 0;
 
    getmaxyx(stdscr, row, col);
    
    height = matrice->righe * 2 - 1 + 7;
    width = matrice->colonne*4 + 2;
    
    /* creo nuove finestra */
    
    h = newwin(height, width, row/2 - height/2, col/2 - width/2); 
    
    leg = newwin(height, (col-width)/2, row/2 - height/2, 0);
    
    info = newwin(height, (col-width)/2, row/2 - height/2, col/2 + width/2);
    
    /* Coloro lo sfondo della finestra */
    
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(7, COLOR_BLACK, COLOR_YELLOW);
    wbkgd(h, COLOR_PAIR(3));

    stampaLeg(leg, height); /* Stampo leg */
    
    stampaInfo(info, height, matrice); /* Stampo info gioco */

    /* Metto bordo alla finestra */
    
    box(h, 0, 0 ); 
    
    /* Stampo caselle */
    for(i = 0; i < matrice->righe; i++)
    {
        for(j = 0; j < matrice->colonne; j++)
        {
            if(i == 0 && j == 0)
                wattron( h, A_STANDOUT);
            else wattroff( h, A_STANDOUT);
            
            mvwprintw( h, i*2+1, (j*4) + 1, "%-3s", "[ ]");
        }
    }
    
    /* Stampo bordo inferiore */
    for(j = 1; j < width-1; j++)
    {
        mvwprintw(h, i*2, j, "_");   
    }
    
    /* Stampo pulsante esci */
    mvwprintw(h, i*2+1, width - 17 - 1, "%-17s", "____ ____ ____ _ ");
    mvwprintw(h, i*2+2, width - 17 - 1, "%-17s", "|___ [__  |    | ");
    mvwprintw(h, i*2+3, width - 17 - 1, "%-17s", "|___ ___] |___ | ");
    mvwprintw(h, i*2+4, width - 17 - 1, "%-17s", "                 ");
    
    
    /* Refresho il terminale */
 
    wrefresh( h );
    
    refresh();
 
    i = 0, j = 0;
    
    /* Disabilito stampa caratteri */
    
    noecho();
    /* Abilito i tasti */
    keypad(h, TRUE);
    
    /* Disabilito cursore */
    curs_set( 0 );
    
    /* Prendo gli input dei tasti */
    flag = 1;
    vintoOPerso = 0;
    cosaDevoFare = 0;
    while(flag && ( ch = wgetch(h))){
        stampaCasella(h, matrice, width, i, j); /* Ristampo casella per togliere selezione */
        switch( ch ) {
            case KEY_UP: /* Ho premuto freccia in su */
                beep(); /* Beep per far capire che mi son mosso */
                if(j == matrice->colonne){
                    i = matrice->righe-1;
                    j--;
                }else{
                    i--;
                    i = (i < 0) ? matrice->righe - 1 : i;
                }
                break;
                
            case KEY_DOWN: /* Ho premuto freccia giù */
                beep(); /* Beep per far capire che mi son mosso */
                if(j == matrice->colonne){
                    i = 0;
                    j--;
                }else{
                    i++;
                    i = (i > matrice->righe-1) ? 0 : i;
                }
                break;
                
            case KEY_LEFT: /* Sinistra */
                beep(); /* Beep per far capire che mi son mosso */
                if(i != matrice->righe){                
                    j--;
                    j = (j < 0) ? matrice->colonne - 1 : j;
                }
                break;
                
            case KEY_RIGHT: /* Destra */
                beep(); /* Beep per far capire che mi son mosso */
                if(i != matrice->righe){                  
                    j++;
                    j = (j > matrice->colonne-1) ? 0 : j;
                }
                break;
                
            case 9: /* Tab */
                beep(); /* Beep per far capire che mi son mosso */
                if(i == matrice->righe){
                    i = 0;
                    j = 0;
                }
                else{
                    i = matrice->righe;
                    j = 1;
                }
                break;
            case 10: /* Invio */
                if(i == matrice->righe){ /* Significa che devo uscire */
                    flag = 0;
                    cosaDevoFare = 1;
                    beep(); /* Beep per far capire che mi son mosso */
                }else{
                     /* Devo scoprire, sono nella matrice */                    
                    if(!((matrice->mycampo)[i][j]).bandiera){ /* Se non c'è la bandiera vedo cosa fare */
                        beep(); /* Beep per far capire che mi son mosso */
                        push(&(matrice->pilaMosse), &((matrice->mycampo)[i][j])); /* Inserisco nella pila delle mosse */
                        if(!((matrice->mycampo)[i][j]).bomba){ /* Se non c'è bomba scopro le celle e controllo se ho vinto */
                            ((matrice->mycampo)[i][j]).visitato = 1;
                            scopriCampo(matrice, i, j);

                            flag = !checkVittoria(matrice);
                            vintoOPerso = !flag;

                            stampaMatrice(h, matrice); /* Ristampo matrice */
                        }else{ /* Altrimenti ho trovato una bomba */
                            int ris = 1;

                            /* Se posso gli chiedo se vuole annullare */
                            if(matrice->quantiAnnullamentiMassimi > 0)
                                ris = mostraMessaggioAnnulla();

                            if(ris == 0){
                                /* ANNULLO */
                                annullaMossa(matrice);
                                matrice->quantiAnnullamentiMassimi--;
                            }
                            else{
                                /* metto flag a 0 e gli dirò che ha perso */
                                flag = 0;
                            }

                            wbkgd(h, COLOR_PAIR(3));

                            /* Ristampo tutto */
                            stampaLeg(leg, height);
                            stampaInfo(info, height, matrice);
                            stampaMatrice(h, matrice);
                        }
                    }
                }
                break;
            case ' ':   /* Ho premuto spazio, se c'è la bandiera la tolgo altrimento se non c'è la metto */ 
                beep(); /* Beep per far capire che mi son mosso */beep(); /* Beep per far capire che mi son mosso */
                if(((matrice->mycampo)[i][j]).bandiera == 1 && ((matrice->mycampo)[i][j]).visitato == 0){
                    ((matrice->mycampo)[i][j]).bandiera = (((matrice->mycampo)[i][j]).bandiera == 1) ? 0 : 1;
                    matrice->quanteBandiereMesse--;
                }
                else if(((matrice->mycampo)[i][j]).bandiera == 0 && ((matrice->mycampo)[i][j]).visitato == 0){
                    if(matrice->quanteBandiereMesse < matrice->bombeTotali){
                        ((matrice->mycampo)[i][j]).bandiera = (((matrice->mycampo)[i][j]).bandiera == 1) ? 0 : 1;
                        matrice->quanteBandiereMesse++;
                    }
                }
                
                /* Ristampo info */
                stampaInfo(info, height, matrice);
                break;
        }
        
        /* Ristampo casella/esci selezionata/o  */
        wattron(h, A_STANDOUT );
        stampaCasella(h, matrice, width, i, j);
        wattroff( h, A_STANDOUT);
        refresh();
    }
    
    /* Cancello tutto */
    delwin(h);
    delwin(info);
    delwin(leg);
    endwin();
    clear();
    refresh();
    
    /* Libero la matrice */
    svuotaMatrice(matrice);
    
    /* Devo mostrare vinto o perso oppure se ha premuto esci devo tornare al menù principale */
    if(cosaDevoFare == 0) 
        mostraMessaggioVintoOPerso(vintoOPerso);
    else menuPrincipale();
}

void stampaCasella(WINDOW *h, campo* matrice, int width, int i, int j) /* Funzione che stampa la singola selezione (casella oppure il tasto esci) */
{
    if(i == matrice->righe && j == 1){
        mvwprintw(h, i*2+1, width - 17 - 1, "%-17s", "____ ____ ____ _ ");
        mvwprintw(h, i*2+2, width - 17 - 1, "%-17s", "|___ [__  |    | ");
        mvwprintw(h, i*2+3, width - 17 - 1, "%-17s", "|___ ___] |___ | ");
        mvwprintw(h, i*2+4, width - 17 - 1, "%-17s", "                 ");
    }
    else 
    {
        cella temp = (matrice->mycampo)[i][j];
        if(temp.visitato == 0 && temp.bandiera == 0)
            mvwprintw( h, i*2+1, (j*4) + 1, "%-3s", "[ ]");
        else if(temp.visitato == 0 && temp.bandiera == 1)
            mvwprintw( h, i*2+1, (j*4) + 1, "%-3s", "[>]");
        else if(temp.bomba == 1)
            mvwprintw( h, i*2+1, (j*4) + 1, "[*]");
        else if(temp.bombeVicine > 0)
            mvwprintw( h, i*2+1, (j*4) + 1, "[%d]", temp.bombeVicine);
        else mvwprintw( h, i*2+1, (j*4) + 1, "   ");
    }
}

void stampaMatrice(WINDOW *h, campo* matrice) /* Funzione che ristampa tutta la matrice */
{
    int q, p;
    for(q = 0; q < matrice->righe; q++)
    {
        for(p = 0; p < matrice->colonne; p++)
        {
            cella temp = (matrice->mycampo)[q][p];

            wattroff( h, A_STANDOUT);

            if(temp.visitato == 0 && temp.bandiera == 0)
                mvwprintw( h, q*2+1, (p*4) + 1, "%-3s", "[ ]");
            else if(temp.visitato == 0 && temp.bandiera == 1)
                mvwprintw( h, q*2+1, (p*4) + 1, "%-3s", "[>]");
            else if(temp.bomba == 1)
                mvwprintw( h, q*2+1, (p*4) + 1, "[*]");
            else if(temp.bombeVicine > 0)
                mvwprintw( h, q*2+1, (p*4) + 1, "[%d]", temp.bombeVicine);
            else mvwprintw( h, q*2+1, (p*4) + 1, "   ");
        }
    }
}

void stampaInfo(WINDOW *info, int height, campo* matrice) /* Funzione che stampa le info del gioco */
{
    /* Coloro lo sfondo della finestra */

    wbkgd(info, COLOR_PAIR(7));
    
    /* Mette il bordo */
    box(info, 0, 0);
    
    mvwprintw(info, height/7 * 1, 1, "RIGHE:   ");
    mvwprintw(info, height/7 * 2, 1, "COLONNE:   ");
    mvwprintw(info, height/7 * 3, 1, "BOMBE:    ");
    mvwprintw(info, height/7 * 4, 1, "ANNULLAMENTI RIMASTI:   ");
    mvwprintw(info, height/7 * 5, 1, "MOSSE CHE VENGONO ANNULLATE:   ");
    mvwprintw(info, height/7 * 6, 1, "BANDIERE RIMASTE:    ");
    
    mvwprintw(info, height/7 * 1, 1, "RIGHE: %d", matrice->righe);
    mvwprintw(info, height/7 * 2, 1, "COLONNE: %d", matrice->colonne);
    mvwprintw(info, height/7 * 3, 1, "BOMBE: %d", matrice->bombeTotali);
    mvwprintw(info, height/7 * 4, 1, "ANNULLAMENTI RIMASTI: %d", matrice->quantiAnnullamentiMassimi);
    mvwprintw(info, height/7 * 5, 1, "MOSSE CHE VENGONO ANNULLATE: %d", matrice->quantoAnnullare);
    mvwprintw(info, height/7 * 6, 1, "BANDIERE RIMASTE: %d", matrice->bombeTotali - matrice->quanteBandiereMesse);
    
    wrefresh(info);
}

void stampaLeg(WINDOW *leg, int height) /* Funzione che stampa la legenda */
{
    wbkgd(leg, COLOR_PAIR(7));
    
    box(leg, 0, 0);
    
    mvwprintw(leg, height/5 * 1, 1, "INVIO: PER SCOPRIRE UNA CELLA.");
    mvwprintw(leg, height/5 * 2, 1, "TAB: PER ANDARE NELLA BARRA INFERIORE.");
    mvwprintw(leg, height/5 * 3, 1, "SPAZIO: PER METTERE O TOGLIERE UNA BANDIERA.");
    mvwprintw(leg, height/5 * 4, 1, "FRECCETTE: PER SPOSTARSI NELLE VARIE DIREZIONI.");
    
    wrefresh(leg);
}

int mostraMessaggioAnnulla() /* Funzione che chiede se vuole annullare */
{
    int ch;
    
    int i = 0;
    int flag = 1;
    /* creo una nuova finestra */
    
    WINDOW *chiedi = newwin(14, 96, LINES/2-14/2, COLS/2 - 96/2); 
    
    init_pair(6, COLOR_BLACK, COLOR_YELLOW);
    wbkgd(chiedi, COLOR_PAIR(6));
    
    box(chiedi, 0,0);
    
    noecho();
    /* Abilito i tasti */
    keypad(chiedi, TRUE);
    
    /* Disabilito cursore */
    curs_set(0); 
    
    /* Stampo tutto */
    mvwprintw(chiedi, 1, 1, "_  _ ____ _    ___ ____ ____ _ _ ____ ___ ____    _  _ _  _ ____    ___  ____ _  _ ___  ____  ");
    mvwprintw(chiedi, 2, 1, "|__| |__| |     |  |__/ |  | | | |__|  |  |  |    |  | | /| |__|    |__] |  | |][| |__] |__|  ");
    mvwprintw(chiedi, 3, 1, "|  | |  | |     |  |  ) |__|  V  |  |  |  |__|    |__| |/ | |  |    |__] |__| |  | |__] |  | .");
    mvwprintw(chiedi, 4, 1, "                                                                                              ");
    
    mvwprintw(chiedi, 5, (96 - 67 - 1)/2, "_ _ _  _ ____ _    ____ _  _ _  _ _  _ _    _    ____ ____ ____ __ ");
    mvwprintw(chiedi, 6, (96 - 67 - 1)/2, "| | |  | |  | |    |__| | /| | /| |  | |    |    |__| |__/ |___  _]");
    mvwprintw(chiedi, 7, (96 - 67 - 1)/2, " V  |__| |__| |    |  | |/ | |/ | |__| |___ |___ |  | |  ) |___  . ");
    mvwprintw(chiedi, 8, (96 - 67 - 1)/2, "                                                                   ");
    
    wattron(chiedi, A_STANDOUT);
    mvwprintw(chiedi, 9 , 1, " ____ _ ");
    mvwprintw(chiedi, 10, 1, " [__  | ");
    mvwprintw(chiedi, 11, 1, " ___] | ");
    mvwprintw(chiedi, 12, 1, "        ");

    wattroff(chiedi, A_STANDOUT);
    mvwprintw(chiedi, 9 , (96 - 11 - 1), " _  _ ____ ");
    mvwprintw(chiedi, 10, (96 - 11 - 1), " | /| |  | ");
    mvwprintw(chiedi, 11, (96 - 11 - 1), " |/ | |__| ");
    mvwprintw(chiedi, 12, (96 - 11 - 1), "           ");
    
    i = 0;
    flag = 1;
    while(flag && (ch = wgetch(chiedi))){ 
        beep(); /* Beep per far capire che mi son mosso */
        /* Ristampo per togliere selezione */
        if(i == 0){
            mvwprintw(chiedi, 9 , 1, " ____ _ ");
            mvwprintw(chiedi, 10, 1, " [__  | ");
            mvwprintw(chiedi, 11, 1, " ___] | ");
            mvwprintw(chiedi, 12, 1, "        ");
        }else{
            mvwprintw(chiedi, 9 , (96 - 11 - 1), " _  _ ____ ");
            mvwprintw(chiedi, 10, (96 - 11 - 1), " | /| |  | ");
            mvwprintw(chiedi, 11, (96 - 11 - 1), " |/ | |__| ");
            mvwprintw(chiedi, 12, (96 - 11 - 1), "           ");
        }
        
        /* Cosa ha premuto? */
        switch( ch ) {
            case KEY_LEFT:
                /* sinistra */
                i = (i == 0) ? 1 : 0;
                break;
            case KEY_RIGHT:
                /* destra */
                i = (i == 0) ? 1 : 0;
                break;
            case 10:
                /* invio */
                flag = 0;
                break;
        }
        
        /* ristrampo selezione */
        wattron(chiedi, A_STANDOUT);
        if(i == 0){
            mvwprintw(chiedi, 9 , 1, " ____ _ ");
            mvwprintw(chiedi, 10, 1, " [__  | ");
            mvwprintw(chiedi, 11, 1, " ___] | ");
            mvwprintw(chiedi, 12, 1, "        ");
        }else{
            mvwprintw(chiedi, 9 , (96 - 11 - 1), " _  _ ____ ");
            mvwprintw(chiedi, 10, (96 - 11 - 1), " | /| |  | ");
            mvwprintw(chiedi, 11, (96 - 11 - 1), " |/ | |__| ");
            mvwprintw(chiedi, 12, (96 - 11 - 1), "           ");
        }
        wattroff(chiedi,A_STANDOUT);
    }
    
    /* Cancello tutto e ritorno 0 se ha premuto si, 1 se ha premuto no */
    delwin(chiedi);
    endwin();
    clear();
    refresh();
    
    return i;
}

/* MENU VINTO O PERSO */

void mostraMessaggioVintoOPerso(int vintoOPerso) /* Funzione che stampa se ha vinto o perso dato 0 o 1 */
{
    int ch;
    
    int i = 0;
    int flag = 1;
    
    /* creo una nuova finestra */
    
    WINDOW *casella = newwin(13, 52, LINES/2-13/2, COLS/2 - 52/2); 
    
    /* Coloro lo sfondo della finestra */
    
    init_pair(4, COLOR_BLACK, COLOR_GREEN);
    wbkgd(casella, COLOR_PAIR(4));

    /* Metto bordo alla finestra */
    
    box( casella, 0, 0 ); 
    
    if(vintoOPerso){ 
        /* HA VINTO */
        mvwprintw(casella, 1, 1, "      __  __     _          _       __        __  ");
        mvwprintw(casella, 2, 1, "     / / / /___ (_)  _   __(_)____ / / ______/ /  ");
        mvwprintw(casella, 3, 1, "    / /_/ / __ / /  | | / / / __  / __/ __  / /   ");
        mvwprintw(casella, 4, 1, "   / __  / /_// /   | |/ / / / / / /_/ /_/ /_/    ");
        mvwprintw(casella, 5, 1, "  /_/ /_/__,_/_/    |___/_/_/ /_/__/______(_)     ");
        mvwprintw(casella, 6, 1, "                                                  ");   
    }
    else{ 
        /* HA PERSO */
        mvwprintw(casella, 1, 1, "    __  __      _                               __");
        mvwprintw(casella, 2, 1, "   / / / /____ (_)  ____  ____ _______________ / /");
        mvwprintw(casella, 3, 1, "  / /_/ / __  / /  / __  / _  / ___/ ___/ __  / / ");
        mvwprintw(casella, 4, 1, " / __  / /_/ / /  / /_/ /  __/ /  (__  ) /_/ /_/  ");
        mvwprintw(casella, 5, 1, "/_/ /_/__,___/_/ / ___/ ____/_/  /____/____ (_)   ");
        mvwprintw(casella, 6, 1, "                /_/                               "); 
    }
    
    /* Stampa i pulsanti */
    wattron(casella, A_STANDOUT);
    mvwprintw(casella, 8 , 1, "   ____ ____ ____ _    ");
    mvwprintw(casella, 9 , 1, "   |___ [__  |    |    ");
    mvwprintw(casella, 10, 1, "   |___ ___] |___ |    ");
    mvwprintw(casella, 11, 1, "                       ");
    wattroff(casella, A_STANDOUT);
    mvwprintw(casella, 8 , 26, "  _  _ ____ _  _ _  _ . ");
    mvwprintw(casella, 9 , 26, "  |][| |___ | /| |  |'  ");
    mvwprintw(casella, 10, 26, "  |  | |___ |/ | |__|   ");
    mvwprintw(casella, 11, 26, "                        ");
    
    /* Refresho il terminale */
 
    wrefresh( casella );
    
    /* Disabilito stampa caratteri */
    
    noecho();
    /* Abilito i tasti */
    keypad(casella, TRUE);
    
    /* Disabilito cursore */
    curs_set(0); 
    
    i = 0;
    flag = 1;
    while(flag && (ch = wgetch(casella))){ 
        beep(); /* Beep per far capire che mi son mosso */
        /* Ristampo per togliere selezione */
        if(i == 0){
            mvwprintw(casella, 8 , 1, "   ____ ____ ____ _    ");
            mvwprintw(casella, 9 , 1, "   |___ [__  |    |    ");
            mvwprintw(casella, 10, 1, "   |___ ___] |___ |    ");
            mvwprintw(casella, 11, 1, "                       ");
        }else{
            mvwprintw(casella, 8 , 26, "  _  _ ____ _  _ _  _ . ");
            mvwprintw(casella, 9 , 26, "  |][| |___ | /| |  |'  ");
            mvwprintw(casella, 10, 26, "  |  | |___ |/ | |__|   ");
            mvwprintw(casella, 11, 26, "                        ");
        }
        /* Cosa ha premuto? */
        switch( ch ) {
            case KEY_LEFT:
                /* sinistra */
                i = (i == 0) ? 1 : 0;
                break;
            case KEY_RIGHT:
                /* destra */
                i = (i == 0) ? 1 : 0;
                break;
            case 10:
                /* invio */
                flag = 0;
                break;
        }
        
        /* Ristampo selezionando il nuovo */
        wattron(casella, A_STANDOUT);
        if(i == 0){
            mvwprintw(casella, 8 , 1, "   ____ ____ ____ _    ");
            mvwprintw(casella, 9 , 1, "   |___ [__  |    |    ");
            mvwprintw(casella, 10, 1, "   |___ ___] |___ |    ");
            mvwprintw(casella, 11, 1, "                       ");
        }else{
            mvwprintw(casella, 8 , 26, "  _  _ ____ _  _ _  _ . ");
            mvwprintw(casella, 9 , 26, "  |][| |___ | /| |  |'  ");
            mvwprintw(casella, 10, 26, "  |  | |___ |/ | |__|   ");
            mvwprintw(casella, 11, 26, "                        ");
        }
        wattroff(casella,A_STANDOUT);
    }
    
    /* Pulisco tutto e vado a vedere cosa ha premuto */
    delwin(casella);
    endwin();
    clear();
    refresh();
    menuUscita(i);
}

void menuUscita(int i)
{
    switch(i){
        case 0:
                /* esci */
            esci();
            break;
        case 1:
                /* torna al menu */
            menuPrincipale();
            break;
    }
}

/* MENU CREAZIONE CAMPO PERSONALIZZATO */
void menuCreazione()
{
    int ch;
    
    int righe = 0;
    int colonne = 0;
    int bombe = 0;
    int annullamenti = 0;
    
    int i = 0;
    int flag = 1;
    
    campo* mat;
    
    WINDOW *crea, *titolo;
    
    /* creo una nuova finestra */
    
    titolo = newwin( 8, 64, 5, COLS/2 - 64/2);
    
    init_pair(11, COLOR_BLACK, COLOR_YELLOW); /* colori */
    
    /* stampa titolo */
    mvwprintw( titolo, 1, 1, "    ______                   ______                           "); 
    mvwprintw( titolo, 2, 1, "   / ____/_______  ______   / ____/_________ ____ _____ ______"); 
    mvwprintw( titolo, 3, 1, "  / /   / ___/ _ // __  /  / /   / __  / __ `__  / __  / __  /"); 
    mvwprintw( titolo, 4, 1, " / /___/ /  /  __/ /_/ /  / /___/ /_/ / / / / / / /_/ / /_/ / "); 
    mvwprintw( titolo, 5, 1, "/_____/_/  /___//___,_/  /_____/___,_/_/ /_/ /_/ ____/_____/  "); 
    mvwprintw( titolo, 6, 1, "                                              /_/             "); 
    
    box(titolo, 0,0);
    
    wbkgd(titolo, COLOR_PAIR(11));
    
    wrefresh(titolo);
    
    crea = newwin(22, 82, LINES/2 - 22/2, COLS/2 - 82/2); 
    
    /* Coloro lo sfondo della finestra */
    
    init_pair(5, COLOR_BLACK, COLOR_GREEN);
    wbkgd(crea, COLOR_PAIR(5));

    /* Metto bordo alla finestra */
    
    box(crea, 0, 0); 
    
    
    /* stampo tutto */
    mvwprintw(crea, 1, 1, "____ _ ____ _  _ ____  ");
    mvwprintw(crea, 2, 1, "|__/ | | __ |__| |___ .");
    mvwprintw(crea, 3, 1, "|  ) | |__] |  | |___ .");
    mvwprintw(crea, 4, 1, "      (da 9 a 25)      ");
    
    mvwprintw(crea, 5, 1, "____ ____ _    ____ _  _ _  _ ____  ");
    mvwprintw(crea, 6, 1, "|    |  | |    |  | | /| | /| |___ .");
    mvwprintw(crea, 7, 1, "|___ |__| |___ |__| |/ | |/ | |___ .");
    mvwprintw(crea, 8, 1, "           (da 9 a 25)              ");
    
    mvwprintw(crea, 9 , 1, "___  ____ _  _ ___  ____  ");
    mvwprintw(crea, 10, 1, "|__] |  | |][| |__] |___ .");
    mvwprintw(crea, 11, 1, "|__] |__| |  | |__] |___ .");
    mvwprintw(crea, 12, 1, "                          ");
    
    mvwprintw(crea, 13, 1, "____ _  _ _  _ _  _ _    _    ____ _  _ ____ _  _ ___ _  ");
    mvwprintw(crea, 14, 1, "|__| | /| | /| |  | |    |    |__| |][| |___ | /|  |  | .");
    mvwprintw(crea, 15, 1, "|  | |/ | |/ | |__| |___ |___ |  | |  | |___ |/ |  |  | .");
    mvwprintw(crea, 16, 1, "                       (da 0 a 10)                       ");
    
        
    mvwprintw(crea, 17, 1, "____ ____ _  _ ____ ____ ____ ");
    mvwprintw(crea, 18, 1, "| __ |___ | /| |___ |__/ |__| ");
    mvwprintw(crea, 19, 1, "|__] |___ |/ | |___ |  ) |  | ");
    mvwprintw(crea, 20, 1, "                              ");
    
    mvwprintw(crea, 17, 80-23, "   ____ ____ ____ _    ");
    mvwprintw(crea, 18, 80-23, "   |___ [__  |    |    ");
    mvwprintw(crea, 19, 80-23, "   |___ ___] |___ |    ");
    mvwprintw(crea, 20, 80-23, "                       ");
    
    /* Abilito cursore */
    curs_set(1);
    
    righe = 0;
    colonne = 0;
    bombe = 0;
    annullamenti = 0;
    
    echo();
    
    /* Chiedo tutti i vari dati */
    do{
        mvwprintw(crea, 2, 65, "                ");
        mvwscanw(crea, 2, 65, "%d", &righe);
    }while(righe < 9 || righe > 25);
    
    do{
        mvwprintw(crea, 6, 65, "                ");
        mvwscanw(crea, 6, 65, "%d", &colonne);
    }while(colonne < 9 || colonne > 25);
    
    mvwprintw(crea, 12, 1, "       (da 1 a %d)       ", righe*colonne-1);
    
    do{
        mvwprintw(crea, 10, 65, "                ");
        mvwscanw(crea, 10, 65, "%d", &bombe);
    }while(bombe > (righe*colonne - 1) || bombe < 1);
    
    do{
        mvwprintw(crea, 14, 65, "                ");
        mvwscanw(crea, 14, 65, "%d", &annullamenti);
    }while(annullamenti < 0 || annullamenti > 10);
    
    /* Creo la matrice con bombe a caso */
    mat = creaMatriceACaso(righe, colonne, bombe, annullamenti);
    
    /* Stampo pulsanti con selezione */
    wattron(crea, A_STANDOUT);
    mvwprintw(crea, 17, 1, "____ ____ _  _ ____ ____ ____ ");
    mvwprintw(crea, 18, 1, "| __ |___ | /| |___ |__/ |__| ");
    mvwprintw(crea, 19, 1, "|__] |___ |/ | |___ |  ) |  | ");
    mvwprintw(crea, 20, 1, "                              ");
    
    wattroff(crea, A_STANDOUT);
    mvwprintw(crea, 17, 80-23, "   ____ ____ ____ _    ");
    mvwprintw(crea, 18, 80-23, "   |___ [__  |    |    ");
    mvwprintw(crea, 19, 80-23, "   |___ ___] |___ |    ");
    mvwprintw(crea, 20, 80-23, "                       ");
    
    /* Refresho il terminale */
 
    wrefresh(crea);
    
    /* Disabilito stampa caratteri */
    
    noecho();
    /* Abilito i tasti */
    keypad(crea, TRUE);
    
    /* Disabilito cursore */
    curs_set(0); 
    
    i = 0;
    flag = 1;
    while(flag && (ch = wgetch(crea))){ 
        beep(); /* Beep per far capire che mi son mosso */
        /* Ristampo per togliere selzione */
        if(i == 0){
            mvwprintw(crea, 17, 1, "____ ____ _  _ ____ ____ ____ ");
            mvwprintw(crea, 18, 1, "| __ |___ | /| |___ |__/ |__| ");
            mvwprintw(crea, 19, 1, "|__] |___ |/ | |___ |  ) |  | ");
            mvwprintw(crea, 20, 1, "                              ");
        }else{
            mvwprintw(crea, 17, 80-23, "   ____ ____ ____ _    ");
            mvwprintw(crea, 18, 80-23, "   |___ [__  |    |    ");
            mvwprintw(crea, 19, 80-23, "   |___ ___] |___ |    ");
            mvwprintw(crea, 20, 80-23, "                       ");
        }
        /* Cosa ho premuto? */
        switch( ch ) {
            case KEY_LEFT:
                /* sinistra */
                i = (i == 0) ? 1 : 0;
                break;
            case KEY_RIGHT:
                /* destra */
                i = (i == 0) ? 1 : 0;
                break;
            case 10:
                /* invio */
                flag = 0;
                break;
        }
        
        /* ristampo con selezione */
        wattron(crea, A_STANDOUT);
        if(i == 0){
            mvwprintw(crea, 17, 1, "____ ____ _  _ ____ ____ ____ ");
            mvwprintw(crea, 18, 1, "| __ |___ | /| |___ |__/ |__| ");
            mvwprintw(crea, 19, 1, "|__] |___ |/ | |___ |  ) |  | ");
            mvwprintw(crea, 20, 1, "                              ");
        }else{
            mvwprintw(crea, 17, 80-23, "   ____ ____ ____ _    ");
            mvwprintw(crea, 18, 80-23, "   |___ [__  |    |    ");
            mvwprintw(crea, 19, 80-23, "   |___ ___] |___ |    ");
            mvwprintw(crea, 20, 80-23, "                       ");
        }
        wattroff(crea,A_STANDOUT);
    }
    
    
    /* cancello e vado a vedere cosa ha premuto */
    delwin(crea);
    delwin(titolo);
    endwin();
    clear();
    refresh();
    
    SelectMenuCreazione(i, mat);
}

void SelectMenuCreazione(int i, campo* matrice)
{
    switch(i){
        case 0:
            /* Ha premuto GENERA, quindi salvo su file e vado a giocare */
            salvaSuFile(matrice);
            menuGioco(matrice);
            break;
        case 1:
            /* Ha premuto su torna indietro */
            menuPrincipale();
            break;
    }
}

/* ALTRO */

void esci() /* Esce dal gioco */
{
    endwin();
    exit(0);
}

int main() /* Main */
{
    menuPrincipale(); /* Invoco il menu principale */
    
    return 0;
}