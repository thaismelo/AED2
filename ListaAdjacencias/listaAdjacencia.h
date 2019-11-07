#ifndef lista_H
#define lista_H
#include <stdio.h>
#include <stdlib.h>
//---------------------------------Lista--------------------------------
typedef enum CORES{BRANCO,CINZA,PRETO} COR;

typedef struct vertice{
    char letra;
    struct lista* adj;
    COR cor;
    vertice* pai;
    int dist;
}vertice;

typedef struct no{
    struct vertice* noVertice;
    struct no* prox;

}no;

typedef struct lista{
    struct no* inicial;

}lista;

lista* inicializarLista();
vertice* inicializarVertice(char letra);
void inserirNaLista(lista* lista, vertice* vertice);
void imprimirLista(lista* lista);

//---------------------------------Grafo--------------------------------
typedef struct grafo{
    int nmrVertices;
    lista* lista_v;
}grafo;

grafo* criarGrafo(int nmrV);
void addVertices(grafo* g, char vert);
int buscarVertice(char v, lista* l);
vertice* retornarVertice(char v, lista* l);
void addAresta(grafo* gr,char v1,char v2);
void imprimirListaADJ(grafo* gr);
//--------------------------------Fila----------------------------------

typedef struct noFila{
   struct vertice* noVertice;
   struct noFila* ant;
}noFila;

typedef struct fila{
   struct noFila* inicio;
   struct noFila* fim;
}fila;

fila* inicializarFila();
void inserirNaFila(fila* fila,vertice* v);
void removerDaFila(fila* fila);
void imprimirFila(fila* fila);

#endif