/**
 * @file input_control.h
 * @authors Bettiol Luca, Brognera Enrico
 * @date 27/01/2022
 */
#ifndef TETRISUNIVE_INPUT_CONTROL_H
#define TETRISUNIVE_INPUT_CONTROL_H

/**
 * Effettua la richiesta e la verifica di tutti i parametri per l'inserimento di un tetramino
 * @param rot la rotazione
 * @param pos la posizione
 * @param nbloc il numero del tetramino
 * @param v il vettore contenente la descrizione di ciascun tetramino
 */
void controllo_input(int *rot, int *pos, int *nbloc, struct Blocco *v);

/**
 * Effetua la richiesta dell'input 'rotazione' e ne verifica la correttezza
 * @return la rotazione del tetramino
 */
int controllo_rot();

/**
 * Effettua la richiesta dell'input 'posizione' e ne verifica la correttezza
 * @param b il blocco selezionato di cui si vuole richiedere la posizione
 * @return la posizione del tetramino
 */
int controllo_pos(struct Blocco b);

/**
 * Effettua la richiesta dell'input 'numero del tetramino' e ne verifica la correttezza
 * @param v il vettore contenente il numero di tetramino rimanenti
 * @return il numero del tetramino
 */
int controllo_nbloc(struct Blocco *v);

#endif
