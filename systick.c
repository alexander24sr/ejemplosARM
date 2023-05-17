#include <stdint.h>

#define RCC_BASE 0x40021000
#define GPIOC_BASE 0x40011000

#define RCC_APB2ENR (*((unsigned int*) (RCC_BASE + 0x18)))

#define SYSTICK_CTRL (*((unsigned int*) (0xE000E010)))
#define SYSTICK_LOAD (*((unsigned int*) (0xE000E014)))
#define SYSTICK_CURRENT (*((unsigned int*) (0xE000E018)))

typedef struct
{
    uint32_t CRL;
    uint32_t CRH;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t BRR;
    uint32_t LCKR;
}GPIO_TypeDef;

#define GPIOC ((GPIO_TypeDef *) GPIOC_BASE)

void gpio_init(void)
{
    RCC_APB2ENR |= (1<<4);
    GPIOC->CRH &= ~(0xF << 20);
    GPIOC->CRH |= (0x2 << 20);
}

void systick_init()
{
    SYSTICK_CURRENT &= ~(0xFFFFFF);
    SYSTICK_CURRENT |= 1000000;
    SYSTICK_LOAD &= ~(0xFFFFFF);
    SYSTICK_LOAD |= 1000000;
    SYSTICK_CTRL &= ~((1 << 1)|(1 << 0));
    SYSTICK_CTRL |= (1<<2);
}

void delay_s(void)
{
    SYSTICK_CURRENT &= ~(0xFFFFFF);
    SYSTICK_CURRENT |= 1000000;
    SYSTICK_LOAD &= ~(0xFFFFFF);
    SYSTICK_LOAD |= 1000000;
    SYSTICK_CTRL |= (1<<0);
    while((SYSTICK_CTRL & (1<<16)) == 0);
    SYSTICK_CTRL &= ~(1<<0);
    SYSTICK_CTRL |= (1<<2);
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