#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "list.c"

int main(int argc, char *argv[]) {
    FILE *file;
    file = fopen("inf.txt", "r");

    if(file == NULL){
        printf("n foi possivel abrir o arquivo\n");
        exit(0);
    }

    int v,a,i,j,peso;
    fscanf(file,"%d %d", &v,&a); //pegando tamanho dos vertices e arestas
    grafo* gr = criarGrafo(v,a);

    char vertice,lixo,a1,a2;

    for(i = 0; i<v; i++){ //pegando cada vertice do arquivo e colocando numa lista na posicao de dimensao
        fscanf(file, "%c %c",&lixo,&vertice);
        addVertices(gr,vertice);
    }
   
    for(j=0; j<a;j++){ //pegando as arestas
        fscanf(file,"%c %c%c %d",&lixo,&a1,&a2,&peso);
        addAresta(gr,a1,a2,peso);
    }
    imprimirListaADJ(gr);
    printf("\n");
    printf("%d\n",bellmanFord(gr,'C'));
    imprimirArestas(gr);
    fclose(file);
}