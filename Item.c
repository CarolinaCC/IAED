#include "Item.h"

// aloca e inicializa um novo item
Item newItem(long unsigned int chav, long int unidade){
    Item x = (Item)malloc(sizeof(struct produto));
    x->chave = chav;
    x->unidades = unidade;
return x; }


// apaga item
void deleteItem(Item a){
	free(a); 
}

// escreve item
void visitItem(Item a) {
    printf("%08lx",a->chave);
    printf(" %li\n",a->unidades);
}

// devolve > 0 se a (unidades de a) > (unidades de b)
// devolde < 0 se a < b
// devolde 0 se a = b
long int item_unidades_compara (Item a, Item b) {
	return (a->unidades - b->unidades);
}

// devolve > 0 se o a > b (em termos de chave)
// devolde < 0 se a < b
// devolde 0 se a = b
long unsigned int item_chave_compara (Item a, Item b) {
		return (a->chave - b->chave);
}
