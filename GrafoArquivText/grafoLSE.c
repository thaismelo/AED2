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

listaAdjacencia** criarLista(int nmrV){
    listaAdjacencia* lista = (listaAdjacencia*)malloc(sizeof(listaAdjacencia)); //aloquei memoria para o struct
    lista->nmrVertices = nmrV;
    lista->verticesVizinhos = (lista**) malloc(sizeof(lista*)*nmrV);
    
    int i;
    for(i=0; i<nmrV;i++){
        lista->verticesVizinhos[i] = (lista*)malloc(sizeof(lista));
    }

    return lista;
}

void addVertices(lista* l, char vertice){
    if(l==NULL){
        lista* blocoNovo = (lista*)malloc(sizeof(lista);
        blocoNovo->vertice = vertice;
        blocoNovo->prox=NULL;
    }else{
        lista* aux;
        for(aux = l; aux!=NULL;aux=aux->prox){
            if(aux->prox == NULL){
                lista* blocoNovo = (lista*)malloc(sizeof(lista);
                blocoNovo->vertice = vertice;
                blocoNovo->prox=NULL;
                aux->prox=blocoNovo;
            }
        }
    }
}
/*
void addVizinho(lista* l, char a1,char a2, char vertices[]){
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
*/
void mostrarLista(lista* l){
    lista* cursor;
    for(cursor=l;cursor!=NULL;cursor= cursor->prox){
        printf("%c\n", cursor->vertice);
    }
}
int main(void){

    FILE *file;
    file = fopen("inf.txt", "r");

    if(file == NULL){
        printf("n foi possivel abrir o arquivo\n");
        exit(0);
    }

    int v,a,i,j;
    fscanf(file, "%d %d", &v,&a); //pegando tamanho dos vertices e arestas

    listaAdjacencia** dimensao = criarLista(v); //declarando tamanho do vetor de vertices
    
    char vertice,lixo,a1,a2;

    for(i = 0; i<v; i++){ //pegando cada vertice do arquivo e colocando numa lista na posicao de dimensao
        fscanf(file, "%c %c",&lixo,&vertice);
        addVertices(dimensao[v],vertice);
    }
   
    printf("\n%d %d\n", v,a);
    
    for(i = 0; i<v; i++){
        mostrarLista(dimensao[v]);
    }
    
   
    fclose(file);


}

