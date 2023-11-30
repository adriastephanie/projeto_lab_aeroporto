#ifndef CENARIO_H
#define CENARIO_H

#include "comandos.h"
#include "aeronave.h"
// biblioteca para usar tipo de dado bool e os valores true e false
#include <stdbool.h>

// lista encadeada simples 
//cada nó representa uma aeronave na fila do cenário
struct aeronaveNaFila{
    aeronave * aeronave; //ponteiro para estrutura aeronave
    struct aeronaveNaFila * proximo; //ponteiro para o próximo nó na lista.
};
typedef struct aeronaveNaFila aeronaveNaFila;

//utiliza essa lista encadeada aeronaveNaFila
//manter o rastreamento de aeronaves
struct cenario{
    int numero_pistas;
    int tempestade;
    int neblina;
    int turbulencia;
    int passos_simulacao;
    aeronaveNaFila * fila;
};
typedef struct cenario cenario;

void inserirComandos( comandos comandos, cenario * cenario );
void iniciarSimulacao(cenario * cenario);
cenario * avancarEstado(cenario * cenario);
#endif