#ifndef GRAPH_ADJACENT_LIST_INCLUDED
#define GRAPH_ADJACENT_LIST_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

typedef struct adjacent_list_graph
{
    Lista ** lista;
    char * flag; 
    int qtd_lista;
}ALGraph;

void cleanFlag(ALGraph * gp);

TIPO makeTuple(int _vertice, int _valor);

ALGraph *  createGraph(int vertices);
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