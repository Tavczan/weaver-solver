#ifndef WEAVER_SOLVER_C
#define WEAVER_SOLVER_C

#include "weaver_solver.h"
#include "../weaver/weaver.h"
#include <stdlib.h>

#include "dijkstra_solver_helpers.h"
#include "dijkstra_solver_helpers.c"

int *solve_dijkstra (struct word_graph_node *graph, int graphSize, char (*words)[5], int word_a, int word_b, int *steps)
{
    // Edge caseeeesss
    if (word_a == word_b) return NULL;
    if (graphSize < 2) return NULL;

    // Populate the graph with data for pathfinding

    for (int i = 0; i < graphSize; i++)
    {
        graph[i].data = malloc(sizeof(struct path_data_dijkstra));
        ((struct path_data_dijkstra*) graph[i].data)->distance = DIJKSTRA_INFINITY;
        ((struct path_data_dijkstra*) graph[i].data)->visited = 0;
        ((struct path_data_dijkstra*) graph[i].data)->source = DIJKSTRA_PATH_ROOT; 
    }

    // Prepare the starting node

    ((struct path_data_dijkstra*) graph[word_a].data)->distance = 0;

    int current_node = word_a;

    // While the node is reachable
    while (get_distance(graph, current_node) != DIJKSTRA_INFINITY)
    {
        // Do distance setting on unvisited neighbouring nodes
        int unvisited_count;
        int *unvisited = get_unvisited_neighbours(graph, current_node, &unvisited_count);
        int current_distance = get_distance(graph, current_node);

        for (int i = 0 ; i < unvisited_count; i++)
        {
            if (get_distance(graph, unvisited[i]) > current_distance+1)
            {
                set_distance(graph, unvisited[i], current_distance+1);
                set_source(graph, unvisited[i], current_node);
            }
        }

        // Done in this node, it will not be visited again
        mark_visited(graph,current_node);

        free(unvisited);

        // Did we mark the word_b node as visited? If so, we're done and it's time to prepare the output
        if (current_node == word_b)
        {
            int *toreturn = malloc(sizeof(int)*current_distance+1);
            int pointer = current_node;
            int counter = current_distance;
            while (pointer != DIJKSTRA_PATH_ROOT)
            {
                struct path_data_dijkstra *node_data = (struct path_data_dijkstra*) graph[pointer].data;
                toreturn[counter] = pointer;
                counter--;
                pointer = node_data->source;
            }

            *steps = current_distance+1;

            free_graph_data(graph,graphSize);

            return toreturn;
        }

        // If not, find the other node
        current_node =  get_next_node(graph, graphSize);
    }
    
    // If we reach here it means the node is unreachable

    return NULL;
    
}

#endif