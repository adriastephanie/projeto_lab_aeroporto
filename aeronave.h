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

//EXISTE 2 METODOS DE DECLARAR STRUCT 
// #include<stdio.h>

// struct Point{
//   int x;
//   int y;
// };
// typedef struct Point Coisa;
// int main() {
//     Coisa p1;
//     p1.x = 1;
//     p1.y = 3;
//     printf("%d \n", p1.x);
//     printf("%d \n", p1.y);
//     return 0;
// }