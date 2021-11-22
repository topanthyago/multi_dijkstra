#include <stdio.h>
#include "adj-graph/graph.h"
#include <stdlib.h>
#include "debug.h"
#include <string.h>
/*

protocolo de carteira do bingo: 
*/

int main()
{
	int qtd_elevator, qtd_floor, mean_time_change_elevator;
	scanf("%d %d", &qtd_elevator, &qtd_floor);
	scanf("%d", &mean_time_change_elevator);


	//printf("%d %d\n", elevator, floor);
	//printf("%d\n", mean_time_change_elevator);

	int i=0, j;
	int floor_aux, floor_aux_last;
	int returned;
	
	ALGraph ** elevators = malloc(sizeof(ALGraph*) * qtd_elevator);
	size_t * elevators_flag = calloc(sizeof(size_t), qtd_elevator);
	//create a one graph with qtd_elevator vertez, and qtd_floor vertex.
	for (i=0; i<qtd_elevator; i++)
	{
		elevators[i] = createGraph(qtd_floor);
		if (elevators[i] == NULL)
			debugf(printf("not aloccate graph n:\t%d\n", i));
	}


	int mean_time_change_floor, qtd_floor_allowed, weigth_edge;
	for (i=0; scanf("%d %d", &mean_time_change_floor, &qtd_floor_allowed) >0; i++)
	{
		debugf(printf("time_change:\t%d\t\tqtd_allowed:\t%d\n\n", mean_time_change_floor, qtd_floor_allowed));
		if (qtd_floor_allowed) scanf("%d", &floor_aux_last);
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
		debugf(printGraph(elevators[i]));
		debugf(printf("\n"));
	}







	for (i=0; i<qtd_elevator-1; i++)
	{
		memset(elevators_flag, 0, sizeof(elevators_flag)*qtd_elevator);
	}








	for (i=0; i<qtd_elevator; i++)
	{
		free(elevators[i]);
	}

	

	free(elevators);
	free(elevators_flag);

}