<<<<<<< HEAD
#include <stdio.h>

#define N_BLOCCHI  7

#define N_RIGHE  20
#define N_COLONNE  10

/*1*/
#define RED "\e[0;31m"
/*2*/
#define GRN "\e[0;32m"
/*3*/
#define YEL "\e[0;33m"
/*4*/
#define BLU "\e[0;34m"
/*5*/
#define MAG "\e[0;35m"
/*6*/
#define CYN "\e[0;36m"
/*7*/
#define WHT "\e[0;37m"

/*
 * TO DO
 * Bettiol:
 *  - Grafica
 *  - Contatore pezzi
 *  - Contatore punti
 *  - Interazione utente
 *  - 
 * */

struct Blocco{
    int forma[4][4];
    int rotazione;
    int pos_x;
    /*int num_blocchi*/
    int colore;
};

struct Piano_Gioco{
    int matrice[N_RIGHE+3][N_COLONNE];
    int score;
};

void stampa_blocco(struct Blocco b);
void stampa_blocchi(struct  Blocco *b);
void flip_blocco(struct Blocco *b, int rot);
void flip_blocco_0(struct Blocco *b);
void inizializza_matrice(struct Piano_Gioco *m);
void stampa_matrice(struct Piano_Gioco m);
void inizializza_blocchi(struct Blocco *blocchi);
void stampa_colore(int colore);

int inserisci_blocco(struct Piano_Gioco *m, struct Blocco b);
void caduta_blocco(struct Piano_Gioco *m, struct Blocco b, int piano);
int verifica_posizione_blocco(struct Piano_Gioco *m, struct Blocco b, int piano);
void inserisci_bloccco_posizione(struct Piano_Gioco *m, struct Blocco b, int piano);

int main() {
    struct Blocco blocchi[N_BLOCCHI];

    struct Piano_Gioco player1;
    inizializza_matrice(&player1);
    inizializza_blocchi(&blocchi);

    stampa_blocchi(blocchi);

    /*richiesta blocco, posizione e rotazione*/

    blocchi[0].pos_x=-1;
    flip_blocco(&blocchi[0],2);

    inserisci_blocco(&player1, blocchi[0]);
    stampa_matrice(player1);
    printf("\n\n");

    blocchi[1].pos_x=5;
    flip_blocco(&blocchi[1],0);

    inserisci_blocco(&player1, blocchi[1]);

    stampa_matrice(player1);

    printf("\n\n");

    blocchi[2].pos_x=5;
    flip_blocco(&blocchi[2],2);

    inserisci_blocco(&player1, blocchi[2]);

    stampa_matrice(player1);

    printf("\n\n");

    /*ripeti il tutto*/

    return 0;
}

void stampa_blocco(struct Blocco b){
    int i, j;
    for(i=0;i<4;i++){
        for (j = 0;  j<4 ; j++) {
            stampa_colore(b.forma[i][j]);
        }
        printf("\n");
    }
}

void stampa_blocchi(struct  Blocco *b){
    int i;
    for(i=0;i<N_BLOCCHI;i++){
        stampa_blocco(b[i]);
    }
}

void flip_blocco(struct Blocco *b, int rot) {
    int i, j, k;
    /*calcolo la rotazione da effettuare per arrivare a rot*/
    rot=(4-(b->rotazione-rot))%4;

    for (k = 0; k < rot; k++) {
        int mat_app[4][4]={0};
        /*copio la matrice*/
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                mat_app[j][3-i]=b->forma[i][j];
            }
        }
        /*giro la matrice del blocco utilizzando la matrice d'appoggio*/
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                b->forma[i][j]=mat_app[i][j];
            }
        }
    }
    b->rotazione=(b->rotazione+rot)%4;
}

void inizializza_matrice(struct Piano_Gioco *m){
    int i, j;
    for(i=0;i<N_RIGHE; i++){
        for (j = 0;  j<N_COLONNE ; j++) {
            m->matrice[i][j]=0;
        }
    }
    for(i=N_RIGHE;i<N_RIGHE+3; i++){
        for (j = 0;  j<N_COLONNE ; j++) {
            m->matrice[i][j]=1;
        }
    }
    m->score=0;
}

