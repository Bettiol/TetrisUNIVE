#ifndef TETRISUNIVE_TETRIS_OPERATIONS_H
#define TETRISUNIVE_TETRIS_OPERATIONS_H


/**
 * verifica la correttezza del tetramino nel piano selezionato
 * @param m piano di gioco
 * @param b tetramino
 * @param piano livello del piano di gioco
 * @return 1 se è corretto 0 altrimenti
 */
int verifica_posizione_blocco(struct Piano_Gioco *m, struct Blocco b, int piano);

/**
 * verifica la correttezza del tetramino nel piano selezionato, se è corretto prova a inserire il tetramino nel piano sucessivo, altrimenti lo inserisce sul piano precedente
 * @param m piano di gioco
 * @param b tetramino
 * @param piano livello del piano da inserire
 * @return 1 se il giocatore ha perso 0 altrimenti
 */
int caduta_blocco(struct Piano_Gioco *m, struct Blocco b, int piano);

/**
 * inserisce un tetramino nel piano di gioco nella modalità single_player
 * @param m piano di gioco
 * @param b tetramino da inserire
 * @return 1 se il giocatore ha perso 0 altrimenti
 */
int inserisci_blocco(struct Piano_Gioco *m, struct Blocco b);

/**
 * inserisce un tetramino nel piano di gioco nella modalità multi_player
 * @param m1 piano di gioco
 * @param m2 piano di gioco avversario
 * @param b tetramino da inserire
 * @return 1 se il giocatore ha perso 0 altrimenti
 */
int inserisci_blocco_multi(struct Piano_Gioco *m1, struct Piano_Gioco *m2, struct Blocco b);

/**
 * elimina una riga dal piano di gioco
 * @param m piano di gioco
 * @param riga riga da eliminare
 */
void elimina_riga(struct Piano_Gioco *m, int riga);

/**
 * verifica e conta il punteggio il punteggio ottenuto ed elimina le eventuali rige completate
 * @param m piano di gioco
 * @return il punteggio ottenuto
 */
int score_control(struct Piano_Gioco *m);

/**
 * inverte le ultime due rige del piano di gioco se lo score è maggiore o uguale a 6
 * @param m piano di gioco avversario
 * @param score punteggio effettuato
 */
void penalita(struct Piano_Gioco *m, int score);

/**
 * verifica se sono finiti tutti i blocchi disponibili
 * @param v il vettore contenente la descrizione di ciascun tetramino
 * @return 1 se sono finiti i tetramini 0 altrimenti
 */
int fine_blocchi(struct Blocco *v);

/**
 * inserisce un tetramino nel piano di gioco in un livello
 * @param m piano di gioco
 * @param b tetramino
 * @param piano il livello del piano di gioco
 * @return 1 se il giocatore ha perso 0 altrimenti
 */
int inserisci_bloccco_posizione(struct Piano_Gioco *m, struct Blocco b, int piano);

/**
 * inserisce un tetramino in un piano di gioco e ne restituisce il punteggio ottenuto
 * @param m piano di gioco
 * @param b tetramino
 * @return -1 se ha perso altrimenti il punteggio effettuato
 */
int inserisci_blocco_score(struct Piano_Gioco *m, struct Blocco b);

#endif
