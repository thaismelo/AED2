#include <stdlib.h>
#include <stdio.h>
#include "rb.h"

void imprimir(no *raiz){
    printf("%d [%d] ", raiz->valor, raiz->cor);
}


void preOrder(no *raiz) {
	printf("(");
	if(raiz != NULL) {
		imprimir(raiz);
		pre_order(raiz->esq);
		pre_order(raiz->dir);
	}
	printf(")");
}

void posOrder(no *raiz) {
	printf("(");
	if(raiz != NULL) {
		pos_order(raiz->esq);
		pos_order(raiz->dir);
		imprimir(raiz);
	}
	printf(")");
}

void inOrder(no *raiz) {
	printf("(");
	if(raiz != NULL) {
		in_order(raiz->esq);
		imprimir(raiz);
		in_order(raiz->dir);
	}
	printf(")");
}

int cor(no *raiz){
    if(raiz->cor==PRETO){
        return 0;
    }else{
        return 1;
    }
}

int ehRaiz(no *raiz){
    if(raiz->pai==NULL){
        return 1;
    }else{
        return 0;
    }
}

int ehEsquerdo(no *raiz){
    if(raiz->pai->esq==raiz){
        return 1;
    }else{
        return 0;
    }
}

int ehDireito(no *raiz){
    if(raiz==raiz->pai->dir){
        return 1;
    }else{
        return 0;
    }
}

no * avo(no *raiz){
    if(raiz->pai!=NULL){
        return raiz->pai->pai;    
    }else{
        return NULL;
    }   
}

no * tio(no *raiz){
    if(ehEsquerdo(raiz->pai)){
        return avo(raiz)->dir;
    }else{
        return avo(raiz)->esq;
    }
}

no * recolorirRaiz(no *raiz){
    if(raiz->cor == VERMELHA){
        raiz->cor == PRETA;
    }
    return raiz;
}

no * recolorir(no *raiz){
    no * avo = avo(raiz);
    if(ehRaiz(avo)){
         avo->esq->cor= PRETA;
         avo->dir->cor=PRETA;
    }else{
        avo->cor=VERMELHA;
        avo->esq->cor= PRETA;
        avo->dir->cor=PRETA;
    }
    return raiz;    
}

no * rotacao_simples_direita(no *raiz){
    no *p, *u, *t2;
    
    //declaracao
    p = raiz->pai->pai;
    u = raiz->pai;
    t2 = raiz->pai->dir;
    //atribuicao
    p->esq=t2;
    u->dir = p;
    
    u->cor=PRETO;
    u->dir = VERMELHO;
    u->esq = VERMELHO;
    
    return u;
    
}

no * rotacao_simples_esquerda(no *raiz){
    no *p, *u, *t2;
    
    //declaracao
    p = raiz->pai->pai;
    u = raiz->pai;
    t2 = raiz->pai->esq;
    //atribuicao
    p->dir=t2;
    u->esq = p;
    
    u->cor=PRETO;
    u->dir = VERMELHO;
    u->esq = VERMELHO;
    
    return u;
    
}

no * rotacao_dupla_esquerda(no *raiz){
    no *p, *u, *v, *t2,*t3;
    
    //declaracao
    p = raiz->pai->pai;
    u = raiz->pai;
    v = raiz->pai->esq;
    t2 = v->esq;
    t3 = v->dir;

    //1 rotacao
    u->esq = t3;
    v->dir = u;
    p->dir = v;

    //2 rotacao
    
    p->dir = t2;
    v->esq= p;
    
    v->cor=PRETO;
    v->dir = VERMELHO;
    v->esq = VERMELHO;
    
    return v;
    
}
no * rotacao_dupla_direita(no *raiz){
    no *p, *u, *v, *t2,*t3;
    
    //declaracao
    p = raiz->pai->pai;
    u = raiz->pai;
    v = raiz->pai->dir;
    t2 = v->esq;
    t3 = v->dir;

    //1 rotacao
    u->dir = t2;
    v->esq = u;
    p->esq = v;

    //2 rotacao
    
    p->esq = t3;
    v->dir= p;
    
    v->cor=PRETO;
    v->dir = VERMELHO;
    v->esq = VERMELHO;
    
    return v;
    
}


