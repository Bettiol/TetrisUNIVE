#include <stdio.h>
#include "tetris_components.h"
#include "tetris_print.h"
#include "input_control.h"
#include "tetris_operations.h"
#include "NPC_tetris.h"

/*
 * TO DO
 *  - Menù per la scelta della modalità
 *  - Grafica e messaggi di interazione
 *  - Algoritmo per la CPU
 * */


void single_player();
void multi_player();
void player_cpu();

void centeredPrintf(char *s);
int menu();

int main() {
    //single_player();
    //multi_player();

    int scelta = menu();
    int aiuto;

    switch (scelta) {

        case 1:

            single_player();

            break;

        case 2:

            multi_player();

            break;

        case 3:

            player_cpu();

            break;

        case 9:

            aiuto = help();

            break;
    }

    return 0;
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
        if (p == 0)
            perso = inserisci_blocco_multi(&player1, &player2, blocchi[n_blocco]);
        else
            perso = inserisci_blocco_multi(&player2, &player1, blocchi[n_blocco]);
        p = (p + 1) % 2;
    }
}

void player_cpu(){
    struct Blocco blocchi[N_BLOCCHI];
    struct Piano_Gioco player1;
    int n_blocco, pos_x, rot, perso=0, fine=0;

    inizializza_matrice(&player1);
    inizializza_blocchi(&blocchi[0]);

    while (perso==0 && fine==0) {
        stampa_matrice(player1);

        pos_x= choose_block(&n_blocco,&rot,&blocchi[0],player1);

        blocchi[n_blocco].pos_x = pos_x;
        flip_blocco(&blocchi[n_blocco], rot);
        blocchi[n_blocco].num_blocchi--;

        perso=inserisci_blocco(&player1, blocchi[n_blocco]);
        fine= fine_blocchi(&blocchi[0]);
    }
}


