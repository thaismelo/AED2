#ifndef RB_H
#define RB_H

#include <stdlib.h>
#include <stdio.h>
enum COR{PRETO,VERMELHO};
typedef struct no{
    int valor;
    COR cor;
    struct no* esq;
    struct no* dir;
    struct no* pai;
}no;

void imprimir(no *raiz);
void preOrder(no *raiz);
void inOrder(no *raiz);
void posOrder(no *raiz);

no* inserir(no *raiz,int valor,no *pai);
int cor(no *raiz);
int ehraiz(no *raiz);
int ehEsquerdo(no *raiz);
int ehDireito(no *raiz);
no* tio(no *raiz);
no* avo(no *raiz);
no* recolorirRaiz(no *raiz);
no* recolorir(no *raiz);

no* remover(no *raiz, int valor,no *pai);

no* rotacionar(no *pivo);
int maiorDescendente(no *raiz);
no* rotacao_simples_direita(no *p);
no* rotacao_simples_esquerda(no *p);
no* rotacao_dupla_direita(no *p);
no* rotacao_dupla_esquerda(no *p);
#endif 
