#include <stdio.h>
#include <stdlib.h>
#include "listaAdjacencia.h"
#include "grafoLista.c"

int main(int argc, char *argv[]) {
    FILE *file;
    file = fopen("inf.txt", "r");

    if(file == NULL){
        printf("n foi possivel abrir o arquivo\n");
        exit(0);
    }

    int v,a,i,j;
    fscanf(file, "%d %d", &v,&a); //pegando tamanho dos vertices e arestas
    grafo* gr = criarGrafo(v);

    char vertice,lixo,a1,a2;

    for(i = 0; i<v; i++){ //pegando cada vertice do arquivo e colocando numa lista na posicao de dimensao
        fscanf(file, "%c %c",&lixo,&vertice);
        addVertices(gr,vertice);
    }
   
    for(j=0; j<a;j++){ //pegando as arestas
        fscanf(file, "%c %c%c",&lixo,&a1,&a2);
        addAresta(gr,a1,a2);
    }
    imprimirListaADJ(gr);
   /* char origem;
    printf("\n Digite um vertice de origem:\n");
    scanf("%c", &origem);
    buscaEmLargura(gr,origem);
    imprimirListaPosBusca(gr);
    */
    buscaEmProfundidade(gr,0);
   // imprimirListaPosBuscaProf(gr);
    fclose(file);
}