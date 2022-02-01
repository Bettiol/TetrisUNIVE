#include "tetris_components.h"
#include <stdio.h>
#include "tetris_operations.h"

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

int caduta_blocco(struct Piano_Gioco *m, struct Blocco b, int piano){
    int corretto=verifica_posizione_blocco(m, b, piano);
    if(corretto==1){
        return caduta_blocco(m,b,piano+1);
    }
    else{
        return inserisci_bloccco_posizione(m,b,piano-1);
    }
}

int inserisci_blocco(struct Piano_Gioco *m, struct Blocco b){
    int perso;
    perso=caduta_blocco(m,b,0);
    if(perso==1){
        printf("Sei uscito dal campo di gioco, hai PERSO!\n\n");
    }
    score_control(m);
    return perso;
}

int inserisci_blocco_multi(struct Piano_Gioco *m1, struct Piano_Gioco *m2, struct Blocco b){
    int perso;
    int score;
    perso=caduta_blocco(m1,b,0);
    score= score_control(m1);
    penalita(m2, score);
    return perso;
}

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

void penalita(struct Piano_Gioco *m, int score){
    int i, j;
    if(score==6){
        for(i=N_RIGHE-3; i<N_RIGHE;i++){
            for(j=0;j<N_COLONNE;j++){
                if(m->matrice[i][j]!=0)
                    m->matrice[i][j] = 0;
                else
                    m->matrice[i][j] = 8;
            }
        }
    }else if(score==12){
        for(i=N_RIGHE-4; i<N_RIGHE;i++){
            for(j=0;j<N_COLONNE;j++){
                if(m->matrice[i][j]!=0)
                    m->matrice[i][j] = 0;
                else
                    m->matrice[i][j] = 8;
            }
        }
    }
}

int fine_blocchi(struct Blocco *v){
    int i;
    int fine=1;
    for(i=0;i<N_BLOCCHI && fine==1;i++){
        if(v[i].num_blocchi!=0)
            fine=0;
    }
    if(fine==1){
        printf("Hai finito i Blocchi!\n\n");
    }
    return fine;
}

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

int inserisci_blocco_score(struct Piano_Gioco *m, struct Blocco b){
    int perso;
    perso=caduta_blocco(m,b,0);
    if(perso==1)
        return -1;
    else
        return score_control(m);
}
