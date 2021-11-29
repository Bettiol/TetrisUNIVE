#include <stdio.h>
#include "tetris_components.h"
#include "tetris_print.h"
#include "input_control.h"
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
int GetColumnWidth() {

    CONSOLE_SCREEN_BUFFER_INFO info;
    HANDLE out;

    if (!(out = GetStdHandle(STD_OUTPUT_HANDLE)) ||
        !GetConsoleScreenBufferInfo(out, &info))
        return 80;
    return info.dwSize.X;

}
#else
int GetColumnWidth() {
    return 200;
}
#endif

/*
 * TO DO
 *  - Menù per la scelta della modalità
 *  - Grafica e messaggi di interazione
 *  - Algoritmo per la CPU
 * */


int inserisci_blocco(struct Piano_Gioco *m, struct Blocco b);
int caduta_blocco(struct Piano_Gioco *m, struct Blocco b, int piano);
int verifica_posizione_blocco(struct Piano_Gioco *m, struct Blocco b, int piano);
int inserisci_bloccco_posizione(struct Piano_Gioco *m, struct Blocco b, int piano);
void elimina_riga(struct Piano_Gioco *m, int riga);
int score_control(struct Piano_Gioco *m);
void penalita(struct Piano_Gioco *m, int score);
int fine_blocchi(struct Blocco *v);

void single_player();
void multi_player();
void player_cpu();


void istruzioni();
void cleaner();
void grafica();
void centeredPrintf(char *s);
int menu();

int main() {
    //single_player();
    //multi_player();

    int scelta = menu();
    printf("Scelta effetuata  %d", scelta);

    return 0;
}

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
        printf("hai perso coglione AHAHAHAHAHAH \n\n");
    }
    score_control(m);
    return perso;
}

int inserisci_blocco_multi(struct Piano_Gioco *m1, struct Piano_Gioco *m2, struct Blocco b){
    int perso;
    int score;
    perso=caduta_blocco(m1,b,0);
    if(perso==1){
        printf("hai perso coglione AHAHAHAHAHAH \n\n");
    }
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
    }else if(score==2){
        m->score=m->score+3;
    }else if(score==3){
        m->score=m->score+6;
    }else if(score==4){
        m->score=m->score+12;
    }

    return score;
}

void penalita(struct Piano_Gioco *m, int score){
    int i;
    int app;
    if(score>=3){
        for(i=0;i<N_COLONNE;i++){
            app=m->matrice[N_RIGHE-1][i];
            m->matrice[N_RIGHE-1][i]=m->matrice[N_RIGHE-2][i];
            m->matrice[N_RIGHE-2][i]=app;
        }
    }
}

void single_player(){
    struct Blocco blocchi[N_BLOCCHI];
    struct Piano_Gioco player1;
    int n_blocco, pos_x, rot, perso=0, fine=0;

    inizializza_matrice(&player1);
    inizializza_blocchi(&blocchi[0]);

    while (perso==0 && fine==0) {
        stampa_blocchi(blocchi);
        stampa_matrice(player1);

        controllo_input(&rot,&pos_x,&n_blocco, &blocchi[0]);

        blocchi[n_blocco].pos_x = pos_x;
        flip_blocco(&blocchi[n_blocco], rot);
        blocchi[n_blocco].num_blocchi--;

        perso=inserisci_blocco(&player1, blocchi[n_blocco]);
        fine= fine_blocchi(&blocchi[0]);
    }
}

void multi_player() {
    struct Blocco blocchi[N_BLOCCHI];
    struct Piano_Gioco player1;
    struct Piano_Gioco player2;
    int n_blocco, pos_x, rot, perso = 0, p = 0;

    inizializza_matrice(&player1);
    inizializza_matrice(&player2);
    inizializza_blocchi(&blocchi[0]);

    while (perso == 0) {
        stampa_blocchi(blocchi);
        if (p == 0) {
            printf("p1\n");
            stampa_matrici(player1, player2);
            controllo_input(&rot,&pos_x,&n_blocco, &blocchi[0]);
        } else {
            printf("p2\n");
            stampa_matrici(player1, player2);
            controllo_input(&rot,&pos_x,&n_blocco, &blocchi[0]);
        }

        blocchi[n_blocco].pos_x = pos_x;
        blocchi[n_blocco].num_blocchi--;
        flip_blocco(&blocchi[n_blocco], rot);
        if (p == 0)
            perso = inserisci_blocco_multi(&player1, &player2, blocchi[n_blocco]);
        else
            perso = inserisci_blocco_multi(&player2, &player1, blocchi[n_blocco]);
        p = (p + 1) % 2;
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
        printf("hai finito i blocchi AHAHAHAHAHAH\n\n");
    }
    return fine;
}

void cleaner() {
    system("CLEAR");
}

void grafica() {

    printf("Player 1");
    printf("\t\t\t\t\t\t\t\t\t");
    printf("Player 2\n");

    printf("Punti P1: ");
    printf("\t\t\t\t\t\t\t\t\t");
    printf("Punti P2: \n");

    int t;
    scanf("%d", &t);
    printf("%d", t);
    cleaner();

}

int menu() {

    char titolo[] = "TermTris";
    char modalita1[] = "1) Single Player";
    char modalita2[] = "2) Multiplayer Player";
    char help[] = "9) Help";
    int scelta = 0;


    centeredPrintf(titolo);

    printf("\n");
    printf("\n");
    printf("\n");

    centeredPrintf(modalita1);
    centeredPrintf(modalita2);
    printf("\n");
    centeredPrintf(help);

    do {

        printf("Inserire il numero corrispondente all'opzione desisderata --> ");
        scanf("%d", scelta);

    } while (scelta != 1 || scelta != 2 || scelta != 9);

    return scelta;

}

void istruzioni() {

    printf("\t\t\t\t\t\t");

}

void centeredPrintf(char *s) {

    int total_width = GetColumnWidth();
    int s_width = strlen(s);
    int field_width = (total_width - s_width) / 2 + s_width;

    printf("%*s\n", field_width, s);

}