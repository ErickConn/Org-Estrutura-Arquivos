# Organização de Estruturas de Arquivos - Trabalhos P1 e P2

Este repositório contém as implementações desenvolvidas ao longo do curso, com foco em manipulação de arquivos, busca binária, algoritmos de ordenação externa, processamento de CSV e índices com Árvore-B.

## 📂 Estrutura do Repositório

Cada projeto está isolado em seu próprio diretório para facilitar a organização e a compilação:

```
├── BuscaBinaria/
├── Indice/
├── ExternalMerge/
├── Outros/
├── ProcessamentoCSV/
└── IndiceArvoreB/
```

---

## 📝 Trabalhos da P1

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

## 📝 Trabalhos da P2

### 4. Processamento de CSV (`/ProcessamentoCSV/`)

Parser de arquivos CSV implementado em C usando um autômato de estados finitos (máquina de transição de estados — `mte`). Suporta corretamente campos entre aspas, caracteres especiais dentro de aspas e separadores `,`.

**Arquivos:**
- `CSVParser.h` — Interface pública: definição da struct `CSVParser` e assinatura das funções.
- `CSVParser.c` — Implementação do parser via tabela de transição de estados (`mte[estado][char]`). A função `CSVParser_processLines` percorre o input byte a byte, acumulando campos no buffer interno e disparando um callback por linha completa.
- `main.c` — Ponto de entrada (atualmente vazio; a ser preenchido com a lógica de aplicação sobre o arquivo `owid-covid-data.csv`).

**Funcionamento:**
1. `CSVParser_init` inicializa o estado do parser e aponta `fields[0]` para o início do buffer.
2. `CSVParser_processLines` recebe um bloco de bytes e processa carácter a carácter: campos simples, campos entre aspas e newlines disparam ações distintas via a tabela `mte`.
3. Ao final de cada linha, o callback fornecido pelo usuário é invocado com o array de ponteiros `fields` e a contagem `fieldCount`.

### 5. Índice com Árvore-B (`/IndiceArvoreB/`)

Implementação completa de uma Árvore-B persistida em arquivo binário, usada para indexar registros de CEP e realizar junção (join) entre dois arquivos de dados.

**Arquivos:**
- `ArvoreB.h` — Interface: structs `ArvoreB`, `ArvoreB_Cabecalho`, `ArvoreB_Elemento` e `ArvoreB_Pagina`; protótipos das funções públicas.
- `ArvoreB.c` — Implementação completa: abertura/criação do arquivo de índice em modo binário (`rb`/`rb+`/`wb`), inserção recursiva com split de página, busca recursiva e debug print.
- `ArvoreB-Busca.c` — Variante standalone com `main` para busca pontual por chave via linha de comando (`argv[1]`). 
- `aleatorio.c` — Gera o arquivo `cep-2.dat` selecionando ~80% dos registros do `cep.dat` original de forma aleatória (semente por `time(NULL)`).
- `insere.c` — Lê o arquivo `cep-1.dat` e insere cada registro na Árvore-B (`arvore.dat`), armazenando o CEP como chave e a posição do registro como valor.
- `join.c` — Realiza o join entre `cep-2.dat` e a árvore construída a partir de `cep-1.dat`: para cada registro de `cep-2.dat`, busca o CEP na árvore; se encontrado, grava o registro em `cep-join.dat`.

**Fluxo geral:**
```
cep.dat ──(aleatorio.c)──► cep-2.dat
cep-1.dat ──(insere.c)──► arvore.dat (Árvore-B)
cep-2.dat + arvore.dat ──(join.c)──► cep-join.dat
```

---

## 🚀 Como Executar

Para compilar e executar os códigos de cada pasta, navegue até o diretório desejado e utilize seu compilador (ex: `gcc`):

```bash
# Exemplo para compilar a busca binária
cd BuscaBinaria
gcc -o buscaBinaria buscaBinaria.c
./buscaBinaria
