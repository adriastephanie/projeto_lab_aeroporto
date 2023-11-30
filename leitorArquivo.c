#include "leitorArquivo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para ler comandos de um arquivo e armazenar na estrutura comandos
comandos lerArquivo( char * nomeArquivo ){
    comandos comandos; // estrutura para armazenar comandos lidos do arquivo
    comandos.posicoesOcupadas = 0; // inicialização do número de posições ocupadas

    int linhaAtual = 0; // variável para rastrear a linha atual do arquivo
    FILE *arq; // ponteiro para o arquivo
    char linha[100]; // vetor de char para armazenar uma linha do arquivo
    char *result; // ponteiro para o resultado da leitura da linha

    arq = fopen(nomeArquivo, "rt"); // abertura do arquivo em modo de leitura 

    if (arq == NULL){
        printf("Problemas na abertura do arquivo\n");
        exit(0); // Saída do programa em caso de problemas na abertura do arquivo
    }

    // loop para ler cada linha do arquivo
    while (!feof(arq))
    {
        result = fgets(linha, 100, arq); // leitura de uma linha do arquivo

        if (result){
            strcpy(comandos.comandos[linhaAtual], result); // copia a linha lida para a estrutura comandos
            comandos.posicoesOcupadas = linhaAtual; // atualiza o número de posições ocupadas
            linhaAtual++; // avança para a próxima posição array do comandos
        }
    }

    fclose(arq); // fecha o arquivo após a leitura
    return comandos; // retorna a estrutura com os comandos lidos 
}
