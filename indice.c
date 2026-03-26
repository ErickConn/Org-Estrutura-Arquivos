#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Endereco {
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2]; 
} Endereco;

typedef struct _indiceEndereco {
    char cep[8];
    unsigned int posicao;
} indiceEndereco;

int comparaCEPS(const void *c1, const void *c2) {
    indiceEndereco *i1 = (indiceEndereco *)c1;
    indiceEndereco *i2 = (indiceEndereco *)c2;
    return strncmp(i1->cep, i2->cep, 8);
}

int main() {
    FILE *f, *idx_file;
    indiceEndereco *a;
    long tamanhoRegistros;
    int c = 0;

    f = fopen("cep.dat", "rb");

    fseek(f, 0, SEEK_END);
    tamanhoRegistros = ftell(f) / sizeof(Endereco);
    rewind(f);

    a = (indiceEndereco*) malloc(tamanhoRegistros * sizeof(indiceEndereco));

    idx_file = fopen("indice_ordenado", "rb");

    if (idx_file) {
        fread(a, sizeof(indiceEndereco), tamanhoRegistros, idx_file);
        c = (int)tamanhoRegistros;
        fclose(idx_file);
    } else {
        Endereco e;
        while (fread(&e, sizeof(Endereco), 1, f) > 0) {
            strncpy(a[c].cep, e.cep, 8);
            a[c].posicao = c;
            c++;
        }
        
        qsort(a, c, sizeof(indiceEndereco), comparaCEPS);

        idx_file = fopen("indice_ordenado", "wb");
        fwrite(a, sizeof(indiceEndereco), c, idx_file);
        fclose(idx_file);
    }

    char buscaCEP[9];
    printf("\nDigite o CEP: ");
    scanf("%8s", buscaCEP);

    int inicio = 0, fim = c - 1, meio, count = 0, achou = 0;

    while (inicio <= fim) {
        count++;
        meio = (inicio + fim) / 2;
        int comp = strncmp(a[meio].cep, buscaCEP, 8);

        if (comp == 0) {
            fseek(f, (long)a[meio].posicao * sizeof(Endereco), SEEK_SET);
            Endereco res;
            fread(&res, sizeof(Endereco), 1, f);

            printf("\n--- DADOS ENCONTRADOS ---\n");
            printf("Rua:    %.72s\n", res.logradouro);
            printf("Cidade: %.72s\n", res.cidade);
            printf("Buscas realizadas: %d\n", count);
            achou = 1;
            break;
        } else if (comp > 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    if (!achou) 
        printf("CEP nao encontrado apos %d buscas.\n", count);

    free(a);
    fclose(f);
    return 0;
}