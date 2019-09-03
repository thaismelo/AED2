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
                int cresceu;
                case 1:
                     scanf("%d ", &n);
                     raiz = inserir(raiz, n, &cresceu);        
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
                case 999:
                    exit(0);
            }

        }

}
