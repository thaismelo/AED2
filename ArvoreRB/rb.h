#ifndef RB_H
#define RB_H

#include <stdlib.h>
#include <stdio.h>
typedef enum COR{PRETO,VERMELHO} CORES;
typedef struct no{
    int valor;
    CORES cor;
    struct no* esq;
    struct no* dir;
    struct no* pai;
}no;
typedef no * arvore;
no* criarNo(int valor);


void imprimir(arvore a);
void preOrder(arvore a);
void inicializar(arvore *nova);
void inserir(arvore *raizInicializada,int valor);
int cor(no *pivo);
int ehraiz(no *pivo);
int ehFilhoEsquerdo(no *pivo);
int ehFilhoDireito(no *pivo);
no* buscarTio(no *pivo);
no* buscarAvo(no *pivo);
void recolorir(no *pivo);
no* remover(no *raiz, int valor);
int maiorDescendente(no *raiz);
void rotacao_simples_direita(arvore *arvore,no* pivo);
void rotacao_simples_esquerda(arvore *arvore,no* pivo);
void rotacao_dupla_direita(arvore *arvore,no* pivo);
void rotacao_dupla_esquerda(arvore *arvore,no* pivo);
#endif 
