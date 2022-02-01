/**
 * @file tetris_components.h
 * @authors Bettiol Luca, Brognera Enrico
 * @date 27/01/2022
 */
#ifndef TETRISUNIVE_TETRIS_COMPONENTS_H
#define TETRISUNIVE_TETRIS_COMPONENTS_H

#define N_BLOCCHI  7
#define N_RIGHE  15
#define N_COLONNE  10

/**
 * Rappresenta le caratteristiche di un tetramino
 */
struct Blocco{
    int forma[4][4];
    int rotazione;
    int pos_x;
    int num_blocchi;
};

/**
 * Rappresenta le caratteristiche di un piano di gioco
 */
struct Piano_Gioco{
    int matrice[N_RIGHE+3][N_COLONNE];
    int score;
};

/**
 * Inizializza il vettore di tetramini, ciascuno sarà composto da una matrice dove il tetramino è rappresentato con un numero divero da 0 mentre gli spazi vuoti saranno 0:
 * il primo tetramino è la linea (1)
 * il secondo tetramino è il quadrato (2)
 * il terzo tetramino è L_sinistra (3)
 * il quarto tetramino è L_destra (4)
 * il quinto tetramino è S_sinistra (5)
 * il sesto tetramino è S_destra (6)
 * il settimo tetramino è la T (7)
 * @param blocchi vettore da inizializzare
 */
void inizializza_blocchi(struct Blocco *blocchi, int num_blocchi);

/**
 * Routa un tetramino
 * @param b tetramino da ruotare
 * @param rot rotazione
 */
void flip_blocco(struct Blocco *b, int rot);

/**
 * Inizializza il piano di gioco, quindi la matrice che lo compone
 * @param m piano di gioco da inizializzare
 * @param num_blocchi numero di tetramini disponibili
 */
void inizializza_matrice(struct Piano_Gioco *m);

#endif
