#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int comparaCEP(const void *e1, const void *e2){
    return strcmp(((Endereco*)e1)->cep,  ((Endereco*)e2)->cep);
}

int main(int argc, char *argv[]){
    FILE *f;
    FILE *d1;
    FILE *d2;
    long tamanho, registros, meio, resto;

    if(argc != 2){
        fprintf(stderr, "Erro na chamada do programa, uso: %s. [origem]", argv[0]);
        exit(1);
    }

    f = fopen(argv[1], "rb");
    if(f == NULL){
        fprintf(stderr, "Erro na abertura do arquivo origem.");
        exit(1);
    }
    d1 = fopen("cep-ordenado-1.dat", "wb");
    if(d1 == NULL){
        fprintf(stderr, "Erro na abertura do primeiro arquivo destino.");
        exit(1);
    }
    d2 = fopen("cep-ordenado-2.dat", "wb");
    if(d2 == NULL){
        fprintf(stderr, "Erro na abertura do segundo arquivo destino.");
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    tamanho = ftell(f);
    registros = tamanho / sizeof(Endereco);
    meio = registros / 2;
    rewind(f);

    Endereco *v1 = (Endereco*) malloc(meio * sizeof(Endereco));
    fread(v1, sizeof(Endereco), meio, f);
    qsort(v1, meio, sizeof(Endereco), comparaCEP);
    fwrite(v1, sizeof(Endereco), meio, d1);
    free(v1);

    resto = registros - meio;
    Endereco *v2 = (Endereco*) malloc(resto * sizeof(Endereco));
    fread(v2, sizeof(Endereco), resto, f);
    qsort(v2, resto, sizeof(Endereco), comparaCEP);
    fwrite(v2, sizeof(Endereco), resto, d2);
    free(v2);
        
    fclose(f);
    fclose(d1);
    fclose(d2);

    return 0;
}