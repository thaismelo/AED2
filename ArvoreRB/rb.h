#ifndef RB_H
#define RB_H

#include <stdlib.h>
#include <stdio.h>
typedef enum CORES{PRETO,VERMELHO,DUPLO_PRETO} COR;
typedef struct no{
    int valor;
    COR cor;
    struct no* esq;
    struct no* dir;
    struct no* pai;
}no;
typedef no * arvore;
no* criarNo(int valor);
void imprimir(arvore a);
void preOrder(arvore a);
void inicializar(arvore *nova);

COR cor(no *raiz);
int ehraiz(no *pivo);
int ehFilhoEsquerdo(no *pivo);
int ehFilhoDireito(no *pivo);
no* buscarTio(no *pivo);
no* buscarAvo(no *pivo);
no* buscarIrmao(no *pivo);
void recolorir(no *pivo);

void inserir(arvore *raizInicializada,int valor);
void ajustar(arvore *arvore, no *novo);
void rotacao_simples_direita(arvore *arvore,no* pivo);
void rotacao_simples_esquerda(arvore *arvore,no* pivo);
void rotacao_dupla_direita(arvore *arvore,no* pivo);
void rotacao_dupla_esquerda(arvore *arvore,no* pivo);

void remover (arvore *arvore, int valor);
int maiorDescendente(no *raiz);
void reajustar(arvore *arvore, no *pivo);
void rotacao_caso2_esq(arvore *arvore,no *pivo);
void rotacao_caso2_dir(arvore *arvore,no *pivo);
void rotacao_caso3(arvore *arvore,no *pivo);
void rotacao_caso4(arvore *arvore,no *pivo);
void rotacao_caso5_esq(arvore *arvore, no *pivo);
void rotacao_caso5_dir(arvore *arvore, no *pivo);
void rotacao_caso6_esq(arvore *arvore, no *pivo);
void rotacao_caso6_dir(arvore *arvore, no *pivo);
#endif 
