
#include <stdint.h>

#define RCC_BASE 0x40023800UL
#define GPIOC_BASE 0x40020800UL

#define RCC_AHB1ENR *(volatile uint32_t*)(RCC_BASE + 0x30)


typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];


}GPIOC_TypeDef;

#define GPIOC ((GPIOC_TypeDef *)GPIOC_BASE)

void delay(void)
{
    for(volatile uint32_t i = 0; i < 1000000; i++)
    {
    }
}

int main(void)
{
	RCC_AHB1ENR |= (1U << 2);

    GPIOC->MODER &= ~(3U << (13*2));
	GPIOC->MODER |= (1U << (13*2));

	GPIOC->ODR|= (1U << 13);


	while (1)
	    {
		 /* LED ON */
		GPIOC->ODR &= ~(1U << 13);
        delay();

        /* LED OFF */
        GPIOC->ODR |= (1U << 13);
        delay();
	    }
	}



