#ifndef COMANDOS_H
#define COMANDOS_H

// Definição de uma estrutura comandos
struct comandos{
    int posicoesOcupadas;  // número de posições ocupadas no array de comandos.
    char comandos[30][100];  // matriz para armazenar os comandos
};

// Definição de um tipo de dado comandos usando a estrutura criada
typedef struct comandos comandos;

#endif  // Fim do bloco de inclusão condicional COMANDOS_H
