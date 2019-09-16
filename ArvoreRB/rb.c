#include <stdlib.h>
#include <stdio.h>
#include "rb.h"

no* criarNo(int valor){
    no* novoNo = malloc(sizeof(no));
    novoNo->pai = NULL;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->valor = valor;
    novoNo->cor = VERMELHO;
    return novoNo;
}

void inicializar(arvore *nova){
    *nova = NULL;
}

void imprimir(arvore a){
    printf("%d [%d] ", a->valor, a->cor);
}

void preOrder(arvore a) {
	printf("(");
	if(a!= NULL) {
		imprimir(a);
		preOrder(a->esq);
		preOrder(a->dir);
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

int ehRaiz(no *pivo){
    if(pivo->pai==NULL){
        return 1;
    }else{
        return 0;
    }
}

int ehFilhoEsquerdo(no *pivo){
    if(pivo->pai->esq==pivo){
        return 1;
    }else{
        return 0;
    }
}

int ehFilhoDireito(no *pivo){
    if(pivo==pivo->pai->dir){
        return 1;
    }else{
        return 0;
    }
}

no * buscarAvo(no *pivo){
    if(pivo->pai!=NULL){
        return pivo->pai->pai;    
    }else{
        return NULL;
    }   
}

no * buscarTio(no *novo){
    if(ehFilhoEsquerdo(novo->pai)){
        return buscarAvo(novo)->dir;
    }else{
        return buscarAvo(novo)->esq;
    }
}

void recolorir(no *pivo){
    no * avo = buscarAvo(pivo);
    if(ehRaiz(avo)){
         avo->esq->cor= PRETO;
         avo->dir->cor=PRETO;
    }else{
        avo->cor=VERMELHO;
        avo->esq->cor= PRETO;
        avo->dir->cor=PRETO;
    }
}

void rotacao_simples_direita(arvore* arvore,no *pivo){
    no *u, *t2;
    u= pivo->esq;    
    if(u->dir!=NULL){
        t2 = u->dir;
    }else{
        t2 = NULL;
    } 
      
    //rotação    
    if(t2 != NULL){
        pivo->esq = t2;
        t2->pai = pivo;
    }else{
        pivo->esq=NULL;
    }
    //pai de u
    if(pivo->pai!=NULL){
        if(ehFilhoEsquerdo(pivo)){
            u->pai->esq = pivo->pai;       
        }else{
           u->pai->dir = pivo->pai;  
        }
    }else{
        u->pai = NULL;
        *arvore = u;
    }
    u->dir = pivo;
    pivo->pai = u;
    
    //corrigindo cores
    u->cor=PRETO;
    u->dir->cor = VERMELHO;
    
}
void rotacao_simples_esquerda(arvore *arvore, no* pivo){
    no *u, *t2;
    u= pivo->dir;
    if(u->esq !=NULL){
        t2 = u->esq;
    }else{
        t2 = NULL;
    }
    
    //rotação
    if(t2!=NULL){
        pivo->dir = t2;
        t2->pai = pivo;
    }else{
        pivo->dir = NULL;
    }
    if(pivo->pai!=NULL){
        if(ehFilhoEsquerdo(pivo)){
            u->pai->esq = pivo->pai;
        }else{
            u->pai->dir = pivo->pai;
        }
    }else{
        u->pai =NULL;
        *arvore = u;
    }
    u->esq = pivo;
    pivo->pai = u;

    //corrigindo cores
    u->cor=PRETO;
    u->esq->cor = VERMELHO;
    
}

void rotacao_dupla_esquerda(arvore *arvore,no *pivo){
    no * u;
    no * v;
    no * t2;
    no * t3;
    u = pivo->dir;
    v = u->esq;

    if(v->esq!=NULL){
        t2 = v->esq;
    }else{
        t2 = NULL;
    }
    if(v->dir!=NULL){
        t3 = v->dir;
    }else{
        t3 = NULL;
    }
    //primeira rotaçao
    if(t3!=NULL){
        u->esq = t3;
        t3->pai = u;
    }else{
        u->esq = NULL;
    }
    v->dir = u;
    u->pai = v;
    pivo->dir = v;
    v->pai = pivo;
    //segunda rotação
    if(pivo->pai!=NULL){
       if(ehFilhoEsquerdo(pivo)){
            v->pai->esq = pivo->pai;
        }else{
            v->pai->dir = pivo->pai;
        }
    }else{
        v->pai = NULL;
        *arvore = v;
    }
    if(t2!=NULL){
        pivo->dir = t2;
        t2->pai = pivo;
    }else{
        pivo->dir = NULL;
    }
    v->esq = pivo;
    pivo->pai = v;
    
    //corrigindo cores
    v->cor = PRETO;
    v->esq->cor= VERMELHO;

}
void rotacao_dupla_direita(arvore *arvore,no* pivo){
    no * u;
    no * v;
    no * t2;
    no * t3;
    u = pivo->esq;
    v = u->dir;

    if(v->esq!=NULL){
        t2 = v->esq;
    }else{
        t2 = NULL;
    }
    if(v->dir!=NULL){
        t3 = v->dir;
    }else{
        t3 = NULL;
    }
    //primeira rotaçao
    if(t2!=NULL){
        u->dir = t2;
        t2->pai = u;
    }else{
        u->esq = NULL;
    }
     printf("1 oi");
    v->esq = u;
    u->pai = v;
    pivo->esq = v;
    v->pai = pivo;
    //segunda rotação
     printf("1");
    if(pivo->pai!=NULL){
       if(ehFilhoEsquerdo(pivo)){
           pivo->pai->esq = v;
        }else{
           pivo->pai->dir = v;
        }
    }else{
        v->pai = NULL;
        *arvore = v;
    }
    printf("1");
    if(t3!=NULL){
        pivo->esq = t3;
        t3->pai = pivo;
    }else{
        pivo->esq = NULL;
    }
    v->dir = pivo;
    printf("a");
    pivo->pai = v;
    printf("b");
    //corrigindo cores
    v->cor = PRETO;
    v->dir->cor= VERMELHO;

}

void corrigir(arvore *arvore, no *novo){
    if(novo->pai == NULL){
        novo->cor=PRETO;
        *arvore = novo;
    }else if(novo->pai->cor==VERMELHO){
        no *tio = buscarTio(novo);
        //caso 1: tio é vermelho
        if(tio !=NULL && tio->cor==VERMELHO){
            recolorir(novo);
            corrigir(arvore,novo->pai->pai);
        //caso 2: tio é preto e novo é filho esquerdo e pai é esquerdo
        }else if(ehFilhoEsquerdo(novo) && ehFilhoEsquerdo(novo->pai)){
            rotacao_simples_direita(arvore,novo->pai->pai);  
        //caso 3: tio é preto, novo filho esquerdo e pai de novo direito
        }else if(ehFilhoEsquerdo(novo) && ehFilhoDireito(novo->pai)){
            rotacao_dupla_esquerda(arvore,novo->pai->pai);
        //caso 2: tio é preto e novo é filho direito e pai é direito
        }else if(ehFilhoDireito(novo) && ehFilhoDireito(novo->pai)){
            rotacao_simples_esquerda(arvore, novo->pai->pai);
        //caso 3: tio é preto, novo filho direito e pai de novo esquerdo
        }else if(ehFilhoDireito(novo) && ehFilhoEsquerdo(novo->pai)){
            rotacao_dupla_direita(arvore,novo->pai->pai);   
        }
    }
}

void inserir(arvore *arvoreInicializada,int valor){
    no *pai = NULL;
    no *novo;
    no *temp = *arvoreInicializada;
    //percorrendo arvore
    while(temp !=NULL){
        pai = temp;
        if(valor<temp->valor){
            temp = temp->esq;
        }else{
            temp = temp->dir;
        }
    }
    novo = criarNo(valor);
    novo->pai = pai;
    //ligando arvore com novo no
    if(ehRaiz(novo)){
        *arvoreInicializada = novo;
    }else if(valor<pai->valor){
        pai->esq = novo;
    }else{
        pai->dir = novo;
    }
    corrigir(arvoreInicializada,novo);
}



