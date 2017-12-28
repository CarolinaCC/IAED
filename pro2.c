
// *****************************************
//          Carolina Carreira
//
//               87641
//
//               IAED    
// *****************************************
//        2016/2017 2o projeto

# include <stdio.h>
# include <stdlib.h>
# include "ST.h"

// HEADERS

link comando_a (link head);
void comando_l (link head);
void comando_m (link head);
link comando_r (link head);


// CONSTANTES

// varivel que vai contando os produtos em stock
long unsigned int contador;

// variavel apontador que guarda o produto com mais unidades
Item static mais_unidades = NULL;



// MAIN
int main () {
    char comando;
    link head;
    STinit(&head);
    while (1) {
        comando = getchar();
        switch (comando) {
        case 'a':
            head = comando_a (head);
            getchar();
            break;
        case 'l':
            comando_l (head);
            getchar();
            break;
        case 'm':
            comando_m (head);
            getchar();
            break;
        case 'r':
            head = comando_r (head);
            getchar ();
            break;
        case 'x':
            STfree(&head);
            printf("%li\n",contador );
            return 0;

        default:
            printf("ERRO: Comando desconhecido\n");
            getchar();
            break;
        }
    }
    return 0;
}

// Adiciona um novo produto
// ou
// Atualiza o numeros de unidades de um produto (retira ou adiciona)
link comando_a (link head) {

    getchar ();
    unsigned long int chave_buffer;
    long int unidades_buffer, aux;
    Item novo;
    scanf("%lx %li", &chave_buffer,&unidades_buffer );

    // verifica se essa chave ja foi inserida
    if ( (novo = STsearch(head, chave_buffer)) != NULL) {

        // flag negativo
        int negativo;

        aux = novo->unidades;
        aux += unidades_buffer;

        // flag negativo vai ficar true se as unidades inseridas foram negativas
        negativo = (unidades_buffer < 0 ? 1 : 0);

        // garante que nao fico com unidades negativas
        if (aux<0)
            aux = 0;
        novo->unidades = aux;

        // se o novo numero inserido for mais que zero
        if (mais_unidades != NULL && !negativo ) {
            // verifica se e o com mais unidades
            // devolve <0 se o primeiro for menor que o segundo
            // >0 se o primeiro for maior, e 0 se iguais
            if (item_unidades_compara(novo, mais_unidades)>0)
                // se as unidades de novo foram maior do que de mais_unidades
                mais_unidades = novo;

            // se as unidades de novo e mais_unidades foram iguais
            else if (item_unidades_compara(novo, mais_unidades) == 0)

                // se a chave de novo forem menores que de mais_unidades
                if (item_chave_compara(novo, mais_unidades) < 0)
                    mais_unidades = novo;
        }

        // o numero inserido tiver unidades negativas
        else if (mais_unidades != NULL && negativo)
            mais_unidades = NULL;

        return head;
    }

    novo = newItem(chave_buffer, unidades_buffer);
    STinsert(&head,novo);
    contador ++;

    // se o novo numero inserido for mais que zero
    if (mais_unidades != NULL) {
        // verifica se e o com mais unidades
        // devolve <0 se o primeiro for menor que o segundo
        if (item_unidades_compara(novo, mais_unidades)>0)
            mais_unidades = novo;
        else if (item_unidades_compara(novo, mais_unidades) == 0)
            if (item_chave_compara(novo, mais_unidades) < 0)
                mais_unidades = novo;
    }

    return head;
}


// Lista todos os produtos por ordem lexical
void comando_l (link head) {
    STsort(head,visitItem);
}


// Escreve o produto com o maior numero de unidades em stock.
void comando_m (link head) {
    if(head == NULL)
        return;

    // se o mais_unidades e valido
    if (mais_unidades != NULL) {
        visitItem(mais_unidades);
        return;
    }

    Item novo_maximo;
    // procura novo valor maximo
    novo_maximo = STmax_unidades(head);

    if ((mais_unidades == NULL) && (novo_maximo != NULL) ) {
        // atualiza o mais_unidades com o novo maximo detetado
        mais_unidades = novo_maximo;
        visitItem(mais_unidades);
        return;
    }
}



// Remove o produto com o codigo/chave dada
link comando_r (link head) {
    getchar();
    long unsigned int chave_buffer;
    Item aux, aux_procura;
    int flag;

    // le a chave do produto a apagar
    scanf("%lx", &chave_buffer);
    aux = newItem(chave_buffer,0);

    // verifica se o item a apagar tem a msm chave que o mais_unidades
    if( (mais_unidades != NULL ) && (item_chave_compara(aux, mais_unidades) == 0))
        mais_unidades = NULL;

    aux_procura = STsearch(head, chave_buffer);

    // flag fica true se o aux_procura for valido
    flag = ((aux_procura != NULL) ? 1: 0);

    deleteItem(aux);
    STdelete(&head,chave_buffer);

    // ver o aux_procura e valido e so ai decrementar o contador
    if (flag) {
        if (contador == 0);
        else contador--;
    }
    return head;
}









