#ifndef _ITEM_
#define _ITEM_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define key(a) (a != NULL ? a->chave : 0)
#define less(a,b) (a<b)
#define more(a,b) (a>b)
#define eq(a,b) (a==b)

typedef unsigned long int Key;
typedef long int Uni;

typedef struct produto {
	unsigned long int chave;
	long int unidades;
} *Item;


Item newItem(long unsigned int chav, long int uni);
void deleteItem(Item a);
void visitItem(Item a);
long int item_unidades_compara (Item a, Item b) ;
long unsigned int item_chave_compara (Item a, Item b);

#endif
