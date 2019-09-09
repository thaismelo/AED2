#ifndef AVL_H
#define AVL_H

#include <stdlib.h>
#include <stdio.h>

typedef struct no{
    int valor;
    int fb;
    struct no* esq;
    struct no* dir;
}no;

no* criar_no(int valor);
void imprimir(no *raiz);
void preOrder(no *raiz);
void inOrder(no *raiz);
void posOrder(no *raiz);
void limparArvore(no *raiz);
no* inserir(no *raiz,int valor,int *cresceu);
no* remover(no *raiz, int valor, int *diminuiu);
no* rotacionar(no *pivo);
int maiorDescendente(no *raiz);
no* rotacao_simples_direita(no *p);
no* rotacao_simples_esquerda(no *p);
no* rotacao_dupla_direita(no *p);
no* rotacao_dupla_esquerda(no *p);
#endif 
