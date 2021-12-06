#ifndef TETRISUNIVE_TETRIS_PRINT_H
#define TETRISUNIVE_TETRIS_PRINT_H

void stampa_blocco(struct Blocco b);
void stampa_blocchi(struct  Blocco *b);
void stampa_matrice(struct Piano_Gioco m);
void stampa_colore(int colore);
void stampa_matrici(struct Piano_Gioco m1, struct Piano_Gioco m2);
int help();
void cleaner();
void centeredPrintf(char *s);
int menu();
void cleaner();

#endif //TETRISUNIVE_TETRIS_PRINT_H
