#include <stdio.h>
#define N_RIGHE  15
#define N_COLONNE  10

/**
 * rappresenta le caratteristiche di un tetramino
 */
struct Blocco{
    int forma[4][4];
    int rotazione;
    int pos_x;
    int num_blocchi;
};

/**
 * rappresenta le caratteristiche di un piano di gioco
 */
struct Piano_Gioco{
    int matrice[N_RIGHE+3][N_COLONNE];
    int score;
};

/**
 * routa un tetramino
 * @param b tetramino da ruotare
 * @param rot rotazione
 */
void flip_blocco(struct Blocco *b, int rot) {
    int i, j, k;
    /*calcolo la rotazione da effettuare per arrivare a rot*/
    rot=(4-(b->rotazione-rot))%4;

    for (k = 0; k < rot; k++) {
        int mat_app[4][4]={0};
        /*copio la matrice*/
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                mat_app[j][3-i]=b->forma[i][j];
            }
        }
        /*giro la matrice del blocco utilizzando la matrice d'appoggio*/
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                b->forma[i][j]=mat_app[i][j];
            }
        }
    }
    b->rotazione=(b->rotazione+rot)%4;
}

/**
 * inizializza il piano di gioco, quindi la matrice che lo compone
 * @param m piano di gioco da inizializzare
 */
void inizializza_matrice(struct Piano_Gioco *m){
    int i, j;
    for(i=0;i<N_RIGHE; i++){
        for (j = 0;  j<N_COLONNE ; j++) {
            m->matrice[i][j]=0;
        }
    }
    for(i=N_RIGHE;i<N_RIGHE+3; i++){
        for (j = 0;  j<N_COLONNE ; j++) {
            m->matrice[i][j]=1;
        }
    }
    m->score=0;
}

/**
 * inizializza il vettore di tetramini, ciascuno sarà composto da una matrice dove il tetramino è rappresentato con un numero divero da 0 mentre gli spazi vuoti saranno 0:
 * il primo tetramino è la linea (1)
 * il secondo tetramino è il quadrato (2)
 * il terzo tetramino è L_sinistra (3)
 * il quarto tetramino è L_destra (4)
 * il quinto tetramino è S_sinistra (5)
 * il sesto tetramino è S_destra (6)
 * il settimo tetramino è la T (7)
 * @param blocchi vettore da inizializzare
 */
void inizializza_blocchi(struct Blocco *blocchi){
    struct Blocco linea={
            {1,1,1,1,0,0,0,0,0,0,0,0},
            0,
            0,
            20,
    };
    struct Blocco quadrato={
            {2,2,0,0,2,2,0,0,0,0,0,0},
            0,
            0,
            20,
    };
    struct Blocco l_sinistra={
            {3,0,0,0,3,3,3,0,0,0,0,0},
            0,
            0,
            20,
    };
    struct Blocco l_destra={
            {0,0,4,0,4,4,4,0,0,0,0,0},
            0,
            0,
            20,
    };
    struct Blocco s_sinistra={
            {0,5,5,0,5,5,0,0,0,0,0,0},
            0,
            0,
            20,
    };
    struct Blocco s_destra={
            {6,6,0,0,0,6,6,0,0,0,0,0},
            0,
            0,
            20,
    };
    struct Blocco t_rov={
            {0,7,0,0,7,7,7,0,0,0,0,0},
            0,
            0,
            20,
    };

    blocchi[0]=linea;
    blocchi[1]=quadrato;
    blocchi[2]=l_sinistra;
    blocchi[3]=l_destra;
    blocchi[4]=s_sinistra;
    blocchi[5]=s_destra;
    blocchi[6]=t_rov;
}

