#ifndef DIJKSTRA_SOLVER_C
#define DIJKSTRA_SOLVER_C

#include <stdlib.h>
#include <stdio.h>

#include "dijkstra_solver_helpers.h"

int get_next_node (struct word_graph_node *graph, int graphSize)
{
    // Start from a node that was not visited before
    int smallest_node = 0;
    int smallest_distance = DIJKSTRA_INFINITY;

    for (int i = 0; i < graphSize; i++)
    {
        if (!is_visited(graph, i))
        {
            smallest_node = i;
            smallest_distance = ((struct path_data_dijkstra*) graph[i].data)->distance;
            break;
        }
    }

    // Done? Now let's start looking

    for (int i = smallest_node; i < graphSize; i++)
    {
        if ( !is_visited(graph,i) && ((struct path_data_dijkstra*) graph[i].data)->distance < smallest_distance)
        {
            smallest_node = i;
            smallest_distance = ((struct path_data_dijkstra*) graph[i].data)->distance;
        }
    }

    return smallest_node;
}

void dijsktra_debug (struct word_graph_node *graph, int graphSize)
{
    for (int i = 0; i < graphSize; i++)
    {
        struct path_data_dijkstra *node = ((struct path_data_dijkstra*) graph[i].data);
        if (node->distance != DIJKSTRA_INFINITY)
            printf("Node %d Visited %d Distance %d Prev %d\n", i, node->visited, node->distance, node->source);
    }
}

int is_visited (struct word_graph_node *graph, int node)
{
    struct path_data_dijkstra *tested = ((struct path_data_dijkstra*) graph[node].data);
    return tested->visited;
}

int get_distance (struct word_graph_node *graph, int node)
{
    struct path_data_dijkstra *tested = ((struct path_data_dijkstra*) graph[node].data);
    return tested->distance;
}

void set_distance (struct word_graph_node *graph, int node, int new_distance)
{
    struct path_data_dijkstra *tested = ((struct path_data_dijkstra*) graph[node].data);
    tested->distance = new_distance;
    return;
}

void set_source (struct word_graph_node *graph, int node, int new_source)
{
    struct path_data_dijkstra *tested = ((struct path_data_dijkstra*) graph[node].data);
    tested->source = new_source;
    return;
}

void mark_visited (struct word_graph_node *graph, int node)
{
    struct path_data_dijkstra *tested = ((struct path_data_dijkstra*) graph[node].data);
    tested->visited = 1;
}

int *get_unvisited_neighbours (struct word_graph_node *graph, int node, int *count)
{
    int *unvisited = NULL;
    int unvisited_count = 0;

    for (int j = 0; j < graph[node].links_length; j++)
    {
        if (((struct path_data_dijkstra*)graph[graph[node].links[j]].data)->visited == 0)
        {
            unvisited_count++;
            unvisited = realloc(unvisited, sizeof(int)*unvisited_count);
            unvisited[unvisited_count-1] = graph[node].links[j];
        }
    }

    *count = unvisited_count;
    return unvisited;
}

void free_graph_data (struct word_graph_node *graph, int graphSize)
{
    for (int i = 0; i < graphSize; i++)
    {
        struct path_data_dijkstra *current = ((struct path_data_dijkstra*) graph[i].data);
        free(current);
        graph[i].data = NULL;
    }
}

#endif