#include <stdint.h>
#include "stm32f4xx.h"


#define GPIOAEN        (1U << 0)
#define UART2EN        (1U << 17)

#define PERIPHERALCLK  16000000U
#define BAUDRATE       115200U

#define TXEN           (1U << 3)
#define RXEN           (1U << 2)
#define UARTEN         (1U << 13)
#define SR_TXE         (1U << 7)
#define SR_RXEN         (1U << 7)

void uart_send_ch(int ch);

static uint16_t compute_baud_rate(uint32_t PeriphClk,
                                  uint32_t BaudRate);
int __io_putchar(int ch){
	uart_send_ch(ch);
			return ch;
}
void uart_init(){
	  /* Enable GPIOA clock */
	    RCC->AHB1ENR |= GPIOAEN;




	    /* Clear PA2 mode bits */
	    GPIOA->MODER &= ~(3U << (2 * 2));
	    GPIOA->MODER |= (2U << (2 * 2));

	    GPIOA->MODER &= ~(3U << (2 * 3));
	  	GPIOA->MODER |= (2U << (2 * 3));


	    GPIOA->AFR[0] &= ~(1U << 11);
	    GPIOA->AFR[0] |= (1U << 10);
	    GPIOA->AFR[0] |= (1U << 9);
	    GPIOA->AFR[0] |= (1U << 8);

	    GPIOA->AFR[0] &= ~(1U << 15);
	   	GPIOA->AFR[0] |= (1U << 14);
	   	GPIOA->AFR[0] |= (1U << 13);
	   	GPIOA->AFR[0] |= (1U << 12);

	    /* Enable USART2 clock */
	    RCC->APB1ENR |= UART2EN;


	    /* Set baud rate */
	    USART2->BRR = compute_baud_rate(PERIPHERALCLK,
	                                     BAUDRATE);


	    USART2->CR1 = (TXEN | RXEN);
	    USART2->CR1 = UARTEN;


}

char uart_read(void){
	while (!(USART2->SR & SR_TXE)){

	}
  return USART2->DR;
}

/* Send one character */
void uart_send_ch(int ch)
{
    /* Wait until transmit data register is empty */
    while (!(USART2->SR & SR_TXE))
    {
    }

    /* Put character into data register */
    USART2->DR = (uint8_t)ch;
}


/* Calculate USART baud rate */
static uint16_t compute_baud_rate(uint32_t PeriphClk,
                                  uint32_t BaudRate)
{
    return (uint16_t)((PeriphClk + (BaudRate / 2U))
                      / BaudRate);
}
