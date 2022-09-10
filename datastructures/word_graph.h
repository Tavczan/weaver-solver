#ifndef WORD_GRAPH_H
#define WORD_GRAPH_H

struct word_graph_node {
    // Graph structure information
    int links_length;
    int *links;

    // Data
    void *data;
};

// Graphs should be of type
// struct **word_graph_node
// with a same-length array storing words that it can be used on for the purpose of weaver solving 

/* Safely makes a new struct of word_graph_node type */
struct word_graph_node *make_graph_node();

/* Safely initializes a new graph */
void init_graph(struct word_graph_node *graph, int graphSize);

/* Adds a two-way link between two nodes */
void add_graph_node_link(struct word_graph_node *a, struct word_graph_node *b, int a_number, int b_number);

/* Checks if a connection exists between two nodes */
int graph_node_links_to(struct word_graph_node *node, int node_id);

/* Creates graph connections based on a word list */
void create_graph_links(struct word_graph_node *graph, int graphSize, char (*words)[5]);

/* Frees a graph structure */
void delete_graph(struct word_graph_node *graph, int graphSize);

/* Print out the graph structure in the format NODE -> NODES LINKED TO */
void print_graph_structure(struct word_graph_node *graph, int graphSize, char (*words)[5]);

#endif