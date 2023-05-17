//sudo apt-get install arm-none-eabi-gcc
//sudo apt-get install st-tools

#include <stdint.h>

#define RCC_BASE 0x40021000
#define GPIOA_BASE 0x40010800
#define GPIOB_BASE 0x40010C00
#define ADC1_BASE 0x40012400
#define TIM4_BASE 0x40000800

#define RCC_APB2ENR (*((unsigned int*) (RCC_BASE + 0x18)))
#define RCC_APB1ENR (*((unsigned int*) (RCC_BASE + 0x1C)))
#define GPIOA_CRL (*((unsigned int*) (GPIOA_BASE + 0x00)))
#define GPIOB_CRH (*((unsigned int*) (GPIOB_BASE + 0x04)))

#define ADC1_CR2 (*((unsigned int*) (ADC1_BASE + 0x08)))
#define ADC1_CR1 (*((unsigned int*) (ADC1_BASE + 0x04)))
#define ADC1_SQR1 (*((unsigned int*) (ADC1_BASE + 0x2C)))
#define ADC1_SQR3 (*((unsigned int*) (ADC1_BASE + 0x34)))
#define ADC1_SMPR2 (*((unsigned int*) (ADC1_BASE + 0x10)))
#define ADC1_SR (*((unsigned int*) (ADC1_BASE + 0x00)))
#define ADC1_DR (*((unsigned int*) (ADC1_BASE + 0x4C)))

#define TIM4_PSC (*((unsigned int*) (TIM4_BASE + 0x28)))
#define TIM4_ARR (*((unsigned int*) (TIM4_BASE + 0x2C)))
#define TIM4_CCR4 (*((unsigned int*) (TIM4_BASE + 0x40)))
#define TIM4_CCMR2 (*((unsigned int*) (TIM4_BASE + 0x1C)))
#define TIM4_BDTR (*((unsigned int*) (TIM4_BASE + 0x44)))
#define TIM4_CCER (*((unsigned int*) (TIM4_BASE + 0x20)))
#define TIM4_CR1 (*((unsigned int*) (TIM4_BASE + 0x00)))

int main(void)
{
	//Habilitacion del ADC, puerto A, puerto B
	RCC_APB2ENR |= (1<<2)|(1<<9)|(1<<3)|(1<<0);

	//Habilitacion del timer4
	RCC_APB1ENR |= (1<<2);

	//Configuracion del puerto PA2 como entrada
	GPIOA_CRL &= ~(0xF << 8);

	//Configuracion del puerto PB9 como salida alterna
	GPIOB_CRH &= ~(0xF << 4);
	GPIOB_CRH |= (0xA<<4);

	//Configuracion del timer
	TIM4_PSC = 7;

	// PARA ARR = 20000 - PERIODO PWM ES 10ms -- Para un PSC = 3
	// Para un PSC = 7 - FrecuenciaTimer = 1 Mhz - Arr=20000 - Frecuencia de 50Hz - Periodo de 20ms
	// PARA ARR = 40000 - PERIODO PWM ES 20ms - Para un preescalador = 3
	TIM4_ARR = 20000; 
	TIM4_CCR4 = 10000;

	TIM4_CCMR2 |= (0x68<<8);
	TIM4_BDTR |= (1<<15);
	TIM4_CCER |= (1<<12);
	TIM4_CR1 |= (1<<7)|(1<<0);

	ADC1_CR2 &= ~(0x1 << 0);

	ADC1_SQR1 &= ~(0xFFFFFF);

	ADC1_SQR3 &= ~(0x3FFFFFFF);
	ADC1_SQR3 |= (0x2 << 0);

	ADC1_CR1 &= ~((0xFFFFF) | (0xC << 20));
	ADC1_SMPR2 &= ~(0X7 << 6);
	ADC1_CR2 |= (1 << 0);

	while(1)
	{
		//ADC1_CR2 |= (1 << 0);
		//ADC1_CR2 |= (1 << 22);

		//while(!(ADC1_SR & (1<<1)));

		//uint16_t valorADC = ADC1_DR & 0xFFF;

		//ADC1_SR &= ~(1 << 1);

	}

}