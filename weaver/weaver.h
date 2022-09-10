#ifndef WEAVER_H
#define WEAVER_H

/*
    This should only store functions related to weaver game itself
*/

/* Takes two 4-character strings. Returns 1 if the move is legal, 0 if not */
int is_legal_weaver_move(char *a, char *b);

/* Returns the amount of matching letters */
int get_desirability(char *a, char *b);

#endif