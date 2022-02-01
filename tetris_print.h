/**
 * @file tetris_print.h
 * @authors Bettiol Luca, Brognera Enrico
 * @date 27/01/2022
 */
#ifndef TETRISUNIVE_TETRIS_PRINT_H
#define TETRISUNIVE_TETRIS_PRINT_H

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
