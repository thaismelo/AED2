#include <stdio.h>
#include <stdlib.h>
#include "listaAdjacencia.h"
//---------------------------------Lista--------------------------------
lista* inicializarLista(){
    lista* nova = (lista*) malloc(sizeof(lista));
    nova->inicial=NULL;
    return nova;
}

vertice* inicializar_vertice(char letra){
    vertice* ver = (vertice*)malloc(sizeof(vertice));
    ver->letra = letra;
    ver->adj = inicializarLista();
    return ver;
}
void inserirNaLista(lista* lista, vertice* vertice){
    no* novoNo = (no*) malloc(sizeof(no));
    novoNo->noVertice = vertice; //no que vai receber o inteiro e ser adicionado na lista
    if(lista->inicial==NULL){
        lista->inicial = novoNo; //adiciona o primeiro elemento
        novoNo->prox = NULL;
    }else{
        no* cursor = lista->inicial;
        while(cursor->prox!=NULL){
            cursor = cursor->prox;
        }
        novoNo->prox = NULL; // vai ser o ultimo da lista
        cursor->prox = novoNo;

    }
}
void imprimirLista(lista* lista){
    no* cursor;
    for(cursor=lista->inicial;cursor!=NULL;cursor= cursor->prox){
        printf("%c\n", cursor->noVertice->letra);
    }
}
//---------------------------------Lista--------------------------------


//---------------------------------Grafo--------------------------------

grafo* criarGrafo(int nmrV){
    grafo* g = (grafo*)malloc(sizeof(grafo)); //aloquei memoria para o struct
    g->nmrVertices = nmrV;
    g->lista_v = inicializarLista();
    return g;
}

void addVertices(grafo* g, char vert){
    vertice* ver = inicializar_vertice(vert);
    inserirNaLista(g->lista_v,ver);
}
int buscarVertice(char v, lista* l){
    no* cursor;
    for(cursor = l->inicial;cursor!=NULL; cursor=cursor->prox){
        if(cursor->noVertice->letra == v){
            return 1;
        }
    }
    return 0;
}
vertice* retornarVertice(char v, lista* l){
    no* cursor;
    for(cursor = l->inicial;cursor!=NULL; cursor=cursor->prox){
        if(cursor->noVertice->letra == v){
            return cursor->noVertice;
        }
    }
    return NULL;
}
void addAresta(grafo* gr,char v1,char v2){ //grafo nao dirigido
    no* cursor;
    for(cursor = gr->lista_v->inicial;cursor!=NULL; cursor=cursor->prox){
        if(cursor->noVertice->letra==v1){
            if(buscarVertice(v2,gr->lista_v)){
                vertice* novo = retornarVertice(v2,gr->lista_v);
                inserirNaLista(cursor->noVertice->adj, novo);
                inserirNaLista(novo->adj, cursor->noVertice);
                break;
            }
        }
    }
}

void imprimirListaADJ(grafo* gr){
    no* cursor;
    no* cursor2;
    for(cursor=gr->lista_v->inicial;cursor!=NULL;cursor= cursor->prox){
        printf("%c-> ", cursor->noVertice->letra);
        for(cursor2=cursor->noVertice->adj->inicial;cursor2!=NULL;cursor2= cursor2->prox){
             printf("%c\t", cursor2->noVertice->letra);
        }
        printf("\n");
    }

}


