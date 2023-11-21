#include "leitorArquivo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

comandos lerArquivo( char * nomeArquivo ){
    comandos comandos;
    comandos.posicoesOcupadas = 0;
    int linhaAtual = 0;
    FILE *arq;
    char linha[100];
    char *result;
    arq = fopen(nomeArquivo, "rt");

    if (arq == NULL){
        printf("Problemas na abertura do arquivo\n");
        exit(0);
    }

    while (!feof(arq))
    {
        result = fgets(linha, 100, arq);
        if (result){
            strcpy(comandos.comandos[linhaAtual], result);
            comandos.posicoesOcupadas = linhaAtual;
            linhaAtual++;
        }
    }
    fclose(arq);
    return comandos;
}