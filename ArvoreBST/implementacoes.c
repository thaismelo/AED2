#include "funcoesBST.h"
#include <stdlib.h>

no* criar_no(int valor){
    no* novo = (no *) malloc(sizeof(no));
    novo->valor = valor;
    novo->dir = NULL;
    novo->esq = NULL;
    return novo;
}

void imprimir(no *raiz){
    printf("[%d] ", raiz->valor);
}

void limparArvore(no *raiz){
    if(raiz!=NULL){
        limparArvore(raiz->esq);
        limparArvore(raiz->dir);
        free(raiz);
    }
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

no* inserir(no *raiz,int valor){
    if(raiz == NULL){
        return criar_no(valor);
    }else{
        if(valor<raiz->valor){
            raiz->esq = inserir(raiz->esq,valor);
        }else{
            raiz->dir = inserir(raiz->dir,valor);
        }
        return raiz;
    }
}

no * buscarElemento(no *raiz, int valor){
    if(raiz!=NULL){
        if(raiz->valor==valor){
            return raiz;
        }else{
            if(valor>raiz->valor){
                return buscarElemento(raiz->dir,valor);
            }else{
               return buscarElemento(raiz->esq,valor);
            }
        }
    }

    return NULL;

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

int menorDescendente(no *raiz){
    if(raiz != NULL){
        if(raiz->esq == NULL){
            return raiz->valor;
        }else{
            menorDescendente(raiz->esq);
        } 
    }
}

int altura(no *raiz){
    if(raiz==NULL){
        return 0;
    }
    if (raiz->esq==NULL && raiz->dir==NULL){
        return 1;
    }else{
        int esq = altura(raiz->esq);
        int dir = altura(raiz->dir);
        if(esq<dir){
            return dir+1;
        }else{
            return esq+1;
        }
    }
   
}
int sucessorDoElemento(no *raiz, int valor){
    no *elemento = buscarElemento(raiz,valor);
    int maior = maiorDescendente(raiz);
    if(elemento!=NULL && valor!=maior && raiz!=NULL){
        if(elemento->dir!=NULL){
            return menorDescendente(elemento->dir);
        }else{
            no *cursor = raiz;
            no *sucessor = NULL;
            while(elemento!=cursor && elemento!=NULL){
                if(cursor->valor>elemento->valor){
                    sucessor = cursor;
                    cursor = cursor->esq;
                }else{
                    cursor = cursor->dir;
                }
            }
            return sucessor->valor;
        }
    }else{
        return -1;
    }
}
int antecessorDoElemento(no *raiz, int valor){
    no *elemento = buscarElemento(raiz,valor);
    int menor = menorDescendente(raiz);
    if(elemento!=NULL && valor!=menor && raiz!=NULL){
        if(elemento->esq!=NULL){
            return maiorDescendente(elemento->esq);
        }else{
            no *cursor = raiz;
            no *antecessor = NULL;
            while(elemento!=cursor && elemento!=NULL){
                if(cursor->valor<elemento->valor){
                    antecessor = cursor;
                    cursor = cursor->dir;
                }else{
                    cursor = cursor->esq;
                }
            }
            return antecessor->valor;
        }
    }else{
        return -1;
    }
}
int paiDoElemento(no *raiz, int valor){
    no* pai = NULL;
    no* cursor = raiz;
    no* elemento = buscarElemento(raiz,valor);
    if(valor == raiz->valor || elemento == NULL)
        return -1;
    while(cursor!=NULL){
        if(cursor->valor > valor){
            pai = cursor;
            cursor = cursor->esq;
            if(cursor != NULL && cursor->valor == valor)
                return pai->valor;
        }
        if(cursor->valor < valor){
            pai = cursor;
            cursor = cursor->dir;
            if(cursor != NULL && cursor->valor == valor)
                return pai->valor;
        }

    }
    return -1;
}
no* remover(no *raiz,int valor){
    if(raiz==NULL)
        return NULL;
    if(valor == raiz->valor){
        if(raiz->dir == NULL){
            return raiz->esq;
        }
        if(raiz->esq==NULL){
            return raiz->dir;
        }
        raiz->valor = maiorDescendente(raiz->esq);
        raiz->esq = remover(raiz->esq, raiz->valor);
        return raiz;
    }

    if(valor > raiz->valor){
        raiz->dir = remover(raiz->dir,valor);

    }else{
        raiz->esq = remover(raiz->esq,valor);
    }
}
