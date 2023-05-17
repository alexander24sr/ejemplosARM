#include "hcsr04.h"

//PC13 como salida y PC14 como entrada
void inicializarSensor(void)
{
    RCC->APB2ENR |= (1<<4);
    GPIOC->CRH &= ~(0xFF << 20);
    GPIOC->CRH |= (0x3 << 20);
    GPIOC->CRH |= (0x4 << 24);
    GPIOC->ODR &= ~(1<<13);
}

uint32_t leerDistancia()
{
    SysTick->CTRL &= ~((1<<0)|(1<<1));
    SysTick->VAL &= ~(0xFFFFFF);
    SysTick->LOAD &= ~(0xFFFFFF);
    SysTick->LOAD |= 80;
    SysTick->CTRL |= (1<<2);
    GPIOC->ODR |= (1<<13);
    SysTick->CTRL |= (1<<0);
    while((SysTick->CTRL & (1<<16)) == 0);
    GPIOC->ODR &= ~(1<<13);
    SysTick->CTRL &= ~((1<<0)|(1<<1));
    SysTick->VAL &= ~(0xFFFFFF);
    SysTick->LOAD &= ~(0xFFFFFF);
    SysTick->LOAD |= 8000000;
    SysTick->CTRL |= (1<<2);
    SysTick->CTRL |= (1<<0);
    while(((GPIOC->IDR & (1<<14)) == 0) & ((SysTick->CTRL & (1<<16)) == 0));
    if((GPIOC->IDR & (1<<14)) != 0)
    {
        SysTick->CTRL &= ~((1<<0)|(1<<1));
        SysTick->VAL &= ~(0xFFFFFF);
        SysTick->LOAD &= ~(0xFFFFFF);
        SysTick->LOAD |= 8000000;
        SysTick->CTRL |= (1<<2);
        SysTick->CTRL |= (1<<0);
        while(((GPIOC->IDR & (1<<14)) != 0) & ((SysTick->CTRL & (1<<16)) == 0));
        if((GPIOC->IDR & (1<<14)) == 0)
        {
            uint32_t pulsos = SysTick->VAL & 0xFFFFFF;
            SysTick->CTRL &= ~((1<<0)|(1<<1));
            return (8000000 - pulsos);
        }
        else
        {
            return 1;
        }

    }
    else
    {
        return 0;
    }

}