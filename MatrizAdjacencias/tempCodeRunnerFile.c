
    for(i = 0; i<v; i++){
        printf("v[%d]: %c ",i,g->vertices[i]);
    }

    imprimirGrafo(g);
    buscaEmLargura(g,'A');
    fclose(file);


}
