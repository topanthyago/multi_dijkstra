#ifndef LISTA_INCLUDED
#define LISTA_INCLUDED



typedef struct tupla
{
	int vertex;
	int weight;
} TIPO;




typedef struct No{
	TIPO value;
	struct No *next;
} No;

typedef struct {
	No *inicio;
	int (*compar)(const void* a,const void* b); 
	void (*swap)(void* a,void* b); 
	void (*copy)(void* dest,void* origem);
	void (*printer)( const void* obj);
	void (*free_memory)( void* obj);
} Lista;






Lista * allocateList();
int insertStartList(Lista *p_l, TIPO value);
int insertMidList(No *p, TIPO value);
No* searchInList(Lista *p_l, TIPO ch_busca, No** pred);
int insertInOrder(Lista *p_l, TIPO value);
int removeStartList(Lista *p_l);
int removeMidList(No* pred);
int removeItemList(Lista *p_l, TIPO value_usu);
void prprintList(Lista *p_l);
void freeList(Lista *p_l);
int removeKthElement(Lista *p_l, int k);

#endif