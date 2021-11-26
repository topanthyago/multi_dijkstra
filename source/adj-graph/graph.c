
#include "lista.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>


TIPO makeTuple(int _vertex, int _value)
{
	TIPO tupla;
	tupla.vertex = _vertex;
	
	tupla.weight = _value;
	return tupla;
}

ALGraph *  createGraph(int vertexes)
{   
    ALGraph * gp = (ALGraph * ) malloc(sizeof(ALGraph));
    gp->qtd_lista = vertexes;
    gp->lista = (Lista ** ) calloc(sizeof(Lista *), vertexes); 
    gp->flag = (int *) calloc(sizeof(int), vertexes);//flag
    for (int i=0; i<vertexes; i++)
    {
        gp->lista[i] = allocateList();
	//printf("%d:%p\n",i,  gp->lista[i]);
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
    //free(gp->flag);
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
			printf("w:%d-->v:%d\t",  aux->value.weight, aux->value.vertex);
			aux = aux->next;
		}
		printf("\n");
	}
}
