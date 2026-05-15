# Organização de Estruturas de Arquivos - Trabalhos P1

Este repositório contém as implementações desenvolvidas até a primeira prova do curso, com foco em manipulação de arquivos, busca binária e algoritmos de ordenação externa. 

## 📂 Estrutura do Repositório

Cada projeto está isolado em seu próprio diretório para facilitar a organização e a compilação:

```
├── BuscaBinaria/
├── Indice/
├── ExternalMerge/
└── Outros/
```

---

## 📝 Descrição dos Trabalhos

### 1. Busca Binária em Arquivo de CEP Ordenado (`/buscabinaria.c`)
Programa implementado em C que realiza a busca binária diretamente em um arquivo binário de CEPs previamente ordenado, acessando os registros através de saltos e deslocamentos de bytes no disco para encontrar o endereço correspondente de forma otimizada.

### 2. Criação e Uso de Índice (`/indice.c`)
Implementação de um sistema de indexação para otimizar buscas. O fluxo de execução consiste em:
1. Ler o arquivo de dados original e criar uma nova estrutura na memória contendo apenas o **CEP** e a **posição (byte offset)** correspondente.
2. Ordenar essa estrutura de índice.
3. Salvar o índice ordenado em um novo arquivo físico.
4. Realizar a busca binária no arquivo de índice.
5. Utilizar a posição encontrada no índice para recuperar os dados completos diretamente do arquivo original.

### 3. Ordenação Externa com K Blocos (`/intercala-revisado.c`)
Algoritmo de ordenação externa focado no processamento de grandes volumes de dados que não cabem inteiramente na memória RAM. O processo segue o modelo de Intercalação (Merge):
1. **Divisão:** O arquivo principal é dividido em `k` blocos (potências de 2).
2. **Ordenação Interna:** Cada bloco é lido para a memória, ordenado individualmente e salvo novamente em arquivos temporários.
3. **Intercalação:** Os arquivos de bloco ordenados são combinados dois a dois de forma iterativa, até que reste apenas um único arquivo final completamente ordenado.

---

## 🚀 Como Executar

Para compilar e executar os códigos de cada pasta, navegue até o diretório desejado e utilize seu compilador (ex: `gcc`):

```bash
# Exemplo para compilar a busca binária
cd BuscaBinaria
gcc -o buscaBinaria.c buscaBinaria
./buscaBinaria
