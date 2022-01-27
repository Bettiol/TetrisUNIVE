/**
 * @file NPC_tetris.h
 * @authors Bettiol Luca, Brognera Enrico
 * @date 27/01/2022
 */
#ifndef TETRISUNIVE_NPC_TETRIS_H
#define TETRISUNIVE_NPC_TETRIS_H

#include <stdio.h>

#define NNVALIDO -1
#define BLOCCHIFINITI -2
#define SPORGEDX -5
#define SPORGESX -6

/**
 * Verifica quale tetramino, in quele rotazione e in quale posizione effettua un punteggio maggiore
 * @param n_block numero del blocco
 * @param rot rotazione
 * @param v vettore contenente la descrizione dei tetramini
 * @param p piano di gioco
 * @return posizione
 */
int choose_block(int *n_block, int *rot, struct Blocco *v, struct Piano_Gioco p);

/**
 * Effettua una deep copy di un piano di gioco
 * @param p piano di gioco
 * @return deep copy del piano di gioco
 */
struct Piano_Gioco p_copia(struct  Piano_Gioco p);

/**
 * Controlla la posizione del tetramino da inserire
 * @param b tetramino
 * @param pos posizione
 * @return la posizioni o eventuali errori SPORGEDX o SPORGESX
 */
int control_pos(struct Blocco b, int pos);

/**
 * Controlla il numero del tetramino da inserire
 * @param v vettore contenente la descrizione dei tetramini
 * @param nbloc il numero del tetramino
 * @return il numero del tetramino o eventuali errori NNVALIDO o BLOCCHIFINITI
 */
int control_nbloc(struct Blocco *v, int nbloc);

/**
 * Controlla la rotazione del tetramino da inserire
 * @param rot rotazione
 * @param n_block numero del tetramino
 * @return la rotazione o eventuale errore NNVALIDO
 */
int control_rot(int rot, int n_block);
/**
 * Scorre l'albero di gioco e ne calcola il punteggio complessivo
 * @param v vettore contenente la descrizione dei tetramini
 * @param p piano di gioco
 * @param depth profondità dell'albero
 * @param pos posizione
 * @param rot rotazione
 * @param nbloc numero del blocco
 * @return il punteggio
 */
int score_play(struct Blocco *v, struct Piano_Gioco p, int depth, int pos, int rot, int nbloc);

/**
 * Identifica se il tetramino selezionato rappresenta la mossa migliore
 * @param score punteggio effettuato
 * @param v vettore contenente la descrizione dei tetramini
 * @return 1 se è la mossa migliore, 0 altrimenti
 */
int top_play(int score, struct Blocco *v);

#endif
