#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "avl.c"

int main(int argc, char *argv[]) {
        int op;

       no * raiz=NULL;


        while(1==1) {
            scanf("%d", &op);
            switch(op) {
                int n;
                int flag;
                case 1:
                     scanf("%d ", &n);
                     raiz = inserir(raiz, n, &flag);        
                     break;
                case 2:
                    preOrder(raiz);
                    printf("\n");                    
                    break;
                case 3:
                    scanf("%d ", &n);
                    raiz = remover(raiz,n,&flag);
                    break;
                case 999:
                    exit(0);
            }

        }

}
