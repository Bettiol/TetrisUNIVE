#include <stdio.h>
#include "tetris_components.h"
#include <string.h>
#include "tetris_print.h"

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
    else if(colore==8)
        printf(GRY"#"WHT);
    else
        printf(" ");
}

void stampa_blocchi(struct  Blocco *b){

    if(b[0].num_blocchi>0)
        printf(BLOCCO0, b[0].num_blocchi);
    if(b[1].num_blocchi>0)
        printf(BLOCCO1, b[1].num_blocchi);
    if(b[2].num_blocchi>0)
        printf(BLOCCO2, b[2].num_blocchi);
    if(b[3].num_blocchi>0)
        printf(BLOCCO3, b[3].num_blocchi);
    if(b[4].num_blocchi>0)
        printf(BLOCCO4, b[4].num_blocchi);
    if(b[5].num_blocchi>0)
        printf(BLOCCO5, b[5].num_blocchi);
    if(b[6].num_blocchi>0)
        printf(BLOCCO6, b[6].num_blocchi);

}

void stampa_matrice(struct Piano_Gioco m){
    int i, j;
    printf("Score : %d\n",m.score);
    for (j = 0;  j<N_COLONNE ; j++) {
        printf("|%d",j);
    }
    printf("|\n");
    for(i=0;i<N_RIGHE;i++){
        for (j = 0;  j<N_COLONNE ; j++) {
            printf("|");
            stampa_colore(m.matrice[i][j]);
        }
        printf("|\n");
    }
}

void stampa_matrici(struct Piano_Gioco m1, struct Piano_Gioco m2){
    int i, j;
    printf("Player 1");
    printf("\t\t\t\t\t\t\t\t\t");
    printf("Player 2\n");

    printf("Punti P1: %d", m1.score);
    printf("\t\t\t\t\t\t\t\t\t");
    printf("Punti P2: %d\n", m2.score);

    for (j = 0;  j<N_COLONNE ; j++) {
        printf("|%d",j);
    }
    printf("|\t\t\t\t\t\t\t\t\t");
    for (j = 0;  j<N_COLONNE ; j++) {
        printf("|%d",j);
    }
    printf("|\n");

    for(i=0;i<N_RIGHE;i++){
        for (j = 0;  j<N_COLONNE ; j++) {
            printf("|");
            stampa_colore(m1.matrice[i][j]);
        }
        printf("|\t\t\t\t\t\t\t\t\t");
        for (j = 0;  j<N_COLONNE ; j++) {
            printf("|");
            stampa_colore(m2.matrice[i][j]);
        }
        printf("|\n");
    }

}

void stampa_score(int p1, int p2){
    printf("Score Player 1 -> %d\t\t\t Score Player 2 -> %d\n", p1, p2);
    if(p1>p2)
        printf("\n\nComplimenti Player 1, hai VINTO!\n\n");
    else if(p2>p1)
        printf("\n\nComplimenti Player 2, hai VINTO!\n\n");
    else
        printf("\n\nPlayer 1 e Player 2, avete PAREGGIATO!\n\n");
}

void stampa_perso(int perso, int p1, int p2){
    if(perso==1 && p1==1){
        printf("\n\nPlayer 1 sei uscito dal campo di gioco. Complimenti Player 2, hai VINTO!\n\n");
    }
    if(perso==1 && p2==1){
        printf("\n\nPlayer 2 sei uscito dal campo di gioco. Complimenti Player 1, hai VINTO!\n\n");
    }
}

void centeredPrintf(char *s) {

    int larghezza = 240;
    int lungString = (int)strlen(s);
    int larghezzaCent = (larghezza - lungString) / 2 + lungString;

    printf("%*s\n", larghezzaCent, s);

}

int menu() {

    char titolo[] = "X-TETRIS";
    char modalita1[] = "1) Single Player";
    char modalita2[] = "2) Multiplayer Player";
    char modalita3[] = "3) Player vs CPU";
    char exit[] = "9) Esci";
    int scelta;


    centeredPrintf(titolo);

    printf("\n");
    printf("\n");
    printf("\n");

    centeredPrintf(modalita1);
    centeredPrintf(modalita2);
    centeredPrintf(modalita3);
    printf("\n");
    centeredPrintf(exit);

    do {

        printf("Inserire il numero corrispondente all'opzione desisderata --> ");
        scanf("%d", &scelta);

    } while (scelta != 1 && scelta != 2 && scelta != 3 && scelta != 9);

    return scelta;

}

int finePartita() {

    int scelta;

    do {

        printf("\n\nPer tornare al menù premere 0, per uscire premere 9 --> ");
        scanf("%d", &scelta);

    } while (scelta != 0 && scelta != 9);

    return scelta;

}

void cleaner() {

    int i;

    for (i = 0; i < 1000; ++i) {

        printf("\n");

    }
}

