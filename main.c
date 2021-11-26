#include <stdio.h>

#define N_BLOCCHI  7

#define N_RIGHE  15
#define N_COLONNE  10

/*1*/
#define RED "\e[0;31m"
/*2*/
#define GRN "\e[0;32m"
/*3*/
#define YEL "\e[0;33m"
/*4*/
#define BLU "\e[0;34m"
/*5*/
#define MAG "\e[0;35m"
/*6*/
#define CYN "\e[0;36m"
/*7*/
#define WHT "\e[0;37m"

/*
 * TO DO
 *  - Menù per la scelta della modalità
 *  - Grafica e messaggi di interazione
 *  - Algoritmo per la CPU
 * */

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

void stampa_blocco(struct Blocco b);
void stampa_blocchi(struct  Blocco *b);
void flip_blocco(struct Blocco *b, int rot);
void inizializza_matrice(struct Piano_Gioco *m);
void stampa_matrice(struct Piano_Gioco m);
void inizializza_blocchi(struct Blocco *blocchi);
void stampa_colore(int colore);
void stampa_matrici(struct Piano_Gioco m1, struct Piano_Gioco m2);

int inserisci_blocco(struct Piano_Gioco *m, struct Blocco b);
int caduta_blocco(struct Piano_Gioco *m, struct Blocco b, int piano);
int verifica_posizione_blocco(struct Piano_Gioco *m, struct Blocco b, int piano);
int inserisci_bloccco_posizione(struct Piano_Gioco *m, struct Blocco b, int piano);
void elimina_riga(struct Piano_Gioco *m, int riga);
int score_control(struct Piano_Gioco *m);
void penalita(struct Piano_Gioco *m, int score);
int fine_blocchi(struct Blocco *v);

void controllo_input(int *rot, int *pos, int *nbloc, struct Blocco *v);
int controllo_rot();
int controllo_pos(struct Blocco b);
int controllo_nbloc(struct Blocco *v);

void single_player();
void multi_player();
void player_cpu();


void istruzioni();
void cleaner();
void grafica();

int main() {
    //single_player();
    multi_player();

    //grafica();

    return 0;
}

void stampa_blocco(struct Blocco b){
    int i, j;
    for(i=0;i<4;i++){
        for (j = 0;  j<4 ; j++) {
            stampa_colore(b.forma[i][j]);
        }
        printf("\n");
    }
}

