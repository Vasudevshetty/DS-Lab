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

    if (!graph->adjList)
    {
        free(graph);
        printf("Memroy allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < graph->vertex; i++)
        graph->adjList[i] = NULL;

    return graph;
}

#define list graph->adjList

void addEdge(Graph *graph, int src, int dest)
{
    if (list[src] == NULL)
    {
        list[src] = (int *)malloc(sizeof(int));
        list[src][0] = dest;
        list[src][1] = -1;
    }
    else
    {
        int size = 0;
        while (list[src][size] != -1)
            size++;

        int *newList = (int *)malloc(sizeof(int) * (size + 2));
        if (!newList)
        {
            printf("Memroy allocation failed.\n");
            exit(1);
        }
        for (int i = 0; i < size; i++)
            newList[i] = list[src][i];

        newList[size] = dest;
        newList[size + 1] = -1;

        free(list[src]);
        list[src] = newList;
    }
}

void printGraph(const Graph *graph)
{
    for (int i = 0; i < graph->vertex; i++)
    {
        printf("Vertex %d : ", i);
        int j = 0;
        while (list[i][j] != -1)
            printf("%d ", list[i][j++]);
        printf("\n");
    }
    printf("\n");
}

void freeGraph(Graph *graph)
{
    for (int i = 0; i < graph->vertex; i++)
        free(list[i]);
    free(list);
    free(graph);
}

int main()
{
    int vertex = 4;
    Graph *graph = createGraph(vertex);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);
    addEdge(graph, 4, 2);

    printGraph(graph);
    return 0;
}