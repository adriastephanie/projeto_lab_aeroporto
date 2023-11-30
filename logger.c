#include "logger.h"

#include <stdio.h>
#include <stdlib.h>

// funcao para limpar o conteúdo do arquivo de log
void limpar_arquivo(){
    FILE *arquivo;
    // Abre o arquivo em modo de escrita e vai removendo o conteúdo anterior
    arquivo = fopen("log.txt", "w");
// faz a verificacao de erro, se houve erro na abertura do arquivo
    if (arquivo == NULL) {
        printf("Erro ao escrever log.\n");
        exit(0);
    }
    // escreve uma string vazia no arquivo
    fprintf(arquivo, "%s","");
    // fechar o arquivo
    fclose(arquivo);
}

void escrever_log( char * conteudo ){
    FILE *arquivo;
    // abre o arquivo em modo de escrita
    arquivo = fopen("log.txt", "a");
 // faz a verificacao se houve erro na abertura do arquivo
    if (arquivo == NULL) {
        printf("Erro ao escrever log.\n");
        exit(0);
    }
    // vai escrever o conteúdo
    fprintf(arquivo,"%s", conteudo);
    // fechar o arquivo
    fclose(arquivo);
}

void escrever_log_numero( char * conteudo, int numero ){
    FILE *arquivo;
    arquivo = fopen("log.txt", "a");
 // faz a verificacao se houve erro na abertura do arquivo
    if (arquivo == NULL) {
        printf("Erro ao escrever log.\n");
        exit(0);
    }
    // vai escrever o conteúdo
    fprintf(arquivo, conteudo, numero);
    // fechar o arquivo
    fclose(arquivo);
}

// funcao para escrever um número decimal no arquivo de log
void escrever_log_decimal( char * conteudo, double numero ){
    FILE *arquivo;
    // abre o arquivo em modo de escrita
    arquivo = fopen("log.txt", "a");
    // faz a verificacao se houve erro na abertura do arquivo
    if (arquivo == NULL) {
        printf("Erro ao escrever log.\n");
        exit(0);
    }
     // vai escrever o conteúdo
    fprintf(arquivo, conteudo, numero);
    // fechar o arquivo
    fclose(arquivo);
}

// funcao para escrever uma string no arquivo de log
void escrever_log_string( char * conteudo, char * str ){
    FILE *arquivo;
    // abre o arquivo em modo de escrita
    arquivo = fopen("log.txt", "a");
    // faz a verificacao se houve erro na abertura do arquivo
    if (arquivo == NULL) {
        printf("Erro ao escrever log.\n");
        exit(0);
    }

    // vai escrever o conteúdo formatado com a string no arquivo
    fprintf(arquivo, conteudo, str);

    // fechar o arquivo
    fclose(arquivo);
}