void stampa_blocchi(struct  Blocco *b){
    if(b[0].num_blocchi>0)
        printf("blocco 0\t\trimanenti:%d\nrot: 0 \t\trot: 90 \trot: 180 \trot:270\n"RED"####\t\t#\t\t####\t\t#\n\t\t#\t\t\t\t#\n\t\t#\t\t\t\t#\n\t\t#\t\t\t\t#\n\n"WHT, b[0].num_blocchi);
    if(b[1].num_blocchi>0)
        printf("blocco 1\t\trimanenti:%d\nrot: 0 \t\trot: 90 \trot: 180 \trot:270\n"GRN"##\t\t##\t\t##\t\t##\n##\t\t##\t\t##\t\t##\n\n"WHT, b[1].num_blocchi);
    if(b[2].num_blocchi>0)
        printf("blocco 2\t\trimanenti:%d\nrot: 0 \t\trot: 90 \trot: 180 \trot:270\n"YEL"#\t\t##\t\t###\t\t #\n###\t\t#\t\t  #\t\t #\n\t\t#\t\t\t\t##\n\n"WHT, b[2].num_blocchi);
    if(b[3].num_blocchi>0)
        printf("blocco 3\t\trimanenti:%d\nrot: 0 \t\trot: 90 \trot: 180 \trot:270\n"BLU"  #\t\t#\t\t###\t\t##\n###\t\t#\t\t#\t\t #\n\t\t##\t\t\t\t #\n\n"WHT, b[3].num_blocchi);
    if(b[4].num_blocchi>0)
        printf("blocco 4\t\trimanenti:%d\nrot: 0 \t\trot: 90 \trot: 180 \trot:270\n"MAG" ##\t\t#\t\t ##\t\t#\n##\t\t##\t\t##\t\t##\n\t\t #\t\t\t\t #\n\n"WHT, b[4].num_blocchi);
    if(b[5].num_blocchi>0)
        printf("blocco 5\t\trimanenti:%d\nrot: 0 \t\trot: 90 \trot: 180 \trot:270\n"CYN"##\t\t #\t\t##\t\t #\n ##\t\t##\t\t ##\t\t##\n\t\t#\t\t\t\t#\n\n"WHT, b[5].num_blocchi);
    if(b[6].num_blocchi>0)
        printf("blocco 6\t\trimanenti:%d\nrot: 0 \t\trot: 90 \trot: 180 \trot:270\n"WHT" #\t\t#\t\t###\t\t #\n###\t\t##\t\t #\t\t##\n\t\t#\t\t\t\t #\n\n"WHT, b[6].num_blocchi);

    /*int i;
      for(i=0;i<N_BLOCCHI;i++){
        stampa_blocco(b[i]);
        printf("numero blocchi rimanenti -> %d\n",b[i].num_blocchi);
    }*/
}

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
    printf("score : %d\n",m.score);
    for (j = 0;  j<N_COLONNE ; j++) {
        printf("|%d",j);
    }
    printf("|\n");
    for(i=0;i<N_RIGHE;i++){
        for (j = 0;  j<N_COLONNE ; j++) {
            printf("|");
            stampa_colore(m.matrice[i][j]);
        }
        printf("|\n");
    }
}

void stampa_matrici(struct Piano_Gioco m1, struct Piano_Gioco m2){
    int i, j;
    printf("Player 1");
    printf("\t\t\t\t\t\t\t\t\t");
    printf("Player 2\n");

    printf("Punti P1: %d", m1.score);
    printf("\t\t\t\t\t\t\t\t\t");
    printf("Punti P2: %d\n", m2.score);

    for (j = 0;  j<N_COLONNE ; j++) {
        printf("|%d",j);
    }
    printf("|\t\t\t\t\t\t\t\t\t");
    for (j = 0;  j<N_COLONNE ; j++) {
        printf("|%d",j);
    }
    printf("|\n");

    for(i=0;i<N_RIGHE;i++){
        for (j = 0;  j<N_COLONNE ; j++) {
            printf("|");
            stampa_colore(m1.matrice[i][j]);
        }
        printf("|\t\t\t\t\t\t\t\t\t");
        for (j = 0;  j<N_COLONNE ; j++) {
            printf("|");
            stampa_colore(m2.matrice[i][j]);
        }
        printf("|\n");
    }
}

void stampa_colore(int colore){
    if(colore==1)
        printf(RED"#"WHT);
    else if(colore==2)
        printf(GRN"#"WHT);
    else if(colore==3)
        printf(YEL"#"WHT);
    else if(colore==4)
        printf(BLU"#"WHT);
    else if(colore==5)
        printf(MAG"#"WHT);
    else if(colore==6)
        printf(CYN"#"WHT);
    else if(colore==7)
        printf(WHT"#"WHT);
    else
        printf(" ");
}

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

int inserisci_bloccco_posizione(struct Piano_Gioco *m, struct Blocco b, int piano){
    int i, j;
    int perso=0;
    for(i=3;i>=0 && perso==0;i--) {
        for (j = 0; j < 4 && perso==0; j++) {
            if(piano-(3-i)>=0 && b.pos_x+j<N_COLONNE &&  b.pos_x+j>=0) {
                /*sostituisco i blocchi vuoti del piano di gioco con i nuovi valori del blocco*/
                if (piano - i % 3 >= 0 && m->matrice[piano - (3 - i)][b.pos_x + j] == 0)
                    m->matrice[piano - (3 - i)][b.pos_x + j] = b.forma[i][j];
            }else if(piano-(3-i)<0 && b.forma[i][j]!=0)
                perso=1;
        }
    }
    return perso;
}

