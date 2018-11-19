#include <stdlib.h>
#include <stdio.h>
#include "CampoMinato.h"
#include <time.h>

cella** crea_campo(int righe, int colonne) /* Genero il campo dinamicamente */
{
    int i;
    cella** campo = (cella**)malloc(sizeof(cella*) * righe);
    for(i = 0; i < righe; i++)
    {
        campo[i] = (cella*)malloc(sizeof(cella) * colonne);
    }

    
    return campo;
}

void svuotaMatrice(campo* matrice) /* Faccio il free del campo alla fine del gioco */
{
    int q;
    for(q = 0; q < matrice->righe; q++)
    {
        free((matrice->mycampo)[q]);
    }
    
    free(matrice->mycampo);
    free(matrice);
}

campo* creaMatriceACaso(int righe, int colonne, int bombe, int annullamenti) /* creo una matrice e metto un numero n bombe in posizione casuale */
{
    int w, q, j;
    campo* mat = (campo*)malloc(sizeof(campo)); /* Creo campo */
    
    /* Carico le info della struct */
    mat->righe = righe;
    mat->colonne = colonne;
    mat->bombeTotali = bombe;
    mat->quantoAnnullare = 1;
    mat->quanteBandiereMesse = 0;
    mat->quantiAnnullamentiMassimi = annullamenti;
    mat->pilaMosse = 0;

    mat->mycampo = crea_campo(mat->righe, mat->colonne); /* Creo la matrice */
    
    /* Inizializzo ogni singola cella */
    for(w = 0; w < mat->righe; w++)
    {
        for(q = 0; q < mat->colonne; q++)
        {
            (((mat->mycampo)[w])[q]).r = w;
            (((mat->mycampo)[w])[q]).c = q;
            (((mat->mycampo)[w])[q]).bomba = 0;
            (((mat->mycampo)[w])[q]).visitato = 0;
            (((mat->mycampo)[w])[q]).bandiera = 0;
            (((mat->mycampo)[w])[q]).bombeVicine = 0;
        }
    }

    srand(time(NULL)); /* per il random delle bombe */

    /* Genero le n bombe a caso */
    j = 0;
    for(j = 0; j < bombe; j++)
    {
        int r, c;
        do{
            r = rand()%(mat->righe);
            c = rand()%(mat->colonne);
        }while(((mat->mycampo)[r][c]).bomba == 1);

        ((mat->mycampo)[r][c]).bomba = 1;
    }
     
    /* Carico il numero di bombe di ogni singola posizione */
    caricaNumeroBombe(mat);
    
    return mat;
}

void caricaNumeroBombe(campo* matrice) /* funzione che per ogni singola posizione della matrice conta quante bombe ha vicino */
{
    int i = 0, j = 0;
    for(i = 0; i < matrice->righe; i++)
    {
        for(j = 0; j < matrice->colonne; j++)
        {            
            if(i > 0 && j > 0) /* diagonale nord-ovest */
            {
                if(((matrice->mycampo)[i-1][j-1]).bomba == 1)
                    ((matrice->mycampo)[i][j]).bombeVicine++;
            }
            
            if(i > 0 && j < matrice->colonne-1) /* diagonale nord-est */
            {
                if(((matrice->mycampo)[i-1][j+1]).bomba == 1)
                    ((matrice->mycampo)[i][j]).bombeVicine++;
            }
            
            if(i < matrice->righe - 1 && j > 0) /* diagonale sud-ovest */
            {
                if(((matrice->mycampo)[i+1][j-1]).bomba == 1)
                    ((matrice->mycampo)[i][j]).bombeVicine++;
            }
            
            if(i < matrice->righe - 1 && j < matrice -> righe - 1) /* diagonale sud-est */
            {
                if(((matrice->mycampo)[i+1][j+1]).bomba == 1)
                    ((matrice->mycampo)[i][j]).bombeVicine++;
            }
            
            if(i > 0) /*nord */
            {
                if(((matrice->mycampo)[i-1][j]).bomba == 1)
                    ((matrice->mycampo)[i][j]).bombeVicine++;
            }
            
            if(i < matrice->righe-1) /* sud  */
            {
                if(((matrice->mycampo)[i+1][j]).bomba == 1)
                    ((matrice->mycampo)[i][j]).bombeVicine++;
            }
            
            if(j > 0) /* ovest */
            {
                if(((matrice->mycampo)[i][j-1]).bomba == 1)
                    ((matrice->mycampo)[i][j]).bombeVicine++;
            }
            
            if(j < matrice->colonne - 1) /* est */
            {
                if(((matrice->mycampo)[i][j+1]).bomba == 1)
                    ((matrice->mycampo)[i][j]).bombeVicine++;
            }
        }
    }
}

