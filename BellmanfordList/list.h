#ifndef list_H
#define list_H
#include <stdio.h>
#include <stdlib.h>
//---------------------------------Lista--------------------------------
typedef enum CORES{BRANCO,CINZA,PRETO} COR;

typedef struct vertice{
    char letra;
    struct lista* adj;
    COR cor;
    struct vertice* pai;
    int dist;
    int tempoI;
    int tempoF;
}vertice;

typedef struct aresta{
    struct vertice* inicial;
    struct vertice* final;
    int peso;
}aresta;

typedef struct no{
    struct vertice* noVertice;
    struct aresta* noAresta;
    struct no* prox;

}no;

typedef struct lista{
    struct no* inicial;

}lista;


lista* inicializarLista();
vertice* inicializar_vertice(char letra);
void inserirNaLista(lista* lista, vertice* vertice);
void imprimirLista(lista* lista);

//---------------------------------Grafo--------------------------------
typedef struct grafo{
    int nmrVertices;
    int nmrArestas;
    lista* lista_v;
    lista* lista_arestas;
}grafo;

grafo* criarGrafo(int nmrV,int nmrA);
void addVertices(grafo* g, char vert);
int buscarVertice(char v, lista* l);
vertice* retornarVertice(char v, lista* l);
void addAresta(grafo* gr,char v1,char v2,int peso);
void inserirArestaNaLista(lista* lista, aresta* a);
aresta* inicializarAresta();
void imprimirArestas(grafo* gr);
void imprimirListaADJ(grafo* gr);
int bellmanFord(grafo* g, char origem);
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
int filaVazia(fila* fila);
void buscaEmLargura(grafo* g, char origem);
void imprimirListaPosBusca(grafo* gr);

#endif