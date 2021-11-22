
#include "lista.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>


TIPO makeTuple(int _vertice, int _valor)
{
	TIPO tupla;
	tupla.vertice = _vertice;
	
	tupla.valor = _valor;
	return tupla;
}

ALGraph *  createGraph(int vertices)
{   
    ALGraph * gp = (ALGraph * ) malloc(sizeof(ALGraph));
    gp->qtd_lista = vertices;
    gp->lista = (Lista ** ) malloc(sizeof(Lista *) * vertices); 
    gp->flag = (char *) calloc(sizeof(char), vertices);//flag
    for (int i=0; i<vertices; i++)
    {
        gp->lista[i] = allocateList();
    }
    return gp;
}

void cleanFlag(ALGraph * gp)
{
    int i=0;
    if (!gp)
        return;
    for (i=0; i<(gp->qtd_lista); i++)
        gp->flag[i]=0;
}

void freeGraph(ALGraph * gp)
{
    for (int i=0; i<gp->qtd_lista; i++)
    {
        freeList(gp->lista[i]);
    }
    free(gp->flag);
    free(gp->lista);
    free(gp);
}

int insertEdgeInGraph(ALGraph * gp, int u, int v, int w)
{
    if (gp==NULL) //se diferente de null
        return -1;
    if (gp->lista == NULL)
        return -1;
    if (u>=gp->qtd_lista || v >= gp->qtd_lista)
        return -1;
    
    insertStartList((gp->lista[u]), makeTuple(v, w));
    insertStartList((gp->lista[v]), makeTuple(u, w));

    return 0;
}

void printGraph(ALGraph * gp)
{
	int i=0;
	No * aux;
	for (i=0; i<gp->qtd_lista; i++)
	{
		printf("\t%d|\t", i);
		aux = gp->lista[i]->inicio;
		while(aux!=NULL)
		{
			printf("w:%d-->v:%d\t",  aux->chave.valor, aux->chave.vertice);
			aux = aux->prox;
		}
		printf("\n");
	}
}
