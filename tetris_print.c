#include <stdio.h>
#include "tetris_components.h"
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

/*1*/
#define RED "\033[0;31m"
/*2*/
#define GRN "\033[0;32m"
/*3*/
#define YEL "\033[0;33m"
/*4*/
#define BLU "\033[0;34m"
/*5*/
#define MAG "\033[0;35m"
/*6*/
#define CYN "\033[0;36m"
/*7*/
#define WHT "\033[0;37m"
/*8*/
#define GRY "\033[0;90m"


#define BLOCCO0 "BLOCCO 0\t\tRIMANENTI:%d\nROT: 0/180 \t\tROT: 90/270 \n"RED"####\t\t\t#\n\t\t\t#\n\t\t\t#\n\t\t\t#\n\n"WHT
#define BLOCCO1 "BLOCCO 1\t\tRIMANENTI:%d\nROT: 0/90/180/270\n"GRN"##\n##\n\n"WHT
#define BLOCCO2 "BLOCCO 2\t\tRIMANENTI:%d\nROT: 0 \t\tROT: 90 \tROT: 180 \tROT:270\n"YEL"#\t\t##\t\t###\t\t #\n###\t\t#\t\t  #\t\t #\n\t\t#\t\t\t\t##\n\n"WHT
#define BLOCCO3 "BLOCCO 3\t\tRIMANENTI:%d\nROT: 0 \t\tROT: 90 \tROT: 180 \tROT:270\n"BLU"  #\t\t#\t\t###\t\t##\n###\t\t#\t\t#\t\t #\n\t\t##\t\t\t\t #\n\n"WHT
#define BLOCCO4 "BLOCCO 4\t\tRIMANENTI:%d\nROT: 0/180 \t\tROT: 90/270\n"MAG" ##\t\t\t#\n##\t\t\t##\n\t\t\t #\n\n"WHT
#define BLOCCO5 "BLOCCO 5\t\tRIMANENTI:%d\nROT: 0/180 \t\tROT: 90/270\n"CYN"##\t\t\t #\n ##\t\t\t##\n\t\t\t#\n\n"WHT
#define BLOCCO6 "BLOCCO 6\t\tRIMANENTI:%d\nROT: 0 \t\tROT: 90 \tROT: 180 \tROT:270\n"WHT" #\t\t#\t\t###\t\t #\n###\t\t##\t\t #\t\t##\n\t\t#\t\t\t\t #\n\n"WHT

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

    /*int i;
      for(i=0;i<N_BLOCCHI;i++){
        stampa_blocco(b[i]);
        printf("numero blocchi RIMANENTI -> %d\n",b[i].num_blocchi);
    }*/
}

void stampa_matrice(struct Piano_Gioco m){
    int i, j;
    printf("score : %d\n",m.score);
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
    printf("score P1 -> %d\t\t\t score P2 -> %d\n", p1, p2);
    if(p1>p2)
        printf("HA VINTO P1\n");
    else if(p2>p1)
        printf("HA VINTO P2\n");
    else
        printf("PAREGGIO\n");
}

void stampa_perso(int perso, int p1, int p2){
    if(perso==1 && p1==1){
        printf("HA PERSO P1 \t VINCITORE P2\n\n");
    }
    if(perso==1 && p2==1){
        printf("HA PERSO P2 \t VINCITORE P1\n\n");
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
void centeredPrintf(char *s) {

    int total_width = GetColumnWidth();
    int s_width = strlen(s);
    int field_width = (total_width - s_width) / 2 + s_width;

    printf("%*s\n", field_width, s);

}

int menu() {

    char titolo[] = "TermTris";
    char modalita1[] = "1) Single Player";
    char modalita2[] = "2) Multiplayer Player";
    char modalita3[] = "3) Player vs CPU";
    int scelta;


    centeredPrintf(titolo);

    printf("\n");
    printf("\n");
    printf("\n");

    centeredPrintf(modalita1);
    centeredPrintf(modalita2);
    centeredPrintf(modalita3);
    printf("\n");

    do {

        printf("Inserire il numero corrispondente all'opzione desisderata --> ");
        scanf("%d", &scelta);

    } while (scelta != 1 && scelta != 2 && scelta != 3);

    return scelta;

}

void cleaner() {
    system("CLEAR");
}