int verifica_posizione_blocco(struct Piano_Gioco *m, struct Blocco b, int piano){
    int corretto=1;
    int i,j;
    for(i=3;i>=0 && corretto==1;i--){
        for(j=0;j<4 && corretto==1;j++){
            if(piano-(3-i)>=0 && b.pos_x+j<N_COLONNE &&  b.pos_x+j>=0)
                if(m->matrice[piano-(3-i)][b.pos_x+j]!=0 && b.forma[i][j]!=0)
                    corretto=0;
        }
    }
    return corretto;
}

int caduta_blocco(struct Piano_Gioco *m, struct Blocco b, int piano){
    int corretto=verifica_posizione_blocco(m, b, piano);
    if(corretto==1){
        return caduta_blocco(m,b,piano+1);
    }
    else{
        return inserisci_bloccco_posizione(m,b,piano-1);
    }
}

int inserisci_blocco(struct Piano_Gioco *m, struct Blocco b){
    int perso;
    perso=caduta_blocco(m,b,0);
    if(perso==1){
        printf("hai perso coglione AHAHAHAHAHAH \n\n");
    }
    score_control(m);
    return perso;
}

int inserisci_blocco_multi(struct Piano_Gioco *m1, struct Piano_Gioco *m2, struct Blocco b){
    int perso;
    int score;
    perso=caduta_blocco(m1,b,0);
    if(perso==1){
        printf("hai perso coglione AHAHAHAHAHAH \n\n");
    }
    score= score_control(m1);
    penalita(m2, score);
    return perso;
}


void elimina_riga(struct Piano_Gioco *m, int riga){
    int j, i;
    for(i=riga;i>0;i--){
        for(j=0;j<N_COLONNE;j++){
            m->matrice[i][j]=m->matrice[i-1][j];
        }
    }
    for(j=0;j<N_COLONNE;j++){
        m->matrice[0][j]=0;
    }
}

int score_control(struct Piano_Gioco *m){
    int score=0;
    int i, j;
    int flag;
    for(i=0;i<N_RIGHE;i++){
        flag=0;
        for(j=0;j<N_COLONNE && flag==0;j++){
            if(m->matrice[i][j]==0){
                flag=1;
            }
        }
        if(flag==0){
            score++;
            elimina_riga(m,i);
        }
    }
    if(score==1){
        m->score=m->score+1;
    }else if(score==2){
        m->score=m->score+3;
    }else if(score==3){
        m->score=m->score+6;
    }else if(score==4){
        m->score=m->score+12;
    }

    return score;
}

void penalita(struct Piano_Gioco *m, int score){
    int i;
    int app;
    if(score>=3){
        for(i=0;i<N_COLONNE;i++){
            app=m->matrice[N_RIGHE-1][i];
            m->matrice[N_RIGHE-1][i]=m->matrice[N_RIGHE-2][i];
            m->matrice[N_RIGHE-2][i]=app;
        }
    }
}

void single_player(){
    struct Blocco blocchi[N_BLOCCHI];
    struct Piano_Gioco player1;
    int n_blocco, pos_x, rot, perso=0, fine=0;

    inizializza_matrice(&player1);
    inizializza_blocchi(&blocchi[0]);

    while (perso==0 && fine==0) {
        stampa_blocchi(blocchi);
        stampa_matrice(player1);

        controllo_input(&rot,&pos_x,&n_blocco, &blocchi[0]);

        blocchi[n_blocco].pos_x = pos_x;
        flip_blocco(&blocchi[n_blocco], rot);
        blocchi[n_blocco].num_blocchi--;

        perso=inserisci_blocco(&player1, blocchi[n_blocco]);
        fine= fine_blocchi(&blocchi[0]);
    }
}

