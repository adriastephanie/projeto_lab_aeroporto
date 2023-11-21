#include "cenario.h"
#include "comandos.h"
#include "logger.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ESPERANDO 1
#define VOANDO 2
#define ATERISSANDO 3

comandos _comandos;

void imprimir_dados_aeronave(aeronave * a){
    printf("%s\t",a->codigo);
    escrever_log_string("%s\t",a->codigo);
    printf("%.2f\t",a->distancia);
    escrever_log_decimal("%f\t",a->distancia);
    printf("%.2f\t",a->distancia_percorrida);
    escrever_log_decimal("%f\t",a->distancia_percorrida);
    printf("%d\t",a->velocidade);
    escrever_log_numero("%f\t",a->velocidade);
    printf("%d\n",a->estado);
    escrever_log_numero("%d\n",a->estado);
}

void mostrarAvioes( cenario * cenario ){
    char str[20];
    printf("Cenário\n");
    escrever_log("Cenário\n");

    printf("N pistas: %d\n",cenario->numero_pistas);
    escrever_log_numero("N pistas: %d\n", cenario->numero_pistas);

    printf("Tempestade: %d\n",cenario->tempestade);
    escrever_log_numero("Tempestade: %d\n",cenario->tempestade);

    printf("Neblina: %d\n",cenario->neblina);
    escrever_log_numero("Neblina: %d\n",cenario->neblina);

    printf("Turbulencia: %d\n",cenario->turbulencia);
    escrever_log_numero("Turbulencia: %d\n",cenario->turbulencia);

    printf("Aeronaves na pista:\n");
    escrever_log("Aeronaves na pista:\n");
    aeronaveNaFila * af = cenario->fila;
    while( af != NULL ){
        if( af->aeronave->estado == ESPERANDO ){
            imprimir_dados_aeronave( af->aeronave );
        }
        af = af->proximo;
    };
    printf("Aeronaves voando:\n");
    escrever_log("Aeronaves voando:\n");
    af = cenario->fila;
    while( af != NULL ){
        if( af->aeronave->estado == VOANDO ){
            imprimir_dados_aeronave( af->aeronave );
        }
        af = af->proximo;
    };
    printf("Aeronaves aterissando:\n");
    escrever_log("Aeronaves aterissando:\n");
    af = cenario->fila;
    while( af != NULL ){
        if( af->aeronave->estado == ATERISSANDO ){
            imprimir_dados_aeronave( af->aeronave );
        }
        af = af->proximo;
    };
}

int pegarNumero(char comando[100]){
    char * pch = strrchr(comando,' ');
    int posicao = pch-comando+1;   
    return atoi( strndup(comando+posicao, 1 ) );
}

cenario * inserirAviaoNaFila( aeronave * a, cenario * cenario ){
    aeronaveNaFila * afAtual = cenario->fila;
    aeronaveNaFila * novaAeronave = malloc(sizeof(aeronaveNaFila));
    novaAeronave->aeronave = a;
    // printf("##%s\n",a->codigo);
    // printf("##%s\n",novaAeronave->aeronave->codigo);
    // printf("&&%x\n",afAtual);
    if( afAtual == NULL ){
        // printf("if\n");
        afAtual = novaAeronave;
        cenario->fila = afAtual;
        // printf("&&%x\n",afAtual);
        // printf("##%s\n",afAtual->aeronave->codigo);s
    }else{
        // printf("while\n");
        while( afAtual->proximo != NULL ){
            afAtual = afAtual->proximo;
        }
        afAtual->proximo = novaAeronave;
        //cenario->fila = afAtual;
    }
    // printf("acabou\n");
    return cenario;
}

