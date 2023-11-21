#include "logger.h"

#include <stdio.h>
#include <stdlib.h>

void limpar_arquivo(){
    FILE *arquivo;
    arquivo = fopen("log.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao escrever log.\n");
        exit(0);
    }
    fprintf(arquivo, "%s","");
    fclose(arquivo);
}

void escrever_log( char * conteudo ){
    FILE *arquivo;
    arquivo = fopen("log.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao escrever log.\n");
        exit(0);
    }
    fprintf(arquivo,"%s", conteudo);
    fclose(arquivo);
}

void escrever_log_numero( char * conteudo, int numero ){
    FILE *arquivo;
    arquivo = fopen("log.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao escrever log.\n");
        exit(0);
    }
    fprintf(arquivo, conteudo, numero);
    fclose(arquivo);
}


void escrever_log_decimal( char * conteudo, double numero ){
    FILE *arquivo;
    arquivo = fopen("log.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao escrever log.\n");
        exit(0);
    }
    fprintf(arquivo, conteudo, numero);
    fclose(arquivo);
}
void escrever_log_string( char * conteudo, char * str ){
    FILE *arquivo;
    arquivo = fopen("log.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao escrever log.\n");
        exit(0);
    }
    fprintf(arquivo, conteudo, str);
    fclose(arquivo);
}