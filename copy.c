#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    FILE* fO;
    FILE* fD;
    int qtd;
    char buffer[4096];
    if(argc!= 3){
        fprintf(stderr, "Formato inválido, uso: %s [arquivo origem] [arquivo destino]", argv[0]);
        exit(1);
    }
    fO = fopen(argv[1], "rb");
    fD = fopen(argv[2], "wb");
    if(fO == NULL || fD == NULL){
        fprintf(stderr, "Erro na abertura dos arquivos");
        exit(1);
    }
    qtd = fread(buffer, sizeof(char), 4096, fO);
    while(qtd > 0){
        fwrite(buffer, sizeof(char), qtd, fD);
        qtd = fread(buffer, sizeof(char), 4096, fO);
    }
    fclose(fO);
    fclose(fD);
    return 0;
}