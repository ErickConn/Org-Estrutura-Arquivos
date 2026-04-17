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

int comparaCEP (const void *e1, const void *e2) {
    return strncmp(((Endereco *)e1)->cep, ((Endereco *)e2)->cep, 8);
}

int main(int argc, char *argv[]) {
    FILE *f, *saida;
    int prox = 0; 
    int ult = N;
    Endereco e1, e2;
    
    f = fopen("cep.dat", "rb");
    if (f == NULL) {
        fprintf(stderr, "Erro na abertura do arquivo!\n");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long tamanho = ftell(f);
    rewind(f);
    char nome[30];
    int qtdR = tamanho / sizeof(Endereco);
    int qtdB = qtdR / N;
    int resto = qtdR % N;
    Endereco *e = (Endereco *) malloc(sizeof(Endereco) * (qtdB + 1));
    
    for(int i = 0; i < N; i++){
        int qtd = qtdB + (i < resto ? 1 : 0);
        fread(e, sizeof(Endereco), qtd, f);
        qsort(e, qtd, sizeof(Endereco), comparaCEP);
        sprintf(nome, "cep-%d.dat", i);
        saida = fopen(nome, "wb");
        fwrite(e, sizeof(Endereco), qtd, saida);
        fclose(saida);
    }
    free(e);
    fclose(f);

    while (prox < ult - 1) {
        char nome1[30];
        char nome2[30];
        char nome3[30];
        FILE *f1, *f2, *f3;
        sprintf(nome1, "cep-%d.dat", prox);
        sprintf(nome2, "cep-%d.dat", prox + 1);
        sprintf(nome3, "cep-%d.dat", ult);
        f1 = fopen(nome1, "rb");
        f2 = fopen(nome2, "rb");
        f3 = fopen(nome3, "wb");

        fread(&e1, sizeof(Endereco), 1, f1);
        fread(&e2, sizeof(Endereco), 1, f2);

        while (!feof(f1) && !feof(f2)) {
            if (comparaCEP(&e1, &e2) < 0) {
                fwrite(&e1, sizeof(Endereco), 1, f3);
                fread(&e1, sizeof(Endereco), 1, f1);
            } else if (comparaCEP(&e1, &e2) > 0) { 
                fwrite(&e2, sizeof(Endereco), 1, f3);
                fread(&e2, sizeof(Endereco), 1, f2);
            } else {
                fwrite(&e1, sizeof(Endereco), 1, f3);
                fread(&e1, sizeof(Endereco), 1, f1);
                fread(&e2, sizeof(Endereco), 1, f2);
            }
        }

        while(!feof(f1)){
            fwrite(&e1, sizeof(Endereco), 1, f3);
            fread(&e1, sizeof(Endereco), 1, f1);
        }
        
        while(!feof(f2)){
            fwrite(&e2, sizeof(Endereco), 1, f3);
            fread(&e2, sizeof(Endereco), 1, f2);
        }

        fclose(f1);
        fclose(f2);
        fclose(f3);

        prox += 2;
        ult++;
    }
    return 0;
}