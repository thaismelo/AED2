#include <stdio.h>
#include <stdlib.h>
#include "rb.h"
#include "rb.c"


int main(int argc, char *argv[]) {
        int op;

       arvore nova;
       inicializar(&nova);


        while(1==1) {
            scanf("%d", &op);
            switch(op) {
                int n;
                case 1:
                     scanf("%d ", &n);
                     inserir(&nova, n);        
                     break;
                case 2:
                    preOrder(nova);
                    printf("\n");                    
                    break;
                case 999:
                    exit(0);
            }

        }

}
