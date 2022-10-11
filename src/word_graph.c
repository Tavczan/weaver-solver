#ifndef WORD_GRAPH_C
#define WORD_GRAPH_C

#include <stdlib.h>
#include <stdio.h>

#include "weaver.h"
#include "word_graph.h"

struct word_graph_node *make_graph_node()
{
    struct word_graph_node *new_node = malloc(sizeof(struct word_graph_node));
    new_node->links_length = 0;
    new_node->links = NULL;
    new_node->data = NULL; // Using uninitialized pointers reduces job opportunities
    return new_node;
}

void init_graph(struct word_graph_node *graph, int graphSize)
{
    for (int i = 0; i < graphSize; i++)
    {
        (graph+i)->links_length = 0;
        (graph+i)->links = NULL;
        (graph+i)->data = NULL;
    }
}

void add_graph_node_link(struct word_graph_node *a, struct word_graph_node *b, int a_number, int b_number)
{
    // Realloc node a storage and register node b
    a->links = realloc(a->links,sizeof(int)*((a->links_length)+1));
    a->links_length = (a->links_length)+1;
    a->links[(a->links_length)-1] = b_number;

    // Do the same for node b
    b->links = realloc(b->links,sizeof(int)*((b->links_length)+1));
    b->links_length = (b->links_length)+1;
    b->links[(b->links_length)-1] = a_number;

    return;
}

// Deprecated
void unlink_graph_node(struct word_graph_node *graph, int node_id)
{
    if (graph[node_id].links_length)
    {
        for (int i = 0; i < graph[node_id].links_length; i++)
        {
            struct word_graph_node linked_node = graph[graph[node_id].links[i]];
            int *buffer = malloc(sizeof(int)*linked_node.links_length);
            for (int j = 0; j < linked_node.links_length; j++)
            {
                if (linked_node.links[j] == node_id) continue;
                buffer[j] = linked_node.links[j];
            }
            linked_node.links_length--;
            linked_node.links = realloc(linked_node.links, sizeof(int)*linked_node.links_length);
            for (int j = 0; j < linked_node.links_length; j++)
            {
                if (linked_node.links[j] == node_id) continue;
                linked_node.links[j] = buffer[j];
            }
        }
        free(graph[node_id].links);
        graph[node_id].links = NULL;
        graph[node_id].links_length=0;
    }
    return;
}

int graph_node_links_to(struct word_graph_node *node, int node_id)
{
    if (node->links_length)
    {
        for (int i = 0; i < node->links_length; i++)
        {
            if (node->links[i] == node_id) return 1;
        }
    }
    return 0;
}

void create_graph_links(struct word_graph_node *graph, int graphSize, char (*words)[5])
{
    // For every graph node in existence
    for (int i = 0; i < graphSize; i++)
    {
        // Check every other node for being a valid link. Nodes previously checked are irrelevant due to links being made two-way
        for (int j = i; j < graphSize; j++)
        {
            // Edge cases
            if (i == j) continue;
            if (is_legal_weaver_move(words[i], words[j]))
            {
                add_graph_node_link(graph+i,graph+j,i,j);
            }
        }

    }
    return;
}

void delete_graph(struct word_graph_node *graph, int graphSize)
{
    for (int i = 0; i < graphSize; i++)
    {
        free(graph[i].links);
    }
    return;
}

void print_graph_structure(struct word_graph_node *graph, int graphSize, char (*words)[5])
{
    for (int i = 0; i < graphSize; i++)
    {
        printf("%s -> ", words[i]);
        for (int j = 0; j < graph[i].links_length; j++)
        {
            printf("%s ", words[graph[i].links[j]]);
        }
        printf("\n");
    }
    return;
}



#endif