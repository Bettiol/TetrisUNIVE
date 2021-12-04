#include <stdio.h>
#include "tetris_components.h"
#include "tetris_print.h"
#include "input_control.h"
#include "tetris_operations.h"
#include "NPC_tetris.h"
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


void single_player();
void multi_player();
void player_cpu();


int help();
void cleaner();
void grafica();
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
    int scelta;


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
        scanf("%d", &scelta);

    } while (scelta != 1 && scelta != 2 && scelta != 3 && scelta != 9);

    return scelta;

}

int help() {

    char titolo[] = "TermTris - Help";
    char help1[] = "1) Modalità";
    char help2[] = "2) Pezzi";
    char help3[] = "3) Help";
    char help4[] = "4) Punteggi";
    char help5[] = "5) Regole";

    int scelta;


    centeredPrintf(titolo);

    printf("\n");
    printf("\n");
    printf("\n");

    centeredPrintf(help1);
    centeredPrintf(help2);
    centeredPrintf(help3);
    centeredPrintf(help4);
    centeredPrintf(help5);

    do {

        printf("Inserire il numero corrispondente all'opzione desiderata --> ");
        scanf("%d", &scelta);

    } while (scelta != 1 && scelta != 2 && scelta != 3 && scelta != 4 && scelta != 5);

    return scelta;


}

void centeredPrintf(char *s) {

    int total_width = GetColumnWidth();
    int s_width = strlen(s);
    int field_width = (total_width - s_width) / 2 + s_width;

    printf("%*s\n", field_width, s);

}