#ifndef TETRISUNIVE_INPUT_CONTROL_H
#define TETRISUNIVE_INPUT_CONTROL_H

void controllo_input(int *rot, int *pos, int *nbloc, struct Blocco *v);
int controllo_rot();
int controllo_pos(struct Blocco b);
int controllo_nbloc(struct Blocco *v);

#endif
