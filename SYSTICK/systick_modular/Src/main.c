#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"

#include "uart.h"

char key;

int main(void)
{
	 RCC->AHB1ENR |= (1U << 0); ;   // GPIOC


	    /* PC13 as output */
	  GPIOC->MODER &= ~(3U << (13 * 2));
	  GPIOC->MODER |=  (1U << (13 * 2));

	    /* PA0 as input */
	  GPIOA->MODER &= ~(3U << (0 * 2));


    uart_init();

    while (1)
    {
    	key = uart_read();
      if(key == '1'){
    	  GPIOA->BSRR |= (1U << 13);

      }
      else{
    	  GPIOA->BSRR |= (1U << 29);
      }
    }
}

