#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    char vertice;
    struct lista* prox; 
}lista;

typedef struct listaAdjacencia{
    int nmrVertices;
    lista** verticesVizinhos;
    
}listaAdjacencia;

listaAdjacencia* criarLista(int nmrV){
    listaAdjacencia* lista = (listaAdjacencia*)malloc(sizeof(listaAdjacencia));
    listaAdjacencia->nmrVertices = nmrV;
    listaAdjacencia->verticesVizinhos = (lista**)malloc(nmrV*sizeof(lista*));
    
    int i;
    for(i=0; i<nmrV;i++){
        listaAdjacencia->verticesVizinhos[i] = (lista*)malloc(sizeof(lista));
    }

    return listaAdjacencia;
}

void addVizinho(listaAdjacencia* l, char a1,char a2, char vertices[]){
    lista* vizinho = (lista*)malloc(sizeof(lista));
    vizinho->vertice = a2;
    vizinho->prox = NULL;
    
    //procurar as posicoes de a1 e a2
    int i, p1,p2;
   
    for(i=0;i<v;i++){
        if(a1==vertices[i]){
            p1=i;
        }
        if(a2==vertices[i]){
            p2=i;
        }
    }
    
    l->posicao[p1]= vizinho;

    
}

