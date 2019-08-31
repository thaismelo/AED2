#include <stdio.h>
#include <stdlib.h>
#include "funcoesBST.h"
#include "implementacoes.c"


int main(int argc, char* argv[])
{
    int op;
    no *raiz= NULL;
    
    while(1==1){
      scanf("%d", &op);
      int valor;
      switch (op)
      {
      case 1:
        scanf("%d",&valor);
        raiz = inserir(raiz,valor);
        break;
      case 2:
        preOrder(raiz);
        printf("\n");
        break;
      case 3:
        inOrder(raiz);
        printf("\n");
        break;
      case 4:
        posOrder(raiz);
        printf("\n");
        break;
      case 5:
        scanf("%d",&valor);
        raiz = remover(raiz,valor);
        break;
      case 6:
        printf("[%d]\n",maiorDescendente(raiz));
        break;
      case 7:
        printf("[%d]\n",menorDescendente(raiz));
        break;
      case 8:
        printf("%d\n", altura(raiz));
        break;
      case 9:
        scanf("%d", &valor);
        printf("%d\n", paiDoElemento(raiz,valor));
        break;
      case 10:
        scanf("%d", &valor);
        printf("%d\n", sucessorDoElemento(raiz,valor));
        break;
      case 11:
        scanf("%d", &valor);
        printf("%d\n", antecessorDoElemento(raiz,valor));
        break;
      case 999:
        exit(0);
      }
    }
    


    return 0;
}
