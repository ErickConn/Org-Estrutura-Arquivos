#include <stdio.h>
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


int main(int argc, char* argv[]){
    FILE* file;
    Endereco e;
    int encontrado = 0;
    long inicio, fim;
    long tamanho;
    long meio;
    int count;

    if(argc != 2){
        fprintf(stderr, "Formato invalido, use: %s [CEP]", argv[0]);
        return 1;
    }

    file = fopen("cep_ordenado.dat", "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    fseek(file,0,SEEK_END);
    tamanho = ftell(file);

    long totalDeRegistros = tamanho / sizeof(Endereco);
    count = 0;
    inicio = 0;
    fim = totalDeRegistros -1;

    while (inicio <= fim) {
        count++;
        meio = (inicio + fim) / 2;

        fseek(file, meio * sizeof(Endereco), SEEK_SET);
        fread(&e, sizeof(Endereco), 1, file);

        int cmp = strncmp(argv[1], e.cep, 8);
       printf("Tentativa %d: Comparando [%s] com [%.8s] no indice %ld\n", 
            count+1, argv[1], e.cep, meio);

        if (cmp == 0) {
            printf("Registro Encontrado\n");
            printf("Rua:    %.72s\n", e.logradouro);
            printf("Bairro: %.72s\n", e.bairro);
            printf("Cidade: %.72s\n", e.cidade);
            printf("UF:     %.72s\n", e.uf);
            printf("Sigla:  %.2s\n", e.sigla);
            printf("CEP:    %.8s\n", e.cep);
            printf("---------------------------\n");
            printf("Busca concluida em %d saltos.\n", count);
            encontrado = 1;
            break; 
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    if (!encontrado) {
        printf("CEP %s nao encontrado apos %d tentativas.\n", argv[1], count);
    }
    fclose(file);
    return 0;
}
