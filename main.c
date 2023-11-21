#include "leitorArquivo.h"
#include "comandos.h"
#include "cenario.h"

#include <stdio.h>
#include <stdlib.h>

int main(){
    comandos comandos = lerArquivo("entrada.txt");
    cenario cenario;
    inserirComandos( comandos, &cenario );
    iniciarSimulacao( &cenario );
    return 0;
}