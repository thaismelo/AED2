#ifndef FUNCOESBST_H_INCLUDED
#define FUNCOESBST_H_INCLUDED

#include <stdlib.h>

typedef struct no{
    int valor;
    struct no* esq;
    struct no* dir;
}no;

no* criar_no(int valor);
void imprimir(no *raiz);
void preOrder(no *raiz);
void inOrder(no *raiz);
void posOrder(no *raiz);
void limparArvore(no *raiz);
no* inserir(no *raiz,int valor);
no* remover(no *raiz,int valor);
int maiorDescendente(no *raiz);
int menorDescendente(no *raiz);
int altura(no *raiz);
int paiDoElemento(no *raiz, int valor);
int sucessorDoElemento(no *raiz, int valor);
int antecessorDoElemento(no *raiz, int valor);
#endif // FUNCOESBST_H_INCLUDED
