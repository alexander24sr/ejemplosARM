#include <stdint.h>

#define RCC_BASE 0x40021000
#define GPIOA_BASE 0x40010800
#define USART1_BASE 0x40013800

#define RCC_APB2ENR (*((unsigned int*) (RCC_BASE + 0x18)))
#define GPIOA_CRH (*((unsigned int*) (GPIOA_BASE + 0x04)))

#define USART1_SR (*((unsigned int*) (USART1_BASE + 0x00)))
#define USART1_DR (*((unsigned int*) (USART1_BASE + 0x04)))
#define USART1_BRR (*((unsigned int*) (USART1_BASE + 0x08)))
#define USART1_CR1 (*((unsigned int*) (USART1_BASE + 0x0C)))
#define USART1_CR2 (*((unsigned int*) (USART1_BASE + 0x10)))
#define USART1_CR3 (*((unsigned int*) (USART1_BASE + 0x14)))
#define USART1_GTPR (*((unsigned int*) (USART1_BASE + 0x18)))

void enviarCaracter(uint8_t caracter)
{
    while(!(USART1_SR & (1<<7)));
    USART1_DR &= ~(0xF);
    USART1_DR |= caracter;
    while(!(USART1_SR & (1<<6)));
}

void nuevaLinea()
{
    while(!(USART1_SR & (1<<7)));
    USART1_DR &= ~(0xF);
    USART1_DR |= '\n';
    while(!(USART1_SR & (1<<6)));
}

void enviarPalabra(uint8_t cadena[])
{
    uint8_t i = 0;
    for(i=0;cadena[i] != '\0'; i++)
    {
        enviarCaracter(cadena[i]);
    }
    nuevaLinea();
}

int main()
{
    //Habilitacion de senhal de reloj
    RCC_APB2ENR |= (1<<0)|(1<<2)|(1<<14);

    //Configuracion del modo de operacion en PA9 y PA10
    GPIOA_CRH &= ~(0xFF << 4);
    GPIOA_CRH |= (1<<10)|(1<<5)|(1<<7);

    USART1_BRR |= (0x34<<4);
    USART1_BRR |= (1<<0);
    USART1_CR1 |= (1<<2)|(1<<3)|(1<<13);

    while(1)
    {
        enviarPalabra("Esto es programacion de ARM");
        for(int i = 0; i<2000000;i++);
    }
    return 0;
}
