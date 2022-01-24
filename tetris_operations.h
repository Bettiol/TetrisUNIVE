#ifndef TETRISUNIVE_TETRIS_OPERATIONS_H
#define TETRISUNIVE_TETRIS_OPERATIONS_H

int verifica_posizione_blocco(struct Piano_Gioco *m, struct Blocco b, int piano);
int caduta_blocco(struct Piano_Gioco *m, struct Blocco b, int piano);
int inserisci_blocco(struct Piano_Gioco *m, struct Blocco b);
int inserisci_blocco_multi(struct Piano_Gioco *m1, struct Piano_Gioco *m2, struct Blocco b);
void elimina_riga(struct Piano_Gioco *m, int riga);
int score_control(struct Piano_Gioco *m);
void penalita(struct Piano_Gioco *m, int score);
int fine_blocchi(struct Blocco *v);

int inserisci_bloccco_posizione(struct Piano_Gioco *m, struct Blocco b, int piano);
int inserisci_blocco_score(struct Piano_Gioco *m, struct Blocco b);

#endif
