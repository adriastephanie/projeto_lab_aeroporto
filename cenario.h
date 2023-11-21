#ifndef CENARIO_H
#define CENARIO_H

#include "comandos.h"
#include "aeronave.h"

#include <stdbool.h>

struct aeronaveNaFila{
    aeronave * aeronave;
    struct aeronaveNaFila * proximo;
};
typedef struct aeronaveNaFila aeronaveNaFila;

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