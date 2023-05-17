#include <stdint.h>
#include "incFiles/stm32f103x6.h"

void gpio_init(void)
{
    RCC->APB2ENR |= (1<<4);
    GPIOC->CRH &= ~(0xF << 20);
    GPIOC->CRH |= (0x2 << 20);
}

void systick_init()
{
    SysTick->VAL &= ~(0xFFFFFF);
    SysTick->VAL |= 1000000;
    SysTick->LOAD &= ~(0xFFFFFF);
    SysTick->LOAD |= 1000000;
    SysTick->CTRL &= ~((1 << 1)|(1 << 0));
    SysTick->CTRL |= (1<<2);
}

void delay_s(void)
{
    SysTick->VAL &= ~(0xFFFFFF);
    SysTick->VAL |= 1000000;
    SysTick->LOAD &= ~(0xFFFFFF);
    SysTick->LOAD |= 1000000;
    SysTick->CTRL |= (1<<0);
    while((SysTick->CTRL & (1<<16)) == 0);
    SysTick->CTRL &= ~(1<<0);
    SysTick->CTRL |= (1<<2);
}

int main()
{
    gpio_init();
    systick_init();
    while(1)
    {
        GPIOC->ODR |= (1 << 13);
        delay_s();
        GPIOC->ODR &= ~(1<<13);
        delay_s();
    }
    return 0;
}