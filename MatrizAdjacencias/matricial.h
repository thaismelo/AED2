#ifndef matriz_H
#define matriz_H
#include <stdio.h>
#include <stdlib.h>

typedef enum CORES{BRANCO,CINZA,PRETO} COR;

typedef struct vertice{
    char letra;
    COR cor;
    struct vertice* pai;
    int dist;
}vertice;

typedef struct grafo{
    int nmrVertices;
    int **matriz;
    char * vertices;
}grafo;

grafo* inicializarGrafo(int nmrV);
vertice* inicializarVertice(char letra);
void addVertices(grafo* g, char vert, int indice);
void addAresta(grafo* gr,char v1,char v2);
vertice* retornarVertice(grafo*,char v);
int retornarIndiceVertice(grafo* g, char v);
void imprimirGrafo(grafo* g);

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
vertice* removerDaFila(fila* fila);
void imprimirFila(fila* fila);
int filaVazia(fila* fila);
int verificarADJ(grafo* g,char vert1,char vert2);
void buscaEmLargura(grafo* g, char origem);
void imprimirListaPosBusca(grafo* gr);
#endif