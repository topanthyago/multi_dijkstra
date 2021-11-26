#ifndef GRAPH_ADJACENT_LIST_INCLUDED
#define GRAPH_ADJACENT_LIST_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

typedef struct adjacent_list_graph
{
    Lista ** lista;
    int * flag; 
    int qtd_lista; 
}ALGraph;

void cleanFlag(ALGraph * gp);

TIPO makeTuple(int _vertex, int _value);

ALGraph *  createGraph(int vertexes);
void freeGraph(ALGraph * gp);
/**
 * @brief 
 * 
 * @param gp graph 
 * @param u edge
 * @param v edge
 * @param w weight
 * @return int 
 */
int insertEdgeInGraph(ALGraph * gp, int u, int v, int w);
void printGraph(ALGraph * gp);


#endif