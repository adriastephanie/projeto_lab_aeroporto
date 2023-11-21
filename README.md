# Simulação de aeronave Projeto LAB

Projeto de simulação de um sistema de controle aéreo

## RODAR

Use the package manager [pip](https://pip.pypa.io/en/stable/) to install foobar.

```bash
gcc *.c -o aeroporto 
```

```bash
gcc main.c leitorArquivo.c logger.c cenario.c -o main 
```

```bash
./main
```

gcc: Este é o comando para invocar o compilador GCC.

*.c: Isso é um padrão de seleção de arquivos. *.c significa "todos os arquivos que terminam com .c". Ele seleciona todos os arquivos de código-fonte C no diretório atual

-o aeroporto: Isso especifica o nome do arquivo de saída do programa compilado. Neste caso, o executável resultante será chamado "aeroporto".

main.c leitorArquivo.c logger.c cenario.c: São os nomes dos arquivos de código-fonte do projeto que serão compilados

-o main: Isso especifica o nome do arquivo de saída do programa compilado. Neste caso, o executável resultante será chamado "main".


## Descrição


Faça a leitura do arquivo “entrada.txt” (que contém os comandos) e transforme os elementos
do cenário na estrutura de dados que achar mais conveniente (listas simples, lista de listas, listas
com cabeça, entre outras).

Ao final da simulação emitir um relatório, criando um arquivo de log com as informações escrita do log.txt:
- Registre e apresente as colisões que foram evitadas.
- Quais aviões chegaram antes do tempo previsto? Apresente um cenário onde isso acontece.
- Quais aviões chegaram atrasados em relação tempo previsto? Apresente um cenário onde isso
acontece.
- Registre também para cada avião o tempo previsto de voo, o tempo real do voo e as
intercorrências durante o voo.



## License

[MIT](https://choosealicense.com/licenses/mit/)