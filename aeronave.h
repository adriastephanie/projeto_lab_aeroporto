#ifndef AERONAVE_H
#define AERONAVE_H

struct aeronave{
    char codigo[3];
    char modelo[30];
    char destino[30];
    double distancia;
    double distancia_percorrida;
    double tempo_de_voo;
    double latitude;
    double longitude;
    double altura;
    int velocidade;
    int estado;
};

typedef struct aeronave aeronave;
#endif
