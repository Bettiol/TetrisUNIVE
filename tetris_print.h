/**
 * @file tetris_print.h
 * @author Brognera Bettiol
 * @date 07/12/2020
 */
#ifndef TETRISUNIVE_TETRIS_PRINT_H
#define TETRISUNIVE_TETRIS_PRINT_H

/**
 * Funzione che stampa il blocchi utilizzabili e la loro quantità
 * @param b blocco
 */
void stampa_blocchi(struct  Blocco *b);

/**
 * Funzione che stampa il campo di gioco in modalità single player
 * @param m campo di gioco
 */
void stampa_matrice(struct Piano_Gioco m);


/**
 * Funzione che stampa #  colorato in base al blocco selezionato
 * @param colore numero del colore del blocco da stampare
 */
void stampa_colore(int colore);

/**
 * Funzione che stampa i campi di gioco in modalità multi-player
 * @param m1 campo di gioco player 1
 * @param m2 campo di gioco player 2
 */
void stampa_matrici(struct Piano_Gioco m1, struct Piano_Gioco m2);

/**
 * Funzione che stampa il punteggio e il vincitore
 * @param p1 punteggio player 1
 * @param p2 punteggio player 2
 */
void stampa_score(int p1, int p2);

/**
 * Funzione che stampa il vincitore se un payer fuoriesce dal campo di gioco
 * @param perso flag che viene ritornarto dalla funzione che insersce il tetramino nel piano di gioco
 * @param p1 flag che indicache che il player 1 è uscito da lcampo di gioco
 * @param p2 flag che indicache che il player 2 è uscito da lcampo di gioco
 */
void stampa_perso(int perso, int p1, int p2);

/**
 * Funzione che interagisce con l'utente per uscire o andare al menu
 * @return la scelta dell'utente
 */
int finePartita();

/**
 * Funzione che stampa una stringa al centro del terminale
 * @param s stringa da stampare
 */
void centeredPrintf(char *s);

/**
 * Funzione che interagisce con l'utente nel menù
 * @return la scelta dell'utente
 */
int menu();

/**
 * Funzione che pulisce lo schermo
 */
void cleaner();

#endif
