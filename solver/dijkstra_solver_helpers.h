#ifndef DIJKSTRA_SOLVER_H
#define DIJKSTRA_SOLVER_H

#define DIJKSTRA_INFINITY 9999999
#define DIJKSTRA_PATH_ROOT -1

#include "../datastructures/word_graph.h"

struct path_data_dijkstra {
    int visited;
    int distance;
    int source;
};

/* Finds the next node with smallest distance */
int get_next_node (struct word_graph_node *graph, int graphSize);

/* Prints debug information for the graph */
void dijsktra_debug (struct word_graph_node *graph, int graphSize);

/* Returns a 1 if true */
int is_visited (struct word_graph_node *graph, int node);

int get_distance (struct word_graph_node *graph, int node);

void set_distance (struct word_graph_node *graph, int node, int distance);

void set_source (struct word_graph_node *graph, int node, int new_source);

void mark_visited (struct word_graph_node *graph, int node);

/* 
    Return an array of unvisited neighbours and writes their amount to count 
    REMEMBER TO FREE THE RETURNED ARRAY
*/
int *get_unvisited_neighbours (struct word_graph_node *graph, int node, int *count);

void free_graph_data (struct word_graph_node *graph, int graphSize);

#endif