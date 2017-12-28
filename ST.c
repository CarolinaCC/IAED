#include "ST.h"

// em ST.h
// adiciona um novo elemento
link NEW(Item item, link l, link r) {
    link x = (link)malloc(sizeof(struct STnode));
    x->item = item;
    x->l = l;
    x->r = r;
    x->height=1;
    return x;
}

// Retorna a altura de um deteminado node
int height(link h) {
    if (h == NULL) return 0;
    return h->height;
}

// Atualiza a altura de um determino link
void update_height(link h){
    int height_left = height(h->l);
    int height_right = height(h->r);
    h->height = height_left >
                height_right ?  height_left + 1 :
                height_right + 1;
}

// Rotacao para a esquerda
link rotL(link h){
    link x = h->r;
    h->r = x->l;
    x->l = h;
    update_height(h);
    update_height(x);
    return x;
}

// Rotacao direita
link rotR(link h){
    link x = h->l;
    h->l = x->r;
    x->r = h;
    update_height(h);
    update_height(x);
    return x;
}

// rotacao dupla esquerda direita
link rotLR(link h) 
{
    if (h==NULL) return h;
    h->l=rotL(h->l);
    return rotR(h);
}

//rotacao dupla direita esquerda
link rotRL(link h){
    if (h==NULL) return h;
    h->r=rotR(h->r);
    return rotL(h);
}

// Balance factor
int Balance(link h) {
    if(h == NULL) return 0;

    return height(h->l)-height(h->r);
}


// Equilibra a arvore
link AVLbalance(link h) {
    int balanceFactor;
    if (h==NULL) return h;
    balanceFactor= Balance(h);

    // se esta desiquilibrada vai fazer rotacoes para equilibrar
    if(balanceFactor>1) {
        if (Balance(h->l)>=0) h=rotR(h);
        else                  h=rotLR(h);
    }

    // se esta desiquilibrada
    else if(balanceFactor<-1) {
        if (Balance(h->r)<=0) h = rotL(h);
        else                  h = rotRL(h);
    } 

    // esta equilibrada
    else
        update_height(h);
    return h;
}

// inicializa o valor 
void STinit(link*head) {
    *head = NULL;
}


// insere um novo item recursivamente na arvore
// de forma ordenada
link insertR(link h, Item item) {
    if (h == NULL)
        return NEW(item, NULL, NULL);
    if (less(key(item), key(h->item)))
        h->l = insertR(h->l, item);
    else
        h->r = insertR(h->r, item);
    h=AVLbalance(h);
    return h;
}
// em ST.h
// insere um item na arvore
void STinsert(link*head, Item item) {
    *head = insertR(*head, item);
}

// Procura recursiva na arvore
Item searchR(link h, Key v) {
    if (h == NULL)
        return NULL;
    if (eq(v, key(h->item)))
        return h->item;
    if (less(v, key(h->item)))
        return searchR(h->l, v);
    else
        return searchR(h->r, v);
}

// em ST.h
// Procura arvore um determinado key (chave)
Item STsearch(link head, Key v) {
    return searchR(head, v);
}

// encontra o maximo
link max(link h) {
    if (h==NULL || h->r==NULL) return h;
    else return max(h->r);
}

// funcao recursiva que apaga um key da arvore
// e a volta a equilibrar
link deleteR(link h, Key k){
    if (h==NULL) return h;
    else if (less(k, key(h->item))) h->l=deleteR(h->l,k);
    else if (less(key(h->item), k)) h->r=deleteR(h->r,k) ;
    else {
        if (h->l !=NULL && h->r !=NULL) {
            link aux=max(h->l);{
                Item x;
                x=h->item;
                h->item=aux->item;
                aux->item=x;
            }
            h->l= deleteR(h->l, key(aux->item));
        }
        else { 
            link aux=h;
            if ( h->l == NULL && h->r == NULL ) h=NULL;
            else if (h->l==NULL) h=h->r;
            else h=h->l;
            deleteItem(aux->item);
            free(aux);
        }
    }
    // volta a equilibrar a arvore
    h=AVLbalance(h);
    return h;
}

// em ST.h
// apaga o elemento key da arvore
void STdelete(link*head, Key k) {
    *head = deleteR(*head, k);
}

// conta recursivamente o numero de elementos da arvores
int count(link h) {
    if (h==NULL) return 0;
    else return count(h->r)+count(h->l)+1;
}


// em ST.h
// Retorna o numero de elemntos da arvore
int STcount(link head) {
    return count(head);
}


// funcao recursiva (traverse) que imprime de forma crescente
// os items da arvore
void sortR(link h, void (*visit)(Item)){
    if (h == NULL)
        return;
    sortR(h->l, visit);
    visit(h->item);
    sortR(h->r, visit);
}

// em ST.h
// escreve de forma crescente os items
void STsort(link head, void (*visit)(Item)){
    sortR(head, visit);
}

// funcao recursiva que apaga a arvore comecando debaixo
// para cima
link freeR(link h){
    if (h==NULL)
        return h;
    h->l=freeR(h->l);
    h->r=freeR(h->r);
    return deleteR(h,key(h->item));
}

// em ST.h
// apaga toda a arvore
void STfree(link*head){
    *head=freeR(*head);
}

// auxiliar de comparacoes para findmax
Item max_aux(Item a, Item b){
	if(a->unidades > b->unidades)
    	return a;
    if ((a->unidades == b->unidades) && (a->chave < b->chave))
    	return a;
    else return b;
}

// Procura um item com o unidades maior
Item findmax(link root) {
	Item maximo = root->item;
	if(root->l != NULL)
		maximo = max_aux(maximo, findmax(root->l));
	if(root->r != NULL)
		maximo = max_aux(maximo, findmax(root->r));
    return maximo;
}

// em ST.h
// Encontra o elemento com o maximo numero de unidades
// Devolve esse elemento
Item STmax_unidades(link root) {
	return findmax(root);
}


