#include <stdio.h>
#include "tetris_components.h"

/**
 * effettua la richiesta dell'input 'rotazione' e ne verifica la correttezza
 * @return la rotazione del tetramino
 */
int controllo_rot(){
    /*-1 valore non valido*/
    int rot=0;
    printf("Inserire la rotazione del blocco --> ");
    scanf("%d", &rot);
    if(rot==0)
        rot=0;
    else if(rot==90)
        rot=1;
    else if(rot==180)
        rot=2;
    else if(rot==270)
        rot=3;
    else
        rot=-1;

    if(rot==-1)
        printf("La rotazione selezionata non esiste! (0, 90, 180, 270)\n");
    return rot;
}

/**
 * effettua la richiesta dell'input 'posizione' e ne verifica la correttezza
 * @param b il blocco selezionato di cui si vuole richiedere la posizione
 * @return la posizione del tetramino
 */
int controllo_pos(struct Blocco b){
    /*-1 valore non valido*/
    int pos=0;
    int start_b=-5,finish_b=4, count, i, j;
    printf("Inserire la posizione in cui posizionare il blocco --> ");
    scanf("%d", &pos);

    for(i=0;i<4;i++){
        count=0;
        for(j=0;j<4;j++){
            if(b.forma[j][i]!=0 && start_b==-5)
                start_b=i;
            if(b.forma[j][i]!=0)
                count=1;
        }
        if(count==0)
            finish_b--;
    }
    if(pos>=0 && pos<N_COLONNE-finish_b+1){
        pos=pos-start_b;
    }else{
        pos=-5;
    }

    if(pos==-5)
        printf("La posizionata non è valida!\n");
    return pos;
}

/**
 * effettua la richiesta dell'input 'numero del tetramino' e ne verifica la correttezza
 * @param v il vettore contenente il numero di tetramino rimanenti
 * @return il numero del tetramino
 */
int controllo_nbloc(struct Blocco *v){
    /*-1 valore non valido*/
    int nbloc=0;
    printf("Inserire il blocco desiderato --> ");
    scanf("%d", &nbloc);
    if(nbloc>=0 && nbloc<N_BLOCCHI){
        if(v[nbloc].num_blocchi<=0)
            nbloc=-1;
    }else{
        nbloc=-1;
    }

    if(nbloc==-1)
        printf("Il blocco selezionato non esiste!\n");
    return nbloc;
}

/**
 * effettua la richiesta e la verifica di tutti i parametri per l'inserimento di un tetramino
 * @param rot la rotazione
 * @param pos la posizione
 * @param nbloc il numero del tetramino
 * @param v il vettore contenente la descrizione di ciascun tetramino
 */
void controllo_input(int *rot, int *pos, int *nbloc, struct Blocco *v){
    do{
        *nbloc=controllo_nbloc(v);
    }while(*nbloc==-1);
    do{
        *rot=controllo_rot();
    }while(*rot==-1);
    do{
        flip_blocco(&v[*nbloc], *rot);
        *pos=controllo_pos(v[*nbloc]);
    }while(*pos==-5);
}
