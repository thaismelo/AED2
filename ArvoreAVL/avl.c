#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

void imprimir(no *raiz){
    printf("[%d, %d] ", raiz->valor, raiz->fb);
}

void preOrder(no *raiz){
    if(raiz!=NULL){
        imprimir(raiz);
        preOrder(raiz->esq);
        preOrder(raiz->dir);
    }
}
void inOrder(no *raiz){
    if(raiz!=NULL){
        inOrder(raiz->esq);
        imprimir(raiz);
        inOrder(raiz->dir);
    }
}

void posOrder(no *raiz){
    if(raiz!=NULL){
        posOrder(raiz->esq);
        posOrder(raiz->dir);
        imprimir(raiz);
    }
}

void limparArvore(no *raiz){
    if(raiz!=NULL){
        limparArvore(raiz->esq);
        limparArvore(raiz->dir);
        free(raiz);
    }
}

no* rotacao_simples_direita(no *p){
    no * u;
    no * t2;
    u = p->esq;
    t2 = u->dir;

    p->esq = t2;
    u->dir = p;
    if(u->fb==0){
        p->fb = -1;
        u->fb = 1; 
    }else{   
        p->fb = 0;
        u->fb = 0;
    }
    return u;
}

no* rotacao_simples_esquerda(no *p){
    no * u;
    no * t2;
    u = p->dir;
    t2 = u->esq;

    p->dir = t2;
    u->esq = p;

    if(u->fb==0){
        p->fb = 1;
        u->fb = -1; 
    }else{   
        p->fb = 0;
        u->fb = 0;
    }
    return u;
}
no* rotacao_dupla_direita(no *p){
    no * u;
    no * v;
    no * t2;
    no * t3;
    u = p->esq;
    v = u->dir;
    t2 = v->esq;
    t3 = v->dir;

    //primeira rotaçao
    u->dir = t2;
    v->esq = u;
    p->esq = v;
    
    //segunda rotação
    p->esq = t3;
    v->dir = p;


    switch(v->fb){
        case 0:
            u->fb=0;
			p->fb=0;
			v->fb=0;
			break;
		case 1:
			u->fb=-1;
			p->fb=0;
			v->fb=0;
			break;
		case -1:
			u->fb=0;
			p->fb=1;
			v->fb=0;
			break;
	}
	return v;
    
}

no* rotacao_dupla_esquerda(no *p){
    no * u;
    no * v;
    no * t2;
    no * t3;
    u = p->dir;
    v = u->esq;
    t2 = v->esq;
    t3 = v->dir;

    //primeira rotaçao
    u->esq = t3;
    v->dir = u;
    p->dir = v;
    
    //segunda rotação
    p->dir = t2;
    v->esq = p;


    switch(v->fb){
        case 0:
            u->fb=0;
			p->fb=0;
			v->fb=0;
			break;
		case 1:
			u->fb=0;
			p->fb=-1;
			v->fb=0;
			break;
		case -1:
			u->fb=1;
			p->fb=0;
			v->fb=0;
			break;
	}
	return v;
    
}

no* rotacionar(no *pivo){
        if(pivo->fb>0){
            switch(pivo->dir->fb){
                case 0:
                    return rotacao_simples_esquerda(pivo);
                    break;
                case 1:
                    return rotacao_simples_esquerda(pivo);
                    break;
                case -1:
                   return rotacao_dupla_esquerda(pivo);
                   break;
             }
        }else{
             switch(pivo->esq->fb){
                case 0:
                    return rotacao_simples_direita(pivo);
                    break;
                case 1:
                    return rotacao_dupla_direita(pivo);
                    break;
                case -1:
                   return rotacao_simples_direita(pivo);
                   break;
             }
        }
        
}


no * inserir (no* raiz, int valor, int *cresceu){
    if(raiz == NULL) {
        no *novo = (no *) malloc(sizeof(struct no));
        novo->valor = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->fb = 0;
        *cresceu = 1;
        return novo;
    } else {
           if(valor > raiz->valor) {
                raiz->dir = inserir(raiz->dir,valor, cresceu);
                if(*cresceu) {
                       switch(raiz->fb) {
                            case -1:
                                 raiz->fb = 0;
                                 *cresceu = 0;
                                 break;
                            case 0:
                                raiz->fb = 1;
                                 *cresceu = 1;
                                 break;
                            case 1:
                                raiz->fb = 2;
                                *cresceu = 0;
                                return rotacionar(raiz);
                       }

                }
                
           } else {
                raiz->esq = inserir(raiz->esq, valor, cresceu);
                if(*cresceu) {
                       switch(raiz->fb) {
                            case -1:
                                 raiz->fb = -2;
                                 *cresceu = 0;
                                 return rotacionar(raiz);
                            case 0:
                                raiz->fb = -1;
                                 *cresceu = 1;
                                 break;
                            case 1:
                                raiz->fb = 0;
                                *cresceu = 0;
                                break;
                       }

                }


           }
           return raiz;
    }
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

no* remover(no *raiz, int valor, int *diminuiu){
    if(raiz==NULL)
        return NULL;
    if(valor == raiz->valor){
        no *aux;
        *diminuiu = 1;
        if(raiz->dir==NULL && raiz->esq==NULL){
            raiz = NULL;
            free(raiz);
        }
       else if(raiz->dir == NULL){
            aux = raiz;
            raiz = raiz->esq;
            free(aux);
        }
       else if(raiz->esq == NULL){
            aux = raiz;
            raiz = raiz->dir;
            free(aux);
        }else{
            raiz->valor = maiorDescendente(raiz->esq);
            raiz->esq = remover(raiz->esq, raiz->valor,diminuiu); 
            if(*diminuiu) {
                switch(raiz->fb) {
                    case -1:
                        raiz->fb = 0;
                        *diminuiu = 1;
                        break;
                case 0:
                        raiz->fb = 1;
                        *diminuiu= 0;
                        break;
                case 1:
                        raiz->fb = 2;
                        if(raiz->dir->fb==0){
                            *diminuiu= 0;
                        }else{
                            *diminuiu= 1;
                  
                        }
                        return rotacionar(raiz);
                    }

            }
        }              
    }

    else if(valor > raiz->valor){
        raiz->dir = remover(raiz->dir,valor,diminuiu);
        if(*diminuiu) {
                       switch(raiz->fb) {
                            case -1:
                                 raiz->fb = -2;
                                if(raiz->esq->fb==0){
                                    *diminuiu=0;
                                 }else{
                                    *diminuiu = 1;
                                }  
                                return rotacionar(raiz);
                            case 0:
                                raiz->fb = -1;
                                 *diminuiu= 0;
                                 break;
                            case 1:
                                raiz->fb = 0;
                                *diminuiu= 1;
                                break;
                       }

                }                
    }else if (valor < raiz->valor){
        raiz->esq = remover(raiz->esq,valor,diminuiu);
        if(*diminuiu) {
            switch(raiz->fb) {
                case -1:
                    raiz->fb = 0;
                    *diminuiu = 1;
                    break;
                case 0:
                    raiz->fb = 1;
                    *diminuiu= 0;
                    break;
                case 1:
                    raiz->fb = 2;
                    if(raiz->dir->fb==0){
                        *diminuiu= 0;
                    }else{
                        *diminuiu= 1;
                  
                    }
                    return rotacionar(raiz);
                }

            }
               

        }
    return raiz;
}

