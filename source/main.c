#include <stdio.h>
#include "adj-graph/graph.h"
#include <stdlib.h>
#include "debug.h"
#include "adj-graph/lista.h"
#include <string.h>
#include <limits.h>

void preparaMultiDijkstra(ALGraph ** elevators, int qtd_elevator, int start)
{
	for (int i=0; i<qtd_elevator; i++)
	{
		elevators[i]->flag[start] = 0;
		for (int j=0; j<elevators[i]->qtd_lista; j++)
		{
			elevators[i]->flag[j] = INT_MAX;
		}
	}
}

int visited(ALGraph * graph, int vertex)
{
	return graph->flag[vertex];
}
void markVisited(ALGraph * graph, int vertex)
{
	graph->flag[vertex] = 1;
}

int multiDijkstra(ALGraph ** elevators, int  qtd_elevator, int currentEvelator, int currentFloor, int distanceToHere, int weightToChangeElevator)
{
	
	if (distanceToHere < elevators[0]->flag[currentFloor])
	{
		elevators[0]->flag[currentFloor] = distanceToHere;
	}
	else{
		return 0;
	}
	
	No * neighbor;
	int distanceToNextNeighbor;
	for (int i=0; i<qtd_elevator; i++)//para cada elevador
	{
		//printf("%p\n", elevators[i]->lista);
		if (elevators[i]->lista[currentFloor]->inicio != NULL)
		{
			for (neighbor = elevators[i]->lista[currentFloor]->inicio ; neighbor!=NULL; neighbor=neighbor->next)//para cada vizinho 
			{
				//printf("a");
				distanceToNextNeighbor = distanceToHere + neighbor->value.weight + ((currentEvelator==i || currentEvelator<0 )? 0 : weightToChangeElevator);
				multiDijkstra(elevators, qtd_elevator, i, neighbor->value.vertex, distanceToNextNeighbor, weightToChangeElevator);
			}
		}
		
	}
	
	return 0;
}


int main()
{
	int qtd_elevator, qtd_floor, mean_time_change_elevator;
	scanf("%d %d", &qtd_elevator, &qtd_floor);
	scanf("%d", &mean_time_change_elevator);

	int i=0, j;
	int floor_aux, floor_aux_last;
	int returned;
	
	ALGraph ** elevators = malloc(sizeof(ALGraph*) * qtd_elevator);
	int * elevators_flag = calloc(sizeof(int), qtd_elevator);
	
	for (i=0; i<qtd_elevator; i++)
	{
		elevators[i] = createGraph(qtd_floor);
		if (elevators[i] == NULL)
			printf("not aloccate graph n:\t%d\n", i);
	}
	
	int mean_time_change_floor, qtd_floor_allowed, weigth_edge;
	for (i=0; scanf("%d %d", &mean_time_change_floor, &qtd_floor_allowed) >0; i++)
	{
		//debugf(printf("time_change:\t%d\t\tqtd_allowed:\t%d\n\n", mean_time_change_floor, qtd_floor_allowed));
		if (qtd_floor_allowed>0)
			scanf("%d", &floor_aux_last);
		
		for (j=1; j<qtd_floor_allowed; j++)
		{
			scanf("%d", &floor_aux);
			//graph, edge, edge, weight

			weigth_edge = abs(floor_aux - floor_aux_last)*mean_time_change_floor;
			returned = insertEdgeInGraph(elevators[i], floor_aux_last, floor_aux,weigth_edge) ;
			
			debugf(printf("%s", returned == 0? "INSERTED" : "NOT INSERTED"));
			debugf(printf("\tU: %d\tV: %d\tW: %d\t\tinto:\t%d\n\n", floor_aux_last, floor_aux,weigth_edge ,i ));
			
			floor_aux_last = floor_aux;
			//printf(" %d", aux);
		}
		
		//debugf(printGraph(elevators[i]));
		//debugf(printf("\n"));
	}
	
	
	preparaMultiDijkstra(elevators, qtd_elevator, 0);
	multiDijkstra(elevators, qtd_elevator, -1, 0, 0, mean_time_change_elevator);
	
	for (i=1; i< qtd_floor; i++)
	{
		if (elevators[0]->flag[i] !=INT_MAX)
		{
			printf("%d\n",elevators[0]->flag[i]);
		}
		else{
			printf("checkout\n");
		}
	}
	
	for (i=0; i<qtd_elevator; i++)
	{
		freeGraph(elevators[i]);
	}
	
}

