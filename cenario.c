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
    //imprime o código da aeronave e faz o log 
    printf("%s\t",a->codigo);
    escrever_log_string("%s\t",a->codigo);

    //imprime a distância da aeronave e faz o log 
    printf("%.2f\t",a->distancia);
    escrever_log_decimal("%f\t",a->distancia);

    //imprime a distância percorrida da aeronave e faz o log
    printf("%.2f\t",a->distancia_percorrida);
    escrever_log_decimal("%f\t",a->distancia_percorrida);

    //imprime a velocidade da aeronave 
    printf("%d\t",a->velocidade);
    escrever_log_numero("%f\t",a->velocidade);

    //imprime o estado da aeronave
    printf("%d\n",a->estado);
    escrever_log_numero("%d\n",a->estado);
}

void mostrarAvioes( cenario * cenario ){
    char str[20];
    printf("Cenário\n");
    escrever_log("Cenário\n");

    //imprime o número de pistas no cenário e log
    printf("N pistas: %d\n",cenario->numero_pistas);
    escrever_log_numero("N pistas: %d\n", cenario->numero_pistas);

    //imprime o status da tempestade no cenário e no log
    printf("Tempestade: %d\n",cenario->tempestade);
    escrever_log_numero("Tempestade: %d\n",cenario->tempestade);

    //imprime o status da neblina no cenário e no log
    printf("Neblina: %d\n",cenario->neblina);
    escrever_log_numero("Neblina: %d\n",cenario->neblina);

    //imprime o status da turbulencia no cenário e no log
    printf("Turbulencia: %d\n",cenario->turbulencia);
    escrever_log_numero("Turbulencia: %d\n",cenario->turbulencia);

    printf("Aeronaves na pista:\n");
    escrever_log("Aeronaves na pista:\n");

    //lista de aeronaves na fila e imprime detalhes se estão esperando na pista
    aeronaveNaFila * af = cenario->fila;
    while( af != NULL ){
        if( af->aeronave->estado == ESPERANDO ){
            imprimir_dados_aeronave( af->aeronave );
        }
        af = af->proximo;
    };
    printf("Aeronaves voando:\n");
    escrever_log("Aeronaves voando:\n");
    //lista de aeronaves na fila e imprime detalhes se estão voando 
    af = cenario->fila;
    while( af != NULL ){
        if( af->aeronave->estado == VOANDO ){
            imprimir_dados_aeronave( af->aeronave );
        }
        af = af->proximo;
    };
    // lista de aeronaves na fila e imprime detalhes se estão aterrissando.
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
// funcao para extrair um número de um comando que termina em branco
int pegarNumero(char comando[100]){
     // percorre e acha a última ocorrência de um espaço em branco no comando
    char * pch = strrchr(comando,' ');
    //calcula a posição do espaço em branco no comando e adiciona 1 para obter a posição do primeiro caractere do número
    int posicao = pch-comando+1;   
    //usa a função strndup para criar uma cópia da parte do comando contendo o número (1 caractere)
    //converte a string em um número inteiro usando atoi e retorna o resultado.
    return atoi( strndup(comando+posicao, 1 ) );
}

cenario * inserirAviaoNaFila( aeronave * a, cenario * cenario ){
    //ponteiero para o nó atual na lista de aeronaves
    aeronaveNaFila * afAtual = cenario->fila;
    // alocacao espaço para um novo nó de aeronave na lista
    aeronaveNaFila * novaAeronave = malloc(sizeof(aeronaveNaFila));
    // atribuiundo a aeronave ao novo nó
    novaAeronave->aeronave = a;
    // printf("##%s\n",a->codigo);
    // printf("##%s\n",novaAeronave->aeronave->codigo);
    // printf("&&%x\n",afAtual);

     // codicao de se a lista de aeronaves está vazia
    if( afAtual == NULL ){
        // printf("if\n");
        afAtual = novaAeronave; // o nó atual é o novo nó.
        cenario->fila = afAtual; // a lista agora começa com o novo nó 
        // printf("&&%x\n",afAtual);
        // printf("##%s\n",afAtual->aeronave->codigo);s
    }else{ 
        // printf("while\n");

        // caso a lista de aeronaves não está vazia, percorre até o final da lista
        while( afAtual->proximo != NULL ){
            afAtual = afAtual->proximo;
        }
        // adicioina o novo nó ao final da lista
        afAtual->proximo = novaAeronave;
        //cenario->fila = afAtual;
    }
    // printf("acabou\n");
    return cenario;
}

// funcao para processar o comando de inserção de uma nova aeronave no cenário

cenario * processarInserirAviao( char comando[100], cenario * cenario ){

     // para encontrar a posicao do ultimo parêntese na string de comando
    int posicaoFinal = strrchr(comando,')')-comando+1;
    // tirar  os valores entre os parênteses
    char * valores = strndup(comando+12, posicaoFinal );
    // define o caractere separador como virgula
    char separador = ',';

    // aloca a memória para uma nova estrutura de aeronave
    aeronave * a = malloc( sizeof(aeronave) );
     // Utiliza a funcao de strtok para dividir a string de valores com base no separador
    char *token = strtok(valores, &separador);

    // Pula o primeiro, pois é a posição da aeronave
    token = strtok(NULL, &separador);
    // vai copiar o código da aeronave da string para a estrutura
    strcpy(a->codigo, strndup(token+1,strlen(token)));

     // vai repetir o processo para os demais atributos da aeronave
    token = strtok(NULL, &separador);
    strcpy(a->modelo, strndup(token+1,strlen(token)));

    token = strtok(NULL, &separador);
    strcpy(a->destino, strndup(token+1,strlen(token)));

    token = strtok(NULL, &separador);

     // converte a string para um valor numérico (que é a distância) e atribui à estrutura
    a->distancia = atof( strndup(token+1,strlen(token)) );
    a->distancia_percorrida = 0.0;

    token = strtok(NULL, &separador);
    // cpnverte a string para um valor numérico (tempo de voo) e atribui à estrutura
    a->tempo_de_voo = atof( strndup(token+1,strlen(token)) );
    

    // Iniciainicializa outros atributos da aeronave que temos
    a->latitude = 0.0;
    a->longitude = 0.0;
    a->altura = 0.0;
    a->velocidade = 0.0;
    a->estado = ESPERANDO;

    // printf(">>%x\n",cenario->fila );

    // chamkando a funcao para inserir a aeronave na fila do cenario
    cenario = inserirAviaoNaFila( a, cenario );
    // printf("%x\n",cenario->fila );
    // printf("**%s\n",a->codigo);
    // printf("**%s\n",cenario->fila->aeronave->codigo);

    // faz o retorno do ponteiro para o cenário atualizado
    return cenario;
}

// funcao para decolar a próxima aeronave na fila de espera
cenario * decolarProximoAviao( cenario * cenario ){
    // inicializando o ponteiro para a lista de aeronaves no cenário
    aeronaveNaFila * af = cenario->fila;

    // loop para percorrer a lista de aeronaves
    while( af != NULL ){
        // if para /verificar se a aeronave está aguardando para decolar
        if( af->aeronave->estado == ESPERANDO ){
            // mudanca do estado da aeronave para VOANDO
            af->aeronave->estado = VOANDO;
            // define a velocidade da aeronave como 300 
            af->aeronave->velocidade = 300;
            // adiciona a distância percorrida da aeronave em 300 
            af->aeronave->distancia_percorrida += 300;
            // define a altitude da aeronave como 1000 
            af->aeronave->altura = 1000;
            // saida do loop
            break;
        }
        // vai para o próximo nó na lista de aeronaves
        af = af->proximo;
    }
    return cenario;
}

// funcao para mover aeronaves no cenário
cenario * moverAvioes( cenario * cenario ){
     // inicializando o ponteiro para a lista de aeronaves no cenário
    aeronaveNaFila * af = cenario->fila;
    // loop para percorrer a lista de aeronaves
    while( af != NULL ){
        // verifica se a aeronave está voando
        if( af->aeronave->estado == VOANDO ){
            // faz a verificacao das condições do tempo e ajusta a altitude e velocidade da aeronave.
            if( ( rand() % 10 ) < 5 && cenario->tempestade == 0 ){
                af->aeronave->altura += -0.3; // Reduz a altitude da aeronave em 0.3 unidades
                af->aeronave->velocidade = af->aeronave->velocidade*0.9; //Reduz a velocidade da aeronave em 10% do que temos
            }else if( ( rand() % 10 ) < 5 && cenario->neblina == 0 ){
                af->aeronave->altura += -0.5; //reduz a altitude da aeronave em 0.5 unidades.
                af->aeronave->velocidade = af->aeronave->velocidade*0.95; //reduz a velocidade da aeronave em 5%
            }else if( ( rand() % 10 ) < 5 && cenario->tempestade == 0 ){
                af->aeronave->velocidade = af->aeronave->velocidade*0.85; //reduz a velocidade da aeronave em 15%
            }else{
                af->aeronave->velocidade = 600; //colocar a velocidade da aeronave como 600
                af->aeronave->distancia_percorrida += 600; //incrementa a distância percorrida da aeronave em 600 
                af->aeronave->latitude += 600; ///incrementa a latitude da aeronave em 600
            }
            //faz a verificacao se a aeronave percorreu mais de 90% da distância total
            if( af->aeronave->distancia_percorrida > af->aeronave->distancia*0.9){
                //Define o estado da aeronave como "aterrissando" 
                af->aeronave->estado = ATERISSANDO;
            }
            break;
        }
        //próximo nó na lista encadeada de aeronaves
        af = af->proximo;
    }
    return cenario;
}

cenario * aplicarTempestade( cenario * cenario ){
    
    return cenario;
}

// funcao para processar comandos e atualizar o cenário
cenario * processarComando(char comando[100], cenario * cenario){
    // verifica se o comando é relacionado ao número de pistas
    // Esta função compara os primeiros 6 caracteres da string comando com os primeiros 6 caracteres da string literal "pistas". 
    //A função strncmp retorna zero se as strings forem iguais, onde entra o == 0 para processar
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

// funcao para inserir comandos em um cenário
void inserirComandos( comandos comandos, cenario * cenario ){
    // inicia a lista de aeronaves no cenário como zero
    cenario->fila = 0;
     // limpa o arquivo de log antes de inserir novos comandos
    limpar_arquivo();

    // loop para processar cada comando presente na estrutura comandos
    for(int i = 0; i < comandos.posicoesOcupadas; i++){
         // chamando a função para processar o comando e atualizar o cenário
        cenario = processarComando( comandos.comandos[ i ], cenario );
    }
    // chamando a função para mostrar as informações das aeronaves no cenário atual
    mostrarAvioes( cenario );
}

void iniciarSimulacao(cenario * cenario){
    //imprime 
    printf("Iniciando a simulação\n");
    // escreve a mesma mensagem no log
    escrever_log("Iniciando a simulação\n");
    // Loop para avançar o estado da simulação pelo número de passos especificado.
    for (int i = 0; i < cenario->passos_simulacao; i++){
        printf("Avançando estado\n");
        escrever_log("Avançando estado\n");
        // chamando a função para avançar o estado do cenário
        cenario = avancarEstado( cenario );
         // chamando a função para mostrar as informações das aeronaves no cenário atual
        mostrarAvioes( cenario );
    }
    
}
cenario * avancarEstado(cenario * cenario){
     // avança o estado das aeronaves no comando cenario
    cenario = moverAvioes( cenario );
     // está reduzindo o estado de tempestade, neblina e turbulência em 1 unidade de simulação no estado
    cenario->tempestade += -1; //  ou cenario->tempestade--;
    cenario->neblina += -1;
    cenario->turbulencia += -1;
    return cenario;
}