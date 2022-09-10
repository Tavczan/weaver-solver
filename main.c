#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./datastructures/word_list.c"
#include "./datastructures/word_list.h"

#include "./datastructures/word_graph.c"
#include "./datastructures/word_graph.h"

#include "./solver/weaver_solver.c"
#include "./solver/weaver_solver.h"

int main(int argc, char **argv)
{

    /*
        Preparation for cracking
    */

    // Pull 4-letter words from the file and organize them in memory

    printf("Pick the word set to use.\n1 - Full alphanumeric set\n2 - Scrabble and weaver approved set\nEnter a number: ");
    int num;
    

    struct word_element *newlist = NULL;
    while (!newlist)
    {
        scanf("%d", &num);
        if (num == 1)
        {
            newlist = make_list_from_file("words_alpha.txt");
        }
        else if (num == 2)
        {
            newlist = make_list_from_file("scrabble_words.txt");
        }
        if (!newlist)
        {
            printf("Enter again - 1 or 2: ");
        }
    }
    

    int tableLength = word_list_length(newlist);

    char(*words)[5] = tablearize_word_list(newlist);

    // This stuff is no longer needed
    newlist = free_word_list(newlist);

    // Now there are two variables
    // int tableLength holding the amount of words
    // char (*words)[5] holding an array of 4-letter strings

    /*
        Preparation of the graph structure
    */

    struct word_graph_node graph[tableLength];
    init_graph(graph, tableLength);
    create_graph_links(graph, tableLength, words);

    // Now graph explains how words link

    
    int loop = 1;

    // Everything is ready to play, main loop begin

    while (loop)
    {
        // Stuff that needs setting inside the loop, also asking user for words
        
        char word_1[5];
        char word_2[5];
        printf("Please provide a 4-letter starting word: \n");
        scanf("%s", word_1);
        printf("Please provide a 4-letter destination word: \n");
        scanf("%s", word_2);

        printf("Looking for path between %s and %s...\n", word_1, word_2);

        int node_1 = get_node_id_by_string(words, tableLength, word_1);
        int node_2 = get_node_id_by_string(words, tableLength, word_2);

        if (node_1 == -1)
        {
            printf("Starting word not in dictionary!");
        }
        else if (node_2 == -1)
        {
            printf("Destination word not in dictionary!");
        }
        else
        {
            // We can play, hooray
            int steps = 0;
            int *path = solve_dijkstra(graph, tableLength, words, node_1, node_2, &steps);
            if (path)
            {
                // Display the solution
                printf("The solution is:\n");
                for (int i = 0; i < steps; i++)
                {
                    printf("%s\n", words[path[i]]);
                }
                free(path);

                // It may pick a word that is not allowed due to the sheer size of its dictionary, handle removal of such cases
                // didn't work fully, too lazy to fix. Turns out there's a list of scrabble accepted words out there
                /*
                printf("Are all the words accepted? y/n: ");
                char response;
                scanf("%s", &response);

                if (response == 'n')
                {
                    printf("Please type the word that was disallowed. Type a nonexisting word (like aaaa) if it was an accident: ");
                    char badword[5];
                    scanf("%s",badword);
                    int badnode = get_node_id_by_string(words, tableLength, badword);
                    if (badnode == -1)
                    {
                        printf("Aborting removal...\n");
                    }
                    else
                    {
                        unlink_graph_node(graph,badnode);
                    }
                }
                */
            }
            else
            {
                // My prof once said that freeing null pointers is unhealthy
                printf("There is no solution to that!");
            }
        }

        printf("Play again? Enter y to continue...\n");
        char response[10];
        scanf("%s",response);
        if (!(response[0]=='y' || response[0] == 'Y'))
        {
            loop = 0;
        }
    }
    


    /*
        Cleanup
    */
    delete_graph(graph, tableLength);
    free(words);
    return 0;
}