void stampa_matrice(struct Piano_Gioco m){
    int i, j;
    for(i=0;i<N_RIGHE;i++){
        for (j = 0;  j<N_COLONNE ; j++) {
           /* if(m.matrice[i][j]==0)
                printf(".");
            else
                printf("#");*/
            stampa_colore(m.matrice[i][j]);
        }
        printf("\n");
    }
}

void stampa_colore(int colore){
    if(colore==1)
        printf(RED"#"WHT);
    else if(colore==2)
        printf(GRN"#"WHT);
    else if(colore==3)
        printf(YEL"#"WHT);
    else if(colore==4)
        printf(BLU"#"WHT);
    else if(colore==5)
        printf(MAG"#"WHT);
    else if(colore==6)
        printf(CYN"#"WHT);
    else if(colore==7)
        printf(WHT"#"WHT);
    else
        printf(".");
}

void inizializza_blocchi(struct Blocco *blocchi){
    struct Blocco linea={
            {1,1,1,1,0,0,0,0,0,0,0,0},
            0,
            0,
    };
    struct Blocco quadrato={
            {2,2,0,0,2,2,0,0,0,0,0,0},
            0,
            0,
    };
    struct Blocco l_sinistra={
            {3,0,0,0,3,3,3,0,0,0,0,0},
            0,
            0,
    };
    struct Blocco l_destra={
            {0,0,4,0,4,4,4,0,0,0,0,0},
            0,
            0,
    };
    struct Blocco s_sinistra={
            {0,5,5,0,5,5,0,0,0,0,0,0},
            0,
            0,
    };
    struct Blocco s_destra={
            {6,6,0,0,0,6,6,0,0,0,0,0},
            0,
            0,
    };
    struct Blocco t_rov={
            {0,7,0,0,7,7,7,0,0,0,0,0},
            0,
            0,
    };

    blocchi[0]=linea;
    blocchi[1]=quadrato;
    blocchi[2]=l_sinistra;
    blocchi[3]=l_destra;
    blocchi[4]=s_sinistra;
    blocchi[5]=s_destra;
    blocchi[6]=t_rov;
}

