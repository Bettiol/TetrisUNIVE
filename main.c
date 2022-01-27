#include "main.h"
#include "tetris_components.h"
#include "tetris_print.h"
#include "input_control.h"
#include "tetris_operations.h"
#include "NPC_tetris.h"

/**
 * @file main.c
 * @mainpage main PI program
 * @section intro_sec Introduzione
 *
 * Questa è una piccola introduzione, tipo la consegna e le specifiche del
 * programma.
 *
 * @section install_sec Installazione
 * Qui abbiamo creato una nuova sezione dove possiamo scrivere
 * le istruzioni per installare il programma
 * @subsection step1 Step 1: Installa gcc
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
            /*controllo_input(&rot,&pos_x,&n_blocco, &blocchi[0]);*/
            pos_x= choose_block(&n_blocco,&rot,&blocchi[0],player1);
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