#ifndef LOGGER_H
#define LOGGER_H

void limpar_arquivo();
void escrever_log( char * conteudo );
void escrever_log_numero( char * conteudo, int numero );
void escrever_log_decimal( char * conteudo, double numero );
void escrever_log_string( char * conteudo, char * str );
#endif