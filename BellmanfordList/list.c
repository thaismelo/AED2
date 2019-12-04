#include <stdio.h>
#include <stdlib.h>
#include "list.h"
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
    ver->cor = BRANCO;
    ver->dist = 10000;
    ver->pai = NULL;
    ver->tempoI = 0;
    ver->tempoF = 0;
    return ver;
}

aresta* inicializarAresta(){
	aresta* a = (aresta*)malloc(sizeof(aresta));
	a->inicial = NULL;
	a->final = NULL;
	a->peso = 10000;
	return a;
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

void inserirArestaNaLista(lista* lista, aresta* a){
    no* novo = (no*) malloc(sizeof(no));
    novo->noAresta = a; //no que vai receber o inteiro e ser adicionado na lista
    if(lista->inicial==NULL){
        lista->inicial = novo; //adiciona o primeiro elemento
        novo->prox = NULL;
    }else{
        no* cursor = lista->inicial;
        while(cursor->prox!=NULL){
            cursor = cursor->prox;
        }
        novo->prox = NULL; // vai ser o ultimo da lista
        cursor->prox = novo;

    }
}
//---------------------------------Lista--------------------------------

//---------------------------------Fila---------------------------------
fila* inicializarFila(){
   fila* fila = malloc(sizeof(fila));
   fila->inicio = NULL;
   fila->fim = NULL;
   return fila;
}

void inserirNaFila(fila* fila,vertice* v){
   noFila* novo = (noFila*) malloc(sizeof(noFila));
   novo->noVertice = v;
   novo->ant = NULL;
   if(fila->inicio == NULL){
       fila->inicio = novo;
       fila->fim = novo;
   }else{
       fila->inicio->ant = novo;
       fila->inicio= novo;
   }
}
void removerDaFila(fila* fila){
    if(fila->fim != NULL){
       noFila* temp = fila->fim;
       fila->fim = temp->ant;
   }
}
int filaVazia(fila* fila){
    if(fila->fim == NULL){
        return 1;
    }
    return 0;
}
void imprimirFila(fila* fila){
    noFila* cursor = fila->fim;
    while(cursor->ant != NULL){
        printf("%c\n", cursor->noVertice->letra);
        cursor = cursor->ant;
    }
     printf("%c\n", cursor->noVertice->letra);
}
//---------------------------------Grafo--------------------------------

grafo* criarGrafo(int nmrV,int nmrA){
    grafo* g = (grafo*)malloc(sizeof(grafo)); //aloquei memoria para o struct
    g->nmrVertices = nmrV;
	g->nmrArestas = nmrA;
    g->lista_v = inicializarLista();
	g->lista_arestas = inicializarLista();
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
void addAresta(grafo* gr,char v1,char v2, int peso){ //grafo dirigido
    no* cursor;
	aresta* a = inicializarAresta();

    for(cursor = gr->lista_v->inicial;cursor!=NULL; cursor=cursor->prox){
        if(cursor->noVertice->letra==v1){
            if(buscarVertice(v2,gr->lista_v)){
                vertice* novo = retornarVertice(v2,gr->lista_v);
				a->inicial = cursor->noVertice;
				a->final = novo;
				a->peso = peso;
                inserirNaLista(cursor->noVertice->adj, novo);
                inserirArestaNaLista(gr->lista_arestas,a);
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
             printf("%c\t ", cursor2->noVertice->letra);
        }
        printf("\n");
    }

}

void imprimirArestas(grafo* gr){
	no* cursor;
	for(cursor=gr->lista_arestas->inicial; cursor!=NULL;cursor=cursor->prox){
		printf("%c%c %d %d %c\n",cursor->noAresta->inicial->letra,cursor->noAresta->final->letra, cursor->noAresta->inicial->dist,cursor->noAresta->final->dist,cursor->noAresta->final->pai->letra);
	}
}

int bellmanFord(grafo* g, char origem){
    int i;
    no* cursor;
     for(cursor=g->lista_arestas->inicial;cursor!=NULL;cursor=cursor->prox){
         if(cursor->noAresta->inicial->letra==origem || cursor->noAresta->final->letra==origem ){
             cursor->noAresta->inicial->dist=0;
         }
     }
    for(i=1;i<g->nmrVertices-1;i++){
        for(cursor=g->lista_arestas->inicial;cursor!=NULL;cursor=cursor->prox){
            if(cursor->noAresta->final->dist > cursor->noAresta->inicial->dist + cursor->noAresta->peso){
                cursor->noAresta->final->dist  = cursor->noAresta->inicial->dist + cursor->noAresta->peso;
                cursor->noAresta->final->pai = cursor->noAresta->inicial;
            }
        }
    }
     for(cursor=g->lista_arestas->inicial;cursor!=NULL;cursor=cursor->prox){
         if(cursor->noAresta->final->dist > cursor->noAresta->inicial->dist + cursor->noAresta->peso){
            return 0;
         }
     }
     return 1;

}


