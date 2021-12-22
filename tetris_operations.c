#include "tetris_components.h"
#include <stdio.h>
#include "tetris_operations.h"

/**
 * verifica la correttezza del tetramino nel piano selezionato
 * @param m piano di gioco
 * @param b tetramino
 * @param piano livello del piano di gioco
 * @return 1 se è corretto 0 altrimenti
 */
int verifica_posizione_blocco(struct Piano_Gioco *m, struct Blocco b, int piano){
    int corretto=1;
    int i,j;
    for(i=3;i>=0 && corretto==1;i--){
        for(j=0;j<4 && corretto==1;j++){
            if(piano-(3-i)>=0 && b.pos_x+j<N_COLONNE &&  b.pos_x+j>=0)
                if(m->matrice[piano-(3-i)][b.pos_x+j]!=0 && b.forma[i][j]!=0)
                    corretto=0;
        }
    }
    return corretto;
}

/**
 * verifica la correttezza del tetramino nel piano selezionato, se è corretto prova a inserire il tetramino nel piano sucessivo, altrimenti lo inserisce sul piano precedente
 * @param m piano di gioco
 * @param b tetramino
 * @param piano livello del piano da inserire
 * @return 1 se il giocatore ha perso 0 altrimenti
 */
int caduta_blocco(struct Piano_Gioco *m, struct Blocco b, int piano){
    int corretto=verifica_posizione_blocco(m, b, piano);
    if(corretto==1){
        return caduta_blocco(m,b,piano+1);
    }
    else{
        return inserisci_bloccco_posizione(m,b,piano-1);
    }
}

/**
 * inserisce un tetramino nel piano di gioco nella modalità single_player
 * @param m piano di gioco
 * @param b tetramino da inserire
 * @return 1 se il giocatore ha perso 0 altrimenti
 */
int inserisci_blocco(struct Piano_Gioco *m, struct Blocco b){
    int perso;
    perso=caduta_blocco(m,b,0);
    if(perso==1){
        printf("HAI PERSO!\n\n");
    }
    score_control(m);
    return perso;
}

/**
 * inserisce un tetramino nel piano di gioco nella modalità multi_player
 * @param m1 piano di gioco
 * @param m2 piano di gioco avversario
 * @param b tetramino da inserire
 * @return 1 se il giocatore ha perso 0 altrimenti
 */
int inserisci_blocco_multi(struct Piano_Gioco *m1, struct Piano_Gioco *m2, struct Blocco b){
    int perso;
    int score;
    perso=caduta_blocco(m1,b,0);
    if(perso==1){
        printf("HAI PERSO! \n\n");
    }
    score= score_control(m1);
    penalita(m2, score);
    return perso;
}

/**
 * elimina una riga dal piano di gioco
 * @param m piano di gioco
 * @param riga riga da eliminare
 */
void elimina_riga(struct Piano_Gioco *m, int riga){
    int j, i;
    for(i=riga;i>0;i--){
        for(j=0;j<N_COLONNE;j++){
            m->matrice[i][j]=m->matrice[i-1][j];
        }
    }
    for(j=0;j<N_COLONNE;j++){
        m->matrice[0][j]=0;
    }
}

/**
 * verifica e conta il punteggio il punteggio ottenuto ed elimina le eventuali rige completate
 * @param m piano di gioco
 * @return il punteggio ottenuto
 */
int score_control(struct Piano_Gioco *m){
    int score=0;
    int i, j;
    int flag;
    for(i=0;i<N_RIGHE;i++){
        flag=0;
        for(j=0;j<N_COLONNE && flag==0;j++){
            if(m->matrice[i][j]==0){
                flag=1;
            }
        }
        if(flag==0){
            score++;
            elimina_riga(m,i);
        }
    }
    if(score==1){
        m->score=m->score+1;
        return 1;
    }else if(score==2){
        m->score=m->score+3;
        return 3;
    }else if(score==3){
        m->score=m->score+6;
        return 6;
    }else if(score==4){
        m->score=m->score+12;
        return 12;
    }

    return score;
}

/**
 * inverte le ultime due rige del piano di gioco se lo score è maggiore o uguale a 6
 * @param m piano di gioco avversario
 * @param score punteggio effettuato
 */
void penalita(struct Piano_Gioco *m, int score){
    int i;
    int app;
    if(score>=6){
        for(i=0;i<N_COLONNE;i++){
            app=m->matrice[N_RIGHE-1][i];
            m->matrice[N_RIGHE-1][i]=m->matrice[N_RIGHE-2][i];
            m->matrice[N_RIGHE-2][i]=app;
        }
    }
}

/**
 * verifica se sono finiti tutti i blocchi disponibili
 * @param v il vettore contenente la descrizione di ciascun tetramino
 * @return 1 se sono finiti i tetramini 0 altrimenti
 */
int fine_blocchi(struct Blocco *v){
    int i;
    int fine=1;
    for(i=0;i<N_BLOCCHI && fine==1;i++){
        if(v[i].num_blocchi!=0)
            fine=0;
    }
    if(fine==1){
        printf("HAI FINITO I BLOCCHI\n\n");
    }
    return fine;
}

/**
 * inserisce un tetramino nel piano di gioco in un livello
 * @param m piano di gioco
 * @param b tetramino
 * @param piano il livello del piano di gioco
 * @return 1 se il giocatore ha perso 0 altrimenti
 */
int inserisci_bloccco_posizione(struct Piano_Gioco *m, struct Blocco b, int piano){
    int i, j;
    int perso=0;
    for(i=3;i>=0 && perso==0;i--) {
        for (j = 0; j < 4 && perso==0; j++) {
            if(piano-(3-i)>=0 && b.pos_x+j<N_COLONNE &&  b.pos_x+j>=0) {
                /*sostituisco i blocchi vuoti del piano di gioco con i nuovi valori del blocco*/
                if (piano - i % 3 >= 0 && m->matrice[piano - (3 - i)][b.pos_x + j] == 0)
                    m->matrice[piano - (3 - i)][b.pos_x + j] = b.forma[i][j];
            }else if(piano-(3-i)<0 && b.forma[i][j]!=0)
                perso=1;
        }
    }
    return perso;
}

/**
 * inserisce un tetramino in un piano di gioco e ne restituisce il punteggio ottenuto
 * @param m piano di gioco
 * @param b tetramino
 * @return -1 se ha perso altrimenti il punteggio effettuato
 */
int inserisci_blocco_score(struct Piano_Gioco *m, struct Blocco b){
    int perso;
    perso=caduta_blocco(m,b,0);
    if(perso==1)
        return -1;
    else
        return score_control(m);
}