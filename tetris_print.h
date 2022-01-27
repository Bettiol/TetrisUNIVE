#ifndef TETRISUNIVE_TETRIS_PRINT_H
#define TETRISUNIVE_TETRIS_PRINT_H

void stampa_blocco(struct Blocco b);
void stampa_blocchi(struct  Blocco *b);
void stampa_matrice(struct Piano_Gioco m);
void stampa_colore(int colore);
void stampa_matrici(struct Piano_Gioco m1, struct Piano_Gioco m2);
void stampa_score(int p1, int p2);
void stampa_perso(int perso, int p1, int p2);
int help();
void cleaner();
void centeredPrintf(char *s);
int menu();

#endif
