#ifndef WEAVER_SOLVER_H
#define WEAVER_SOLVER_H

#include "../datastructures/word_graph.h"

/* Returns a pointer to an array of steps, writes the length into &steps */
int *solve_dijkstra (struct word_graph_node *graph, int graphSize, char (*words)[5], int word_a, int word_b, int *steps);

#endif