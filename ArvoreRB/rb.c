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
    if(a!=NULL){
		if(cor(a) == PRETO){
			printf("\x1b[30m[%d, PRETO]\x1b[0m", a->valor);
		}else if (cor(a)==VERMELHO){
			printf("\x1b[31m[%d, VERMELHO]\x1b[0m", a->valor);
		}
		else if(cor(a) == DUPLO_PRETO){
			printf("\x1b[32m[%d, DUPLO_PRETO]\x1b[0m", a->valor);	
		}
	}else{
		printf("\x1b[30m N \x1b[0m");
	}
}


void preOrder(arvore a) {
	if(a!= NULL) {
		imprimir(a);
		preOrder(a->esq);
		preOrder(a->dir);
	}
}


COR cor(no *raiz){
    COR c;
    if(raiz==NULL || raiz->cor==PRETO){
        c=PRETO;
    }else if (raiz->cor==VERMELHO){
        c= VERMELHO;
    }else{
        c= DUPLO_PRETO;
    }
    return c;
}

int ehRaiz(no *pivo){
   return (pivo->pai==NULL);
}

int ehFilhoEsquerdo(no *pivo){
    return (pivo->pai != NULL && pivo==pivo->pai->esq);
}

int ehFilhoDireito(no *pivo){
    return (pivo->pai !=NULL && pivo==pivo->pai->dir);
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

no* buscarIrmao(no *pivo){
    if(ehFilhoEsquerdo(pivo)){
        return pivo->pai->dir;
    }else{
        return pivo->pai->esq;
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
   u = pivo->esq;
   t2 = u->dir;
   
    //rotação
    pivo->esq = t2;
    u->dir = pivo;
    
    //colorir
    u->cor=PRETO;
    pivo->cor=VERMELHO;
    
    //atualizar pais
    if(t2!=NULL)
        t2->pai = pivo;

    u->pai = pivo->pai;

    if(ehRaiz(pivo)){
        *arvore = u;
    }else{
        if(ehFilhoDireito(pivo)){
            pivo->pai->dir = u;
        }else{  
            pivo->pai->esq = u;
        }
    }
    pivo->pai = u;
    

    
}
void rotacao_simples_esquerda(arvore *arvore, no* pivo){
    no *u, *t2;
    u= pivo->dir;
    t2 = u->esq;
    //rotação
    pivo->dir = t2;
    if(t2!=NULL){
        t2->pai = pivo;
    }

    u->esq = pivo;
    u->pai = pivo->pai;
    if(ehRaiz(pivo)){
       *arvore = u;
    }else{
        if(ehFilhoEsquerdo(pivo)){
            pivo->pai->esq = u;
        }else{
            pivo->pai->dir = u;
        }
    }
     pivo->pai = u;
    //corrigindo cores
    u->cor=PRETO;
    pivo->cor = VERMELHO;
    
}

void rotacao_dupla_esquerda(arvore *arvore,no *pivo){
    no *u,*v,*t2,*t3;
    u = pivo->dir;
    v = u->esq;
    t2 = v->esq;
    t3 = v->dir;
    //primeira rotaçao
    u->esq = t3;
    v->dir= u;
    pivo->dir= v;   

    //segunda rotação
    pivo->dir = t2;
    v->esq = pivo; 

    //atualizar cores
    v->cor = PRETO;
    pivo->cor = VERMELHO;

    //atualizar pais   
    if(t2!=NULL){
        t2->pai = pivo;
    }
    if(t3!=NULL){
        t3->pai = u;
    }
    u->pai = v;
    v->pai = pivo->pai;
    if(ehRaiz(pivo)){
        *arvore = v;
    }else{
        if(ehFilhoDireito(pivo)){
            pivo->pai->dir = v;
        }else{
            pivo->pai->esq = v;
        }
    }
    pivo->pai = v;
    
}
void rotacao_dupla_direita(arvore *arvore,no* pivo){
    no *u,*v,*t2,*t3;
    u = pivo->esq;
    v = u->dir;
    t2 = v->esq;
    t3 = v->dir;
    //primeira rotaçao
    u->dir = t2;
    v->esq = u;
    pivo->esq= v;   

    //segunda rotação
    pivo->esq = t3;
    v->dir = pivo; 

    //atualizar cores
    v->cor = PRETO;
    pivo->cor = VERMELHO;

    //atualizar pais   
    if(t2!=NULL){
        t2->pai = u;
    }
    if(t3!=NULL){
        t3->pai = pivo;
    }
    u->pai = v;
    v->pai = pivo->pai;
    if(ehRaiz(pivo)){
        *arvore = v;
    }else{
        if(ehFilhoDireito(pivo)){
            pivo->pai->dir = v;
        }else{
            pivo->pai->esq = v;
        }
    }
    pivo->pai = v;
}

void ajustar(arvore *arvore, no *novo){
    if(novo->pai == NULL){
        novo->cor=PRETO;
        *arvore = novo;
    }else if(novo->pai->cor==VERMELHO){
        no *tio = buscarTio(novo);
        //caso 1: tio é vermelho
        if(tio !=NULL && tio->cor==VERMELHO){
            recolorir(novo);
            ajustar(arvore,novo->pai->pai);
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
    ajustar(arvoreInicializada,novo);
}
int maiorDescendente(no *raiz){
    if(raiz != NULL){
        if(raiz->dir == NULL){
            return raiz->valor;
        }else{
            maiorDescendente(raiz->dir);
        }
    }
}

void remover (arvore *arvore, int valor) {
    no *temp, *pai, *novo;
    temp = *arvore;
    pai = NULL;
    

    //Percorre a arvore até achar o elemento ou null
    while(temp != NULL && temp->valor != valor) {
        pai = temp;
        if(valor > temp->valor) {
            temp = temp->dir;
        } else {
            temp = temp->esq;
        }
    }
    
    //Se o elemento não existe encerra a função
    if(temp == NULL)
          return ;

    //O elemento a ser removido tem dois filhos OK
    if(temp->esq != NULL && temp->dir != NULL) {
        temp->valor = maiorDescendente(temp->esq);
        remover(&temp->esq, temp->valor);
    }
    
    //Tem somente o filho esquerdo vermelho OK
    else if(temp->dir == NULL && temp->esq != NULL) {
       if(ehFilhoEsquerdo(temp)){ //atualizar pai de temp
            if(temp->esq!=NULL){
                temp->esq->cor=PRETO;
            }
            temp->pai->esq = temp->esq;
        }else{
            if(temp->esq!=NULL){
                temp->dir->cor=PRETO;
            }
            temp->pai->dir = temp->esq;
        }
    }
    
    //Tem somente o filho direito vermelho OK
    else if(temp->esq == NULL && temp->dir != NULL) {
       if(ehFilhoEsquerdo(temp)){ //atualizar pai de temp
            if(temp->dir!=NULL){
                temp->dir->cor=PRETO;
            }
            temp->pai->esq = temp->dir; 
        }else{
             if(temp->dir!=NULL){
                temp->dir->cor=PRETO;
            }
            temp->pai->dir = temp->dir; 
        }  
    }
    //Não tem filhos e é vermelho OK
   else if(temp->cor == VERMELHO) {
        if(ehFilhoEsquerdo(temp)) {
            temp->pai->esq = NULL;
            temp = NULL;
            free(temp);
        } else {
            temp->pai->dir = NULL;
            temp = NULL;
            free(temp);
        }
    }
    //nao tem filhos e é preto
    else{
          temp->cor = DUPLO_PRETO;
          temp->valor = 0;
          reajustar(arvore,temp);
    }  
}
void reajustar(arvore *arvore, no *pivo){

    //caso 1
    if(ehRaiz(pivo)){
        if(pivo->dir==NULL && pivo->esq==NULL){
            pivo->cor= PRETO;
            free(pivo);
            pivo = NULL;
            *arvore = NULL;
        }else{
            pivo->cor = PRETO;
        }
        return ;
    }
    //caso 2 esquerdo
    if(ehFilhoEsquerdo(pivo) && cor(pivo->pai)==0 && cor(buscarIrmao(pivo))==1 && cor(buscarIrmao(pivo)->esq)== 0 && cor(buscarIrmao(pivo)->dir)==0){
        rotacao_caso2_esq(arvore,pivo);
        return;
    }
     //caso 2 direito
    if(ehFilhoDireito(pivo) && cor(pivo->pai)==0 && cor(buscarIrmao(pivo))==1 && cor(buscarIrmao(pivo)->esq)== 0 && cor(buscarIrmao(pivo)->dir)==0){
        rotacao_caso2_dir(arvore,pivo);
        return;
    }
    //caso 3
     if(cor(pivo->pai)==0){
        if(cor(buscarIrmao(pivo))==0){
            if(buscarIrmao(pivo)!=NULL){
                if(cor(buscarIrmao(pivo)->esq)== 0 && cor(buscarIrmao(pivo)->dir)==0){
                    rotacao_caso3(arvore,pivo);
                    return ;
                }
            }
        }
    }
    //caso 4
    if(cor(pivo->pai)==1){
        if(cor(buscarIrmao(pivo))==0){
            if(buscarIrmao(pivo)!=NULL){
                if(cor(buscarIrmao(pivo)->esq)== 0 && cor(buscarIrmao(pivo)->dir)==0){
                    rotacao_caso4(arvore,pivo);
                    return ;
                }
            }
        }

    }
    //caso 5 esquerdo
    if(ehFilhoEsquerdo(buscarIrmao(pivo)) && buscarIrmao(pivo)->dir!=NULL && (cor(pivo->pai)==0 || cor(pivo->pai)==1) && cor(buscarIrmao(pivo))==0 && 
    cor(buscarIrmao(pivo)->dir)== 1 && cor(buscarIrmao(pivo)->esq)==0){
        rotacao_caso5_esq(arvore,pivo);
        return;
    }
    //caso 5
    if(ehFilhoDireito(buscarIrmao(pivo)) && buscarIrmao(pivo)->esq!=NULL && (cor(pivo->pai)==0 || cor(pivo->pai)==1) && cor(buscarIrmao(pivo))==0 && 
    cor(buscarIrmao(pivo)->esq)== 1 && cor(buscarIrmao(pivo)->dir)==0){
        rotacao_caso5_dir(arvore,pivo);
        return;
    }
    //caso 6
    if(ehFilhoEsquerdo(pivo) && (cor(pivo->pai)==0 || cor(pivo->pai)==1)){
        if(cor(buscarIrmao(pivo))==0){
            if(buscarIrmao(pivo)!=NULL){
                if((cor(buscarIrmao(pivo)->esq)== 1 || cor(buscarIrmao(pivo)->esq)==0) && cor(buscarIrmao(pivo)->dir)==1){
                    rotacao_caso6_esq(arvore,pivo);
                    return ;
                }
            }
        }
    }
     //caso 6 direito
    if(ehFilhoDireito(pivo) && (cor(pivo->pai)==0 || cor(pivo->pai)==1)){
        if(cor(buscarIrmao(pivo))==0){
            if(buscarIrmao(pivo)!=NULL){
                if((cor(buscarIrmao(pivo)->dir)== 1 || cor(buscarIrmao(pivo)->dir)==0) && cor(buscarIrmao(pivo)->esq)==1){
                    rotacao_caso6_dir(arvore,pivo);
                    return ;
                }
            }   
        }
    }
}

void rotacao_caso2_esq(arvore *arvore, no *pivo){
    no *p,*s,*x;
    p= pivo->pai;
    s = p->dir;
    x = s->esq;

    //rotação
    p->dir = x;
    s->esq = p;
    
    //atualizar cores
    pivo->pai->cor = VERMELHO;
    s->cor = PRETO;
    
    //atualizar pais
    if(x!=NULL)
        x->pai = p;
    
    s->pai = p->pai;
    if(ehRaiz(p)){
        s->pai=NULL;
        *arvore = s;
    }else{
        if(ehFilhoEsquerdo(p)){
            p->pai->esq = s;
        }else{
            p->pai->dir = s;
        }
    }
    p->pai = s;
    reajustar(arvore,pivo);
}
void rotacao_caso2_dir(arvore *arvore, no *pivo){
    no *p,*s,*x;
    p= pivo->pai;
    s = p->esq;
    x = s->dir;

    //rotação
    p->esq = x;
    s->dir = p;
    
    //atualizar cores
    pivo->pai->cor = VERMELHO;
    s->cor = PRETO;
    
    //atualizar pais
    if(x!=NULL)
        x->pai = p;
    
    s->pai = p->pai;
    if(ehRaiz(p)){
        s->pai=NULL;
        *arvore = s;
    }else{
        if(ehFilhoEsquerdo(p)){
            p->pai->esq = s;
        }else{
            p->pai->dir = s;
        }
    }
    p->pai = s;
    reajustar(arvore,pivo);
}
void rotacao_caso3(arvore *arvore, no *pivo){
    no *pai;
    pai = pivo->pai;
    
    //recolorir
    buscarIrmao(pivo)->cor = VERMELHO;
    pivo->cor = PRETO;

    if(pivo->valor==0){
        if(ehFilhoEsquerdo(pivo)){
            pivo->pai->esq = NULL;
        }else{
            pivo->pai->dir = NULL;    
        }
        free(pivo);
        pivo = NULL;       
    }

    pai->cor=DUPLO_PRETO;
    reajustar(arvore,pai);
    
}
void rotacao_caso4(arvore *arvore, no *pivo){
    pivo->pai->cor =PRETO;
    buscarIrmao(pivo)->cor= VERMELHO;
    
    if(pivo->valor == 0){        
        if(ehFilhoEsquerdo(pivo)){
            pivo->pai->esq = NULL;
        }else{
            pivo->pai->dir = NULL;    
        }
        free(pivo);
        pivo = NULL;
    }else{
       pivo->cor = PRETO;
    } 
}
void rotacao_caso5_dir(arvore *arvore, no *pivo){
    no *p,*u,*t2;
    p= pivo->pai->dir;
    u = p->esq;
    t2 = u->dir;

    p->esq = t2;
    u->dir = p;
    
    //atualizar cores
    pivo->pai->dir->cor = VERMELHO;
    u->cor = PRETO;
    
    //atualizar pais
    if(t2!=NULL)
        t2->pai = p;
    
    u->pai = p->pai;
    if(ehFilhoEsquerdo(p)){
        p->pai->esq = u;
    }else{
       p->pai->dir = u;    
    }
    p->pai = u;
    reajustar(arvore,pivo);

}
void rotacao_caso5_esq(arvore *arvore, no *pivo){
    no *p,*u,*t3;
    p= pivo->pai->esq;
    u = p->dir;
    t3 = u->esq;

    p->dir = t3;
    u->esq = p;
    
    //atualizar cores
    p->cor = VERMELHO;
    u->cor = PRETO;
    
    //atualizar pais
    if(t3!=NULL)
        t3->pai = p;
    
    u->pai = p->pai;
    if(ehFilhoEsquerdo(p)){
        p->pai->esq = u;
    }else{
       p->pai->dir = u;    
    }
    p->pai = u;
    reajustar(arvore,pivo);

}
void rotacao_caso6_esq(arvore *arvore, no *pivo){
    no *p,*u,*t3;
    p= pivo->pai;
    u = p->dir;
    t3 = u->esq;

    p->dir = t3;
    u->esq = p;
    
    //atualizar cores
    u->cor= pivo->pai->cor;
    pivo->pai->cor = PRETO;
    u->dir->cor = PRETO;
    
    //apagar duplo preto
    if(pivo->valor==0){
        pivo->pai->esq = NULL;
        free(pivo);
        pivo = NULL;
    }else{
        pivo->cor = PRETO;
    }
    //atualizar pais
    if(t3!=NULL)
        t3->pai = p;
    
    u->pai = p->pai;
    if(ehRaiz(p)){
        u->pai=NULL;
        *arvore = u;
    }else{
        if(ehFilhoEsquerdo(p)){
            p->pai->esq = u;
        }else{
            p->pai->dir = u;
        }
    }
    p->pai = u;
}

void rotacao_caso6_dir(arvore *arvore, no *pivo){
    no *p,*u,*t3;
    p= pivo->pai;
    u = p->esq;
    t3 = u->dir;

    //rotação
    
    p->esq = t3;
    u->dir= p;
    
    //atualizar cores
    u->cor= pivo->pai->cor;
    pivo->pai->cor = PRETO;
    u->esq->cor = PRETO;

    //apagar duplo preto
    if(pivo->valor==0){
        pivo->pai->dir = NULL;
        free(pivo);
        pivo = NULL;
    }else{
        pivo->cor = PRETO;
    }
    //atualizar pais
    if(t3!=NULL)
        t3->pai = p;
    
    u->pai = p->pai;
    if(ehRaiz(p)){
        u->pai=NULL;
        *arvore = u;
    }else{
        if(ehFilhoEsquerdo(p)){
            p->pai->esq = u;
        }else{
            p->pai->dir = u;
        }
    }
    p->pai = u;
}