cenario * processarInserirAviao( char comando[100], cenario * cenario ){
    int posicaoFinal = strrchr(comando,')')-comando+1;
    char * valores = strndup(comando+12, posicaoFinal );
    char separador = ',';

    aeronave * a = malloc( sizeof(aeronave) );
    char *token = strtok(valores, &separador);

    token = strtok(NULL, &separador);
    strcpy(a->codigo, strndup(token+1,strlen(token)));

    token = strtok(NULL, &separador);
    strcpy(a->modelo, strndup(token+1,strlen(token)));

    token = strtok(NULL, &separador);
    strcpy(a->destino, strndup(token+1,strlen(token)));

    token = strtok(NULL, &separador);
    a->distancia = atof( strndup(token+1,strlen(token)) );
    a->distancia_percorrida = 0.0;

    token = strtok(NULL, &separador);
    a->tempo_de_voo = atof( strndup(token+1,strlen(token)) );
    
    a->latitude = 0.0;
    a->longitude = 0.0;
    a->altura = 0.0;
    a->velocidade = 0.0;
    a->estado = ESPERANDO;

    // printf(">>%x\n",cenario->fila );
    cenario = inserirAviaoNaFila( a, cenario );
    // printf("%x\n",cenario->fila );
    // printf("**%s\n",a->codigo);
    // printf("**%s\n",cenario->fila->aeronave->codigo);
    return cenario;
}

cenario * decolarProximoAviao( cenario * cenario ){
    aeronaveNaFila * af = cenario->fila;
    while( af != NULL ){
        if( af->aeronave->estado == ESPERANDO ){
            af->aeronave->estado = VOANDO;
            af->aeronave->velocidade = 300;
            af->aeronave->distancia_percorrida += 300;
            af->aeronave->altura = 1000;
            break;
        }
        af = af->proximo;
    }
    return cenario;
}

cenario * moverAvioes( cenario * cenario ){
    aeronaveNaFila * af = cenario->fila;
    while( af != NULL ){
        if( af->aeronave->estado == VOANDO ){
            if( ( rand() % 10 ) < 5 && cenario->tempestade == 0 ){
                af->aeronave->altura += -0.3;
                af->aeronave->velocidade = af->aeronave->velocidade*0.9;
            }else if( ( rand() % 10 ) < 5 && cenario->neblina == 0 ){
                af->aeronave->altura += -0.5;
                af->aeronave->velocidade = af->aeronave->velocidade*0.95;
            }else if( ( rand() % 10 ) < 5 && cenario->tempestade == 0 ){
                af->aeronave->velocidade = af->aeronave->velocidade*0.85;
            }else{
                af->aeronave->velocidade = 600;
                af->aeronave->distancia_percorrida += 600;
                af->aeronave->latitude += 600;
            }
            if( af->aeronave->distancia_percorrida > af->aeronave->distancia*0.9){
                af->aeronave->estado = ATERISSANDO;
            }
            break;
        }
        af = af->proximo;
    }
    return cenario;
}

cenario * aplicarTempestade( cenario * cenario ){
    
    return cenario;
}

cenario * processarComando(char comando[100], cenario * cenario){
    if( strncmp (comando,"pistas",6) == 0){
        cenario->numero_pistas = pegarNumero( comando );
    }else if( strncmp (comando,"insere_aviao",12) == 0){
        cenario = processarInserirAviao( comando, cenario );
    }else if( strncmp (comando,"decolar",7) == 0){
        cenario = decolarProximoAviao( cenario );
    }else if( strncmp (comando,"tempestade",10) == 0){
        cenario->tempestade = pegarNumero( comando );
    }else if( strncmp (comando,"neblina",7) == 0){
        cenario->neblina = pegarNumero( comando );
    }else if( strncmp (comando,"turbulencia",11) == 0){
        cenario->turbulencia = pegarNumero( comando );
    }else if( strncmp (comando,"iniciasimulacao",15) == 0){
        cenario->passos_simulacao = pegarNumero( comando );
    }
    return cenario;
}

void inserirComandos( comandos comandos, cenario * cenario ){
    cenario->fila = 0;
    limpar_arquivo();
    for(int i = 0; i < comandos.posicoesOcupadas; i++){
        cenario = processarComando( comandos.comandos[ i ], cenario );
    }
    mostrarAvioes( cenario );
}

void iniciarSimulacao(cenario * cenario){
    printf("Iniciando a simulação\n");
    escrever_log("Iniciando a simulação\n");
    for (int i = 0; i < cenario->passos_simulacao; i++){
        printf("Avançando estado\n");
        escrever_log("Avançando estado\n");
        cenario = avancarEstado( cenario );
        mostrarAvioes( cenario );
    }
    
}
cenario * avancarEstado(cenario * cenario){
    cenario = moverAvioes( cenario );
    cenario->tempestade += -1;
    cenario->neblina += -1;
    cenario->turbulencia += -1;
    return cenario;
}