void inserisci_bloccco_posizione(struct Piano_Gioco *m, struct Blocco b, int piano){
    int i, j;
    for(i=3;i>=0;i--) {
        for (j = 0; j < 4; j++) {
            if(piano-(3-i)>=0 && b.pos_x+j<N_COLONNE &&  b.pos_x+j>=0) {
                /*sostituisco i blocchi vuoti del piano di gioco con i nuovi valori del blocco*/
                if (piano - i % 3 >= 0 && m->matrice[piano - (3 - i)][b.pos_x + j] == 0)
                    m->matrice[piano - (3 - i)][b.pos_x + j] = b.forma[i][j];
            }
        }
    }
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

void caduta_blocco(struct Piano_Gioco *m, struct Blocco b, int piano){
    int corretto=verifica_posizione_blocco(m, b, piano);
    if(corretto==1){
        caduta_blocco(m,b,piano+1);
    }
    else{
        inserisci_bloccco_posizione(m,b,piano-1);
    }
}

int inserisci_blocco(struct Piano_Gioco *m, struct Blocco b){
    int perso=0;
    caduta_blocco(m,b,0);
    /*controllo se ho perso o se score aumenta*/
    return perso;
}
=======
#include "main.h"
#include "tetris_components.h"
#include "tetris_print.h"
#include "input_control.h"
#include "tetris_operations.h"
#include "NPC_tetris.h"

/**
 * @file main.c
 * @authors Bettiol Luca, Brognera Enrico
 * @mainpage X-TETRIS
 * @section Introduzione
 *
 * Progetto universitario di Introduzione alla Programmazione, che consiste nella rielaborazione in ANSI-C del famoso gioco arcade Tetris
 *
 * Il gioco prevede tre diverse modalità:
 *      - Single Player
 *      - Multi Player
 *      - Player vs CPU
 *
 *
 *
 *
 * Creato da Bettiol Luca (890424) e Brognera Enrico (890406)
 *
 */
int main() {

    int scelta;

    do {

        scelta = menu();

        switch (scelta) {

            case 1:

                single_player();
                scelta = finePartita();

                break;

            case 2:

                multi_player();
                scelta = finePartita();

                break;

            case 3:

                player_cpu();
                scelta = finePartita();

                break;

            case 9:

                return 0;

            default:

                break;
        }

        cleaner();

    } while (scelta == 0);

    return 0;

}

void single_player(){
    struct Blocco blocchi[N_BLOCCHI];
    struct Piano_Gioco player1;
    int n_blocco, pos_x, rot, perso=0, fine=0;

    inizializza_matrice(&player1);
    inizializza_blocchi(&blocchi[0], 20);

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
    int n_blocco, pos_x, rot, perso = 0, turno = 0, fine=0;

    inizializza_matrice(&player1);
    inizializza_matrice(&player2);
    inizializza_blocchi(&blocchi[0], 40);

    while (perso == 0 && fine==0) {
        stampa_blocchi(blocchi);
        if (turno == 0) {
            printf("P1\n");
            stampa_matrici(player1, player2);
            controllo_input(&rot,&pos_x,&n_blocco, &blocchi[0]);
        } else {
            printf("P2\n");
            stampa_matrici(player1, player2);
            controllo_input(&rot,&pos_x,&n_blocco, &blocchi[0]);
        }

        blocchi[n_blocco].pos_x = pos_x;
        blocchi[n_blocco].num_blocchi--;
        flip_blocco(&blocchi[n_blocco], rot);
        if (turno == 0) {
            perso = inserisci_blocco_multi(&player1, &player2, blocchi[n_blocco]);
            stampa_perso(perso, 1, 0);
        }
        else {
            perso = inserisci_blocco_multi(&player2, &player1, blocchi[n_blocco]);
            stampa_perso(perso, 0, 1);
        }
        fine= fine_blocchi(&blocchi[0]);
        turno = (turno + 1) % 2;
    }
    if(fine!=0)
        stampa_score(player1.score, player2.score);
}

void player_cpu(){
    struct Blocco blocchi[N_BLOCCHI];
    struct Piano_Gioco player1;
    struct Piano_Gioco player2;
    int n_blocco, pos_x, rot, perso = 0, turno = 0, fine=0;

    inizializza_matrice(&player1);
    inizializza_matrice(&player2);
    inizializza_blocchi(&blocchi[0], 40);

    while (perso == 0 && fine==0) {
        stampa_blocchi(blocchi);
        if (turno == 0) {
            printf("P1\n");
            stampa_matrici(player1, player2);
            controllo_input(&rot,&pos_x,&n_blocco, &blocchi[0]);
            /*pos_x= choose_block(&n_blocco,&rot,&blocchi[0],player1);*/
        } else {
            printf("P2\n");
            stampa_matrici(player1, player2);
            pos_x= choose_block(&n_blocco,&rot,&blocchi[0],player2);
        }

        blocchi[n_blocco].pos_x = pos_x;
        blocchi[n_blocco].num_blocchi--;
        flip_blocco(&blocchi[n_blocco], rot);
        if (turno == 0) {
            perso = inserisci_blocco_multi(&player1, &player2, blocchi[n_blocco]);
            stampa_perso(perso, 1, 0);
        }
        else {
            perso = inserisci_blocco_multi(&player2, &player1, blocchi[n_blocco]);
            stampa_perso(perso, 0, 1);
        }
        fine= fine_blocchi(&blocchi[0]);
        turno = (turno + 1) % 2;
    }
    if(fine!=0)
        stampa_score(player1.score, player2.score);
}
>>>>>>> release/1.00
