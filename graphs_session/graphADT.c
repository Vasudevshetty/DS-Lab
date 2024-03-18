/*Develop a menu driven program to implement Graph traversal techniques*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Graph
{
    int **adjList;
    int vertex;
} Graph;

Graph *createGraph(int vertex)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (!graph)
    {
        printf("Memroy allocation failed.\n");
        exit(1);
    }
    graph->vertex = vertex;
    graph->adjList = (int **)malloc(sizeof(int *) * graph->vertex);

    if(!graph->adjList){
        free(graph);
        printf("Memroy allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < graph->vertex; i++)
        graph->adjList[i] = NULL;

    return graph;
}