void scopriCampo(campo *matrice, int i, int j) /* Funzione ricorsiva che scopre il campo nel caso sono in una posizione senza bombe e senza bombe vicine */
{
    ((matrice->mycampo)[i][j]).visitato = 1;
    
    if(((matrice->mycampo)[i][j]).bombeVicine == 0)
    {        
        if(i > 0 && j > 0) /* diagonale nord-ovest */
        {
            if(((matrice->mycampo)[i-1][j-1]).visitato == 0 && ((matrice->mycampo)[i-1][j-1]).bandiera == 0)
                scopriCampo(matrice, i-1, j-1);
        }

        if(i > 0 && j < matrice->colonne-1) /* diagonale nord-est */
        {
            if(((matrice->mycampo)[i-1][j+1]).visitato == 0 && ((matrice->mycampo)[i-1][j+1]).bandiera == 0)
                scopriCampo(matrice, i-1, j+1);
        }

        if(i < matrice->righe - 1 && j > 0) /* diagonale sud-ovest */
        {
            if(((matrice->mycampo)[i+1][j-1]).visitato == 0 &&((matrice->mycampo)[i+1][j-1]).bandiera == 0)
                scopriCampo(matrice, i+1, j-1);
                
        }

        if(i < matrice->righe - 1 && j < matrice -> righe - 1) /* diagonale sud-est */
        {
            if(((matrice->mycampo)[i+1][j+1]).visitato == 0 && ((matrice->mycampo)[i+1][j+1]).bandiera == 0)
                scopriCampo(matrice, i+1, j+1);
                
        }

        if(i > 0) /*nord */
        {
            if(((matrice->mycampo)[i-1][j]).visitato == 0 && ((matrice->mycampo)[i-1][j]).bandiera == 0)
                scopriCampo(matrice, i-1, j);
                
        }

        if(i < matrice->righe-1) /* sud */
        {
            if(((matrice->mycampo)[i+1][j]).visitato == 0 && ((matrice->mycampo)[i+1][j]).bandiera == 0)
                scopriCampo(matrice, i+1, j);
                
        }

        if(j > 0) /* ovest */
        {
            if(((matrice->mycampo)[i][j-1]).visitato == 0 && ((matrice->mycampo)[i][j-1]).bandiera == 0)
                scopriCampo(matrice, i, j-1);
                
        }

        if(j < matrice->colonne - 1) /* est */
        {
            if(((matrice->mycampo)[i][j+1]).visitato == 0 && ((matrice->mycampo)[i][j+1]).bandiera == 0)
                scopriCampo(matrice, i, j+1); 
        }
    }
}

int checkVittoria(campo* matrice) /* Un check della vittoria, se ho scoperto tutte le celle tranne le bombe */
{
    int q, p;
    int count = 0;
    for(q = 0; q < matrice->righe; q++)
    {
        for(p = 0; p < matrice->colonne; p++)
        {
            if(((matrice->mycampo)[q][p]).visitato != 1 && ((matrice->mycampo)[q][p]).bomba == 0)
                count++;
        }
    }
    
    return (count > 0) ? 0 : 1;
}

