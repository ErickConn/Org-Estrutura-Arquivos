#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int main() {
    Endereco e;
    int qt;
    FILE * f = fopen("cep.dat", "rb");
    qt = fread(&e, sizeof(Endereco), 1, f);
    srand(time(NULL));
    FILE *s = fopen("cep-2.dat", "wb");
    while (qt > 0){
        float random_num = 1.0*rand()/RAND_MAX;
        if (random_num < 0.8){
            fwrite(&e, sizeof(Endereco), 1, s);
        }
        qt = fread(&e, sizeof(Endereco), 1, f);
    }
    fclose(f);
    fclose(s);
    return 0;
}
