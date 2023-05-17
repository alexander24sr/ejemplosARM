#include <stdint.h>
#include <stdio.h>
#include "incFiles/stm32f103x6.h"
#include "hcsr04/hcsr04.h"
#include "serialUart/serialUart.h"
#include <stdlib.h>
#include <string.h>


int main()
{
    inicializarUart();
    inicializarSensor();
    while(1)
    {
        char mensajeInicial[100] = "Se han leido los pulsos: ";
        char numStr[8];
        uint32_t distanciaSensor = leerDistancia();
        sprintf(numStr,"%d",distanciaSensor);
        strcat(mensajeInicial,numStr);
        enviarPalabra(mensajeInicial);
        for(int i = 0;i < 200000; i++);
    }
    return 0;
}