#include "tetris_components.h"
#include "tetris_operations.h"
#include "NPC_tetris.h"

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

int control_rot(int rot, int n_block){
    /*-1 valore non valido*/
    if(((n_block==0 || n_block==4 || n_block==5) && rot <=1) || (n_block==1 && rot ==0) || ((n_block==2 || n_block==3 || n_block==6) && rot <=3))
        return rot;
    else
        return NNVALIDO;
}

int score_play(struct Blocco *v, struct Piano_Gioco p, int depth, int pos, int rot, int nbloc){
    int errore;
    if(depth==0){
        return 0;
    }else{
        errore= control_nbloc(v, nbloc);
        if(errore==BLOCCHIFINITI){
            return score_play(v, p, depth, pos, rot, nbloc+1);
        }else if(errore==NNVALIDO){
            return score_play(v, p, depth-1, 0, 0, 0);
        }else{
            errore= control_rot(rot, nbloc);
            if(errore==NNVALIDO) {
                return score_play(v, p, depth, 0, 0, nbloc+1);
            }else{
                flip_blocco(&v[nbloc], rot);
                errore= control_pos(v[nbloc], pos);
                if(errore==SPORGEDX)
                    return score_play(v, p, depth, 0, rot+1, nbloc);
                else if(errore==SPORGESX){
                    return score_play(v, p, depth, pos+1, rot, nbloc);
                }else{
                    int score;
                    struct Piano_Gioco copy= p_copia(p);
                    flip_blocco(&v[nbloc], rot);
                    v[nbloc].pos_x=errore;

                    score = inserisci_blocco_score(&p,v[nbloc]);
                    /*stampa_matrice(p);*/
                    return score + score_play(v, copy, depth, pos+1, rot, nbloc) + score_play(v, p, depth-1, 0, 0, 0);

                }
            }
        }
    }
}

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

int choose_block(int *n_block, int *rot, struct Blocco *v, struct Piano_Gioco p){
    int c_block, c_rot, c_pos, pos;
    int score, score_max=-1, top=0, score_app;
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
                            if(score<0)
                                score=0;
                            if(top_play(score, v)==1){
                                top=1;
                                *n_block = c_block;
                                *rot = c_rot;
                                pos = app_pos;
                            }
                            else {
                                score_app = score_play(v, copy, 2, 0, 0, 0);
                                if(score_app>0)
                                    score += score_app;
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


