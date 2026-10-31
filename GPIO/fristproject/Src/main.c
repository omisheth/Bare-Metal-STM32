
#include <stdint.h>

#define RCC_BASE 0x40023800UL
#define GPIOC_BASE 0x40020800UL

#define RCC_AHB1ENR *(volatile uint32_t*)(RCC_BASE + 0x30)
#define GPIOC_MODER *(volatile uint32_t*)(GPIOC_BASE + 0x00)
#define GPIOC_ODR *(volatile uint32_t*)(GPIOC_BASE + 0x14)

void delay(void)
{
    for(volatile uint32_t i = 0; i < 1000000; i++)
    {
    }
}

int main(void)
{
	RCC_AHB1ENR |= (1U << 2);

	GPIOC_MODER &= ~(3U << (13*2));
	GPIOC_MODER |= (1U << (13*2));

	GPIOC_ODR |= (1U << 13);


	while (1)
	    {
		 /* LED ON */
		GPIOC_ODR &= ~(1U << 13);
        delay();

        /* LED OFF */
        GPIOC_ODR |= (1U << 13);
        delay();
	    }
	}



