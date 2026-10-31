#include <stdint.h>
#include "stm32f4xx.h"

#define GPIOCEN (1U << 2)
#define GPIOAEN (1U << 0)

#define PIN_0 (1U << 0)
#define LED_PIN_SET (1U << 13)
#define LED_PIN_RESET (1U << 29)


int main(void)
{
    /* Enable GPIOC and GPIOA clock */
    RCC->AHB1ENR |= GPIOCEN ;   // GPIOC
    RCC->AHB1ENR |= GPIOAEN ;   // GPIOA

    /* PC13 as output */
    GPIOC->MODER &= ~(3U << (13 * 2));
    GPIOC->MODER |=  (1U << (13 * 2));


    /* PA0 as input */
    GPIOA->MODER &= ~(3U << (0 * 2));

    while (1)
    {
        if (!(GPIOA->IDR & (1U << 0)))
        {
            /* PA0 = 0 → LED ON */
            GPIOC->BSRR = LED_PIN_SET ;
        }
        else
        {
            /* PA0 = 1 → LED OFF */
            GPIOC->BSRR = LED_PIN_RESET ;
        }
    }
}
