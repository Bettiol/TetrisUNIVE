#include <stdio.h>

#define N_BLOCCHI  7

#define N_RIGHE  20
#define N_COLONNE  10

struct Blocco{
    int forma[4][4];
    int rotazione;
    int pos_x;
};

struct Piano_Gioco{
    int matrice[N_RIGHE+3][N_COLONNE];
    int score;
};

void stampa_blocco(struct Blocco b);
void stampa_blocchi(struct  Blocco *b);
void flip_blocco(struct Blocco *b, int rot);
void flip_blocco_0(struct Blocco *b);
void inizializza_matrice(struct Piano_Gioco *m);
void stampa_matrice(struct Piano_Gioco m);
void inizializza_blocchi(struct Blocco *blocchi);

void inserisci_blocco(struct Piano_Gioco *m, struct Blocco b);
void caduta_blocco(struct Piano_Gioco *m, struct Blocco b, int piano);
int verifica_posizione_blocco(struct Piano_Gioco *m, struct Blocco b, int piano);
void inserisci_bloccco_posizione(struct Piano_Gioco *m, struct Blocco b, int piano);

int main() {
    struct Blocco blocchi[N_BLOCCHI];

    struct Piano_Gioco player1;
    inizializza_matrice(&player1);
    inizializza_blocchi(&blocchi);

    /*richiesta blocco, posizione e rotazione*/

    blocchi[0].pos_x=5;
    flip_blocco(&blocchi[0],1);

    inserisci_blocco(&player1, blocchi[0]);

    stampa_matrice(player1);
    printf("\n\n");

    blocchi[1].pos_x=5;
    flip_blocco(&blocchi[1],0);

    inserisci_blocco(&player1, blocchi[1]);

    stampa_matrice(player1);

    printf("\n\n");

    blocchi[2].pos_x=5;
    flip_blocco(&blocchi[2],2);

    inserisci_blocco(&player1, blocchi[2]);

    stampa_matrice(player1);

    printf("\n\n");

    /*ripeti il tutto*/

    return 0;
}

void stampa_blocco(struct Blocco b){
    int i, j;
    for(i=0;i<4;i++){
        for (j = 0;  j<4 ; j++) {
            if(b.forma[i][j]!=0)
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void stampa_blocchi(struct  Blocco *b){
    int i;
    for(i=0;i<N_BLOCCHI;i++){
        stampa_blocco(b[i]);
    }
}

void flip_blocco(struct Blocco *b, int rot) {
    int i, j, k;
    printf("%d %d\n",rot, b->rotazione);
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

void stampa_matrice(struct Piano_Gioco m){
    int i, j;
    for(i=0;i<N_RIGHE;i++){
        for (j = 0;  j<N_COLONNE ; j++) {
            if(m.matrice[i][j]==0)
                printf(".");
            else
                printf("#");
        }
        printf("\n");
    }
}

void inizializza_blocchi(struct Blocco *blocchi){
    struct Blocco linea={
            {1,1,1,1,0,0,0,0,0,0,0,0},
            0,
            0,
    };
    struct Blocco quadrato={
            {1,1,0,0,1,1,0,0,0,0,0,0},
            0,
            0,
    };
    struct Blocco l_sinistra={
            {1,0,0,0,1,1,1,0,0,0,0,0},
            0,
    };
    struct Blocco l_destra={
            {0,0,1,0,1,1,1,0,0,0,0,0},
            0,
            0,
    };
    struct Blocco s_sinistra={
            {0,1,1,0,1,1,0,0,0,0,0,0},
            0,
            0,
    };
    struct Blocco s_destra={
            {1,1,0,0,0,1,1,0,0,0,0,0},
            0,
            0,
    };
    struct Blocco t_rov={
            {0,1,0,0,1,1,1,0,0,0,0,0},
            0,
            0,
    };

    blocchi[0]=linea;
    blocchi[1]=quadrato;
    blocchi[2]=l_sinistra;
    blocchi[3]=l_destra;
    blocchi[4]=s_sinistra;
    blocchi[5]=s_destra;
    blocchi[6]=t_rov;
}

/*void inserisci_blocco(struct Piano_Gioco *m, struct Blocco b){
    int i, j;

    for(i=16;i<20;i++){
        for(j=0;j<4;j++){
            m->matrice[i][j]=b.forma[i-16][j];
        }
    }
}*/

/*void inserisci_blocco(struct Piano_Gioco *m, struct Blocco b){
    int i, j, k;
    int vuoti;
    int h;

    for(i=0;i<4;i++){
        k=0;
        for(j=b.pos_x;j<b.pos_x+4;j++){
            m->matrice[i][j]=b.forma[i][k];
            k++;
        }
    }
    stampa_matrice(*m);
    printf("dio\n\n");


    i=19;
    h=0;
     while (i>h){
         vuoti=0;
         for(j=b.pos_x;j<b.pos_x+4;j++){

             if(m->matrice[i][j]!=0)
                 vuoti++;
         }
         printf("2");

         if(vuoti==N_COLONNE || vuoti==0) {
             if (vuoti == 0)
                 m->score++;
             printf("3");
             for (j = i;j>0;j++) {
                for(k=b.pos_x;k<b.pos_x+4;k++){
                    m->matrice[j][k]=m->matrice[j+1][k];
                }
             }
             for(k=b.pos_x;k<b.pos_x+4;k++){
                 m->matrice[0][k]=0;
             }
             h++;
         }else{
             i--;
         }
         stampa_matrice(*m);
         printf("\n\n");
    }

}*/

void inserisci_bloccco_posizione(struct Piano_Gioco *m, struct Blocco b, int piano){
    int i, j;
    for(i=3;i>=0;i--) {
        for (j = 0; j < 4; j++) {
            if (piano - i % 3 >= 0 && m->matrice[piano - (3-i)][b.pos_x + j]==0)
                m->matrice[piano - (3-i)][b.pos_x + j] = b.forma[i][j];
        }
    }
}

int verifica_posizione_blocco(struct Piano_Gioco *m, struct Blocco b, int piano){
    int corretto=1;
    int i,j;
    for(i=3;i>=0 && corretto==1;i--){
        for(j=0;j<4 && corretto==1;j++){
            if(piano-(3-i)>=0)
                if(m->matrice[piano-(3-i)][b.pos_x+j]!=0 && b.forma[i][j]!=0)
                    corretto=0;
        }
    }
    return corretto;
}

void caduta_blocco(struct Piano_Gioco *m, struct Blocco b, int piano){
    int corretto=verifica_posizione_blocco(m, b, piano);
    if(corretto==1){
        caduta_blocco(m,b,piano+1);
    }
    else{
        inserisci_bloccco_posizione(m,b,piano-1);
    }
}

void inserisci_blocco(struct Piano_Gioco *m, struct Blocco b){
    int flag=0;
    caduta_blocco(m,b,0);
    /*controlla se vinto o se score aumenta*/
}