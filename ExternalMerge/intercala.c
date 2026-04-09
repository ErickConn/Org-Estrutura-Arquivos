#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 8

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

int compara (const void *e1, const void *e2){
    return strncmp(((Endereco *)e1)->cep, ((Endereco *)e2)->cep, 8);
}

int main(int argc, char *argv[]){
    FILE * a, *b, *saida;
    Endereco *ea;

    a = fopen("cep.dat", "rb");
    if (a == NULL){
        fprintf(stderr, "Erro na abertura do arquivo");
        exit(1);
    }

    char nomeArq[30];
    fseek(a, 0, SEEK_END);
    long tamanho = ftell(a);
    rewind(a);
    long registros = tamanho / sizeof(Endereco);
    int qtb = registros/N;
    int resto = registros % 8;                                                                                                  
    ea = (Endereco *) malloc(sizeof(Endereco) * (qtb+1));

    for(int i = 0; i < N; i++){
        int qt = qtb + (i < resto? 1 : 0);
        fread(ea, sizeof(Endereco)*qt, 1, a);
        qsort(ea, qt, sizeof(Endereco), compara);
        sprintf(nomeArq, "cep-%d.dat", i);
        saida = fopen(nomeArq, "wb");
        fwrite(ea, sizeof(Endereco) * qt, 1, saida);
        fclose(saida);
    }

    free(ea);
    fclose(a);

    int prox = 0, ultimo = N;

    while(prox < ultimo - 1){
        char nomeArq1[30];
        char nomeArq2[30];
        char nomeArq3[30];
        sprintf(nomeArq1, "cep-%d.dat", prox);
        sprintf(nomeArq2, "cep-%d.dat", prox+1);
        sprintf(nomeArq3, "cep-%d.dat", ultimo);
        FILE *a = fopen(nomeArq1, "rb");
        FILE *b = fopen(nomeArq2, "rb");
        FILE *saida = fopen(nomeArq3, "wb");
        Endereco ea, eb;

        fread(&ea, sizeof(Endereco), 1, a);
        fread(&eb, sizeof(Endereco), 1, b);

        while(!feof(a) && !feof(b)){
            if(compara(&ea, &eb) <= 0){
                fwrite(&ea, sizeof(Endereco), 1, saida);
                fread(&ea, sizeof(Endereco), 1, a);
            }else {
                fwrite(&eb, sizeof(Endereco), 1, saida);
                fread(&eb, sizeof(Endereco), 1, b);
            }
        }

        while(!feof(a)){
            fwrite(&ea, sizeof(Endereco), 1, saida);
            fread(&ea, sizeof(Endereco), 1, a);
        }

        while(!feof(b)){
            fwrite(&eb, sizeof(Endereco), 1, saida);
            fread(&eb, sizeof(Endereco), 1, b);
        }
    
        fclose(a);
        fclose(b);
        fclose(saida);

        prox = prox +2;
        ultimo++;
    }


    return 0;
}