int caricaFilePersonalizzato(campo *mat) /* funzione che carica il file personalizzato */
{
    FILE *f ;
    f = fopen("personalizzato.txt", "r"); /* apro il file */
    
    if(f == NULL)
    {
        return 0;
    }
    else {
        int temp1, temp2;
        int w, q;
        
        fscanf(f, "%d, %d", &(mat->righe), &(mat->colonne)); /* Legge la dimensione del campo */
        
        mat->bombeTotali = 0;
        mat->quantoAnnullare = 1;
        mat->quanteBandiereMesse = 0;
        mat->quantiAnnullamentiMassimi = 5;
        
        mat->quantiAnnullamentiMassimi = scegliQuantoAnnullare(); /* Funzione che carica la grafica per chiedere quante volte può annullare */
            
        mat->pilaMosse = NULL;
        mat->mycampo = crea_campo(mat->righe, mat->colonne);
        
        /* Inizializzo ogni singola cella */
        for(w = 0; w < mat->righe; w++)
        {
            for(q = 0; q < mat->colonne; q++)
            {
                (((mat->mycampo)[w])[q]).r = w;
                (((mat->mycampo)[w])[q]).c = q;
                (((mat->mycampo)[w])[q]).bomba = 0;
                (((mat->mycampo)[w])[q]).visitato = 0;
                (((mat->mycampo)[w])[q]).bandiera = 0;
                (((mat->mycampo)[w])[q]).bombeVicine = 0;
            }
        }

        /* Leggo le coppie di coordinate delle bombe */
        while(fscanf(f, "%d, %d", &temp1, &temp2) && !feof(f))
        {
            int x = temp1;
            int y = temp2;

            (((mat->mycampo)[x])[y]).bomba = 1;
            mat->bombeTotali++;
        }
        
        /* Carico il numero di bombe vicino a ogni cella */
        caricaNumeroBombe(mat);
        
        fclose(f);
        return 1;
    }
}

int salvaSuFile(campo* mat) /* Funzione che salva il campo generato nel file personalizzato.txt */
{
    FILE *f ;
    f = fopen("personalizzato.txt", "w"); /* apro il file */
    
    if(f == NULL)
    {
        return 0;
    }
    else {
        int w, q;
        
        /* Salvo la dimensione */
        fprintf(f, "%d, %d\n\n", mat->righe, mat->colonne);
          
        /* Salvo le bombe */
        for(w = 0; w < mat->righe; w++)
        {
            for(q = 0; q < mat->colonne; q++)
            {
                if((((mat->mycampo)[w])[q]).bomba == 1){
                    fprintf(f, "%d, %d\n", w, q);
                }
            }
        }
        
        fclose(f);
        return 1;
    }
}

void annullaMossa(campo* matrice) /* Funzione che annulla le mosse */
{
    int p, q;
    PilaS temp;
    int quantoAnnullare = matrice->quantoAnnullare;
    matrice->quantoAnnullare++;
    while(quantoAnnullare != 0 && !is_empty(matrice->pilaMosse)) /* While che toglie n mosse dalla pila (se ci sono) */
    {
        cella *elem = NULL;
        int ris = 0;
        do{
            ris = pop(&(matrice->pilaMosse), elem);
        }while(!ris);
        
        quantoAnnullare--;
    }
    
    /* Metto tutto coperto */
    for(q = 0; q < matrice->righe; q++)
    {
        for(p = 0; p < matrice->colonne; p++)
        {
            ((matrice->mycampo)[q][p]).visitato = 0;
        }
    }
    
    /* Scopro tutte le celle restate nella pila delle mosse, in questo modo nella pila ci sono solo le mose effettuate, quindi quelle da fare */
    temp = matrice->pilaMosse;
    
    while(temp)
    {
        scopriCampo(matrice, temp->elem->r, temp->elem->c);
        
        temp = temp->next;
    }
}