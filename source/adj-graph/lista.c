#include <stdio.h>
#include <stdlib.h>
#include "lista.h"




// inicia a lista
Lista * allocateList(){
	// para iniciar uma lista encadeada basta fazer o inicio apontar para NULL (nada)
	return (Lista *)calloc(sizeof(Lista), 1);
	
}

// inserir elemento no inicio da lista
int insertStartList(Lista *p_l, TIPO value){
	// aloca o novo no a ser iserido
	No *novo = (No *)malloc(sizeof(No));
	
	// verifica se a alocacao deu certo
	if (novo==NULL) //falta de memória
	{
		return 0;
	}

    // copia o value para o novo no
	novo->value = value;

	// faz o nextimo do novo no apontar para o inicio
	novo->next = p_l->inicio;

	// faz o inicio apontar para o novo
	p_l->inicio = novo;

	return 1;
}


// inseririr novo elemento no meio da lista
int insertMidList(No *p, TIPO value){
	// aloca o novo no a ser inserido
	No *novo = (No*) malloc(sizeof(No));
	if (novo==NULL)
	{
		//debug("Elemento nao alocado\n");
		return 0;

	}
		

    // faz a insercao utilizando o ponteiro p como referencia para o meio da lista
	novo->value = value;
	novo->next = p->next;
	p->next = novo;

	return 1;
}

// realiza uma busca sequencial na lista (busca binaria so pode ser usada em listas ordenadas)
No* searchInList(Lista *p_l, TIPO ch_busca, No** pred){
	// ponteiro para o predecessor
	*pred = NULL;

	// poteiro para o no corrente
	No* corrente = p_l->inicio;

	// anda na lista ate encontrar a do elemento ou o final da lista
	while ((corrente != NULL) && ( p_l->compar(&corrente->value, &ch_busca) == 0)) {
		*pred = corrente;
		corrente = corrente->next;
	}

    // se achou o elemento retorna o ponteiro para sua posicao
	if ((corrente != NULL) && (p_l->compar(&corrente->value, &ch_busca) == 0) )
	{
		//debug("Elemento encontrado\n");
		return corrente;
	}
	//debug("Elemento NÃO encontrado\n");
    // se não achou o elemento retorna NULL
	return NULL;
}


// realiza insercoes na lista de forma ordenada (se for usar essa funcao sempre use ela para manter a lista ordenada)
int insertInOrder(Lista * p_l, TIPO value){
	// ponteiro para o elemento a ser buscado
	No *q;

	// ponteiro para predecessor
	No *pre=NULL;

	// chama a funcao busca para ver se o elemnto a ser inserido ja existe na lista
	q = searchInList(p_l, value, &pre);

	if (q!=NULL) // elemento já existe na lista
	{
		//debug("Elemento ja existe:\n");
		return 0; // entao nao precisa ser inserido
	}
	if (pre==NULL) // lista vazia (inserção no inicio)
	{
		//debug("lista vazia\n");
		return insertStartList(p_l, value);
	}
	else //(inserção no meio)
		return insertMidList(pre, value);
}

// remove o elemento do inicio da lista
int removeStartList(Lista *p_l){
	// verifica se a lista esta vazia
	if(p_l == NULL) {
		return 0;
	}

	// se a lista nao esta vazia entao da para remover o elemento do inciio
	No* temp = p_l->inicio;
	p_l->inicio = temp->next;
	free(temp);

	return 1;
}

// remove um elemnto do meio da lista
int removeMidList(No* pred){

	// verifica se alista esta vazia
	if(pred == NULL) {
		return 0; // se estiver nao ha nada a ser removido
	}

	// cria um ponteiro temp servir como ancora e nao perder o link do no
	No* temp = pred->next;
	if(temp == NULL) // se temp for nulo que dizer que estamos no final da lista
        pred->next = NULL; // entao nextimo do ultimo tem que ser null
    else
	{
		pred->next= temp->next; // como nao é o ultimo entao nexti tem que ser temp-next
	}
        
	free(temp);
	return 1;
}

// remove um elemnto especifico da lista
int removeItemList(Lista *p_l, TIPO value_usu){
	No *q;
	No *pred=NULL;

	// rpocura pelo elemento a ser removido
	q = searchInList(p_l, value_usu, &pred);

	if (q==NULL) // elemento não existe na lista
		return 0;

	if (pred==NULL) // remover no inicio da lista
		return removeStartList(p_l);
	else
		// remover no meio da lista
		return removeMidList(pred);
}

// imrime o conteudo armazenado na lista
void  intList(Lista *p_l){
	No* temp = p_l->inicio;
	while(temp!=NULL){
		p_l->printer(&temp->value);
		temp=temp->next; //aponta para o próximo nó
	}
	printf("\n");
}


// remove todos os elementos da lista
void freeList(Lista *p_l){
	No* temp = p_l->inicio;
	if (p_l->free_memory != NULL)
		while(temp!=NULL){
			No* next = temp->next;
			p_l->free_memory(temp);
			temp=next;
		}
	free(p_l);
}


// remove o k-esimo elemento da lista
int removeKthElement(Lista *p_l, int k) {
	if(p_l == NULL)
		return 0;

    // conta o numero de elemtnos percorridos na lista
	int count=1;
	No* corrente = p_l->inicio;
	No* pred = NULL;
	while(corrente != NULL && count < k) {
		pred = corrente;
		corrente = corrente->next;

		count++;
	}

	// se nao encontrou o k-esimo elemento para
	if(count != k) {
		return 0;
	} else { // se achou o elemento o remove
		return removeMidList(pred);
	}
}
