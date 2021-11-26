#ifndef TETRISUNIVE_TETRIS_COMPONENTS_H
#define TETRISUNIVE_TETRIS_COMPONENTS_H

#define N_BLOCCHI  7
#define N_RIGHE  15
#define N_COLONNE  10

struct Blocco{
    int forma[4][4];
    int rotazione;
    int pos_x;
    int num_blocchi;
};

struct Piano_Gioco{
    int matrice[N_RIGHE+3][N_COLONNE];
    int score;
};
void inizializza_blocchi(struct Blocco *blocchi);
void flip_blocco(struct Blocco *b, int rot);
void inizializza_matrice(struct Piano_Gioco *m);

#endif //TETRISUNIVE_TETRIS_COMPONENTS_H
