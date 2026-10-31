#include <stdint.h>
#include "stm32f4xx.h"


#define GPIOAEN        (1U << 0)
#define UART2EN        (1U << 17)

#define PERIPHERALCLK  16000000U
#define BAUDRATE       115200U

#define TXEN           (1U << 3)
#define UARTEN         (1U << 13)
#define SR_TXE         (1U << 7)

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


	    /* =========================
	       PA2 = USART2_TX
	       ========================= */

	    /* Clear PA2 mode bits */
	    GPIOA->MODER &= ~(3U << (2 * 2));

	    /* Set PA2 to Alternate Function mode = 10 */
	    GPIOA->MODER |= (2U << (2 * 2));


	    /* PA2 Alternate Function = AF7
	       AF7 = USART2 */
	    GPIOA->AFR[0] &= ~(0xFU << 8);
	    GPIOA->AFR[0] |=  (7U << 8);


	    /* Enable USART2 clock */
	    RCC->APB1ENR |= UART2EN;


	    /* Set baud rate */
	    USART2->BRR = compute_baud_rate(PERIPHERALCLK,
	                                     BAUDRATE);


	    /* Enable USART2
	       Enable Transmitter */
	    USART2->CR1 = UARTEN | TXEN;





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
