#include <stdio.h>
#include "tetris_components.h"
#include "tetris_operations.h"

#define NNVALIDO -1
#define BLOCCHIFINITI -2
#define SPORGEDX -5
#define SPORGESX -6

/**
 * effettua una deep copy di un piano di gioco
 * @param p piano di gioco
 * @return deep copy del piano di gioco
 */
struct Piano_Gioco p_copia(struct  Piano_Gioco p){
    struct Piano_Gioco p_copia;
    int i, j;
    for(i=0;i<N_RIGHE+3; i++){
        for(j=0;j<N_COLONNE;j++){
            p_copia.matrice[i][j]=p.matrice[i][j];
        }
    }
    return p_copia;
}

/**
 * controlla la posizione del tetramino da inserire
 * @param b tetramino
 * @param pos posizione
 * @return la posizioni o eventuali errori SPORGEDX o SPORGESX
 */
int control_pos(struct Blocco b, int pos){
    int start_b=-5,finish_b=4, count, i, j;

    for(i=0;i<4;i++){
        count=0;
        for(j=0;j<4;j++){
            if(b.forma[j][i]!=0 && start_b==-5)
                start_b=i;
            if(b.forma[j][i]!=0)
                count=1;
        }
        if(count==0)
            finish_b--;
    }
    if(pos>=0){
        if(pos<N_COLONNE-finish_b+1)
            pos=pos-start_b;
        else
            pos=SPORGEDX;
    }else{
        pos=SPORGESX;
    }
    return pos;
}

/**
 * controlla il numero del tetramino da inserire
 * @param v vettore contenente la descrizione dei tetramini
 * @param nbloc il numero del tetramino
 * @return il numero del tetramino o eventuali errori NNVALIDO o BLOCCHIFINITI
 */
int control_nbloc(struct Blocco *v, int nbloc){
    /*-1 valore non valido
     *-2 blocchi finiti*/
    if(nbloc>=0 && nbloc<N_BLOCCHI){
        if(v[nbloc].num_blocchi<=0)
            nbloc=BLOCCHIFINITI;
    }else{
        nbloc=NNVALIDO;
    }
    return nbloc;
}

/**
 * controlla la rotazione del tetramino da inserire
 * @param rot rotazione
 * @param n_block numero del tetramino
 * @return la rotazione o eventuale errore NNVALIDO
 */
int control_rot(int rot, int n_block){
    /*-1 valore non valido*/
    if((n_block==0 || n_block==4 || n_block==5) && rot <=1)
        return rot;
    else if(n_block==1 && rot ==0 )
        return rot;
    if((n_block==2 || n_block==3 || n_block==6) && rot <=3)
        return rot;
    else
        return NNVALIDO;
}

/**
 * scorre l'albero di gioco e ne calcola il punteggio complessivo
 * @param v vettore contenente la descrizione dei tetramini
 * @param p piano di gioco
 * @param depth profondità dell'albero
 * @param pos posizione
 * @param rot rotazione
 * @param nbloc numero del blocco
 * @return il punteggio
 */
int score_play(struct Blocco *v, struct Piano_Gioco p, int depth, int pos, int rot, int nbloc){
    int errore;
    if(depth==0){
        return 0;
    }else{
        errore= control_nbloc(v, nbloc);
        if(errore==-2){
            return score_play(v, p, depth, pos, rot, nbloc+1);
        }else if(errore==-1){
            return score_play(v, p, depth-1, 0, 0, 0);
        }else{
            errore= control_rot(rot, nbloc);
            if(errore==-1) {
                return score_play(v, p, depth, 0, 0, nbloc+1);
            }else{
                flip_blocco(&v[nbloc], rot);
                errore= control_pos(v[nbloc], pos);
                if(errore==-5)
                    return score_play(v, p, depth, 0, rot+1, nbloc);
                else if(errore==-6){
                    return score_play(v, p, depth, pos+1, rot, nbloc);
                }else{
                    int score;
                    struct Piano_Gioco copy= p_copia(p);
                    flip_blocco(&v[nbloc], rot);
                    v[nbloc].pos_x=errore;

                    score = inserisci_blocco_score(&p,v[nbloc]);
                    //stampa_matrice(p);
                    return score + score_play(v, copy, depth, pos+1, rot, nbloc) + score_play(v, p, depth-1, 0, 0, 0);

                }
            }
        }
    }
}

/**
 * identifica se il tetramino selezionato rappresenta la mossa migliore
 * @param score punteggio effettuato
 * @param v vettore contenente la descrizione dei tetramini
 * @return 1 se è la mossa migliore, 0 altrimenti
 */
int top_play(int score, struct Blocco *v){
    int i, end=0;
    if(score==12){
        return 1;
    }
    for(i=0;i<N_BLOCCHI;i++){
        if(v[i].num_blocchi==0){
            end++;
        }
    }
    if(end>0 && score==6){
        return 1;
    }
    if(end>1 && score==3){
        return 1;
    }
    if(end>2 && score==1){
        return 1;
    }
    return 0;
}

/**
 * verifica quale tetramino, in quele rotazione e in quale posizione effettua un punteggio maggiore
 * @param n_block numero del blocco
 * @param rot rotazione
 * @param v vettore contenente la descrizione dei tetramini
 * @param p piano di gioco
 * @return posizione
 */
int choose_block(int *n_block, int *rot, struct Blocco *v, struct Piano_Gioco p){
    int c_block, c_rot, c_pos, pos;
    int score=0, score_max=-1, top=0;
    *n_block=0;
    *rot=0;
    pos=0;
    for(c_block=0; c_block<N_BLOCCHI && top==0; c_block++){
        if(control_nbloc(v, c_block)>=0){

            for(c_rot=0; c_rot<4 && top==0; c_rot++){
                if(control_rot(c_rot, c_block)>=0) {

                    for (c_pos = 0; c_pos < N_COLONNE && top==0; c_pos++) {

                        int app_pos;
                        flip_blocco(&v[c_block], c_rot);
                        app_pos=control_pos(v[c_block], c_pos);
                        if (app_pos > -5) {

                            struct Piano_Gioco copy= p_copia(p);
                            v[c_block].pos_x = app_pos;
                            score = inserisci_blocco_score(&copy, v[c_block]);
                            if(top_play(score, v)==1){
                                top=1;
                                *n_block = c_block;
                                *rot = c_rot;
                                pos = app_pos;
                            }
                            else {
                                score += score_play(v, copy, 2, 0, 0, 0);
                                if (score > score_max) {
                                    score_max = score;
                                    *n_block = c_block;
                                    *rot = c_rot;
                                    pos = app_pos;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return pos;
}