void multi_player() {
    struct Blocco blocchi[N_BLOCCHI];
    struct Piano_Gioco player1;
    struct Piano_Gioco player2;
    int n_blocco, pos_x, rot, perso = 0, p = 0;

    inizializza_matrice(&player1);
    inizializza_matrice(&player2);
    inizializza_blocchi(&blocchi[0]);

    while (perso == 0) {
        stampa_blocchi(blocchi);
        if (p == 0) {
            printf("p1\n");
            stampa_matrici(player1, player2);
            controllo_input(&rot,&pos_x,&n_blocco, &blocchi[0]);
        } else {
            printf("p2\n");
            stampa_matrici(player1, player2);
            controllo_input(&rot,&pos_x,&n_blocco, &blocchi[0]);
        }

        blocchi[n_blocco].pos_x = pos_x;
        flip_blocco(&blocchi[n_blocco], rot);
        if (p == 0)
            perso = inserisci_blocco_multi(&player1, &player2, blocchi[n_blocco]);
        else
            perso = inserisci_blocco_multi(&player2, &player1, blocchi[n_blocco]);
        p = (p + 1) % 2;
    }
}

int fine_blocchi(struct Blocco *v){
    int i;
    int fine=1;
    for(i=0;i<N_BLOCCHI && fine==1;i++){
        if(v[i].num_blocchi!=0)
            fine=0;
    }
    if(fine==1){
        printf("hai finito i blocchi AHAHAHAHAHAH\n\n");
    }
    return fine;
}

int controllo_rot(){
    /*-1 valore non valido*/
    int rot=0;
    printf("rotazione -> ");
    scanf("%d", &rot);
    if(rot==0)
        rot=0;
    else if(rot==90)
        rot=1;
    else if(rot==180)
        rot=2;
    else if(rot==270)
        rot=3;
    else
        rot=-1;

    if(rot==-1)
        printf("la rotazione selezionata non esiste\n");
    return rot;
}

int controllo_pos(struct Blocco b){
    /*-1 valore non valido*/
    int pos=0;
    int start_b=-1, i, j;
    printf("posizione -> ");
    scanf("%d", &pos);

    for(i=0;i<4 && start_b==-1;i++){
        for(j=0;j<4 && start_b==-1;j++){
            if(b.forma[j][i]!=0){
                start_b=i;
            }
        }
    }

    if(pos>=0 && pos<N_COLONNE){
        pos=pos-start_b;
    }else{
        pos=-5;
    }

    if(pos==-5)
        printf("la posizione selezionata non è valida\n");
    return pos;
}

int controllo_nbloc(struct Blocco *v){
    /*-1 valore non valido*/
    int nbloc=0;
    printf("blocco -> ");
    scanf("%d", &nbloc);
    if(nbloc>=0 && nbloc<N_BLOCCHI){
        if(v[nbloc].num_blocchi<=0)
            nbloc=-1;
    }else{
        nbloc=-1;
    }

    if(nbloc==-1)
        printf("il blocco selezionato non esiste\n");
    return nbloc;
}

void controllo_input(int *rot, int *pos, int *nbloc, struct Blocco *v){
    do{
        *nbloc=controllo_nbloc(v);
    }while(*nbloc==-1);
    do{
        *rot=controllo_rot();
    }while(*rot==-1);
    do{
        flip_blocco(&v[*nbloc], *rot);
        *pos=controllo_pos(v[*nbloc]);
    }while(*pos==-5);
}

void cleaner() {
    printf("\e[1;1H\e[2J");
}

void grafica() {

    printf("Player 1");
    printf("\t\t\t\t\t\t\t\t\t");
    printf("Player 2\n");

    printf("Punti P1: ");
    printf("\t\t\t\t\t\t\t\t\t");
    printf("Punti P2: \n");

    int t;
    scanf("%d", &t);
    printf("%d", t);
    cleaner();

}

void istruzioni() {

    printf("\t\t\t\t\t\t");

}