#include "ArvoreB.h"
#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char** argv)
{
    FILE *f = fopen("cep-2.dat", "rb");
    FILE *s = fopen("cep-join.dat", "wb");
    Endereco e;
    ArvoreB* a = ArvoreB_Abre("arvore.dat");
    char chave[TAM_CHAVE+1];
    long posicao;
    int qtd;
    qtd = fread(&e, sizeof(Endereco), 1, f);
    while (qtd > 0){
        posicao = ArvoreB_Busca(a, e.cep);
        if (posicao != -1){
            fwrite(&e, sizeof(Endereco), 1, s);
        }
        qtd = fread(&e, sizeof(Endereco), 1, f);
    }
    ArvoreB_Fecha(a);
    fclose(f);
    fclose(s);
    return 0;
}
