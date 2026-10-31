#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"

#define GPIOAEN        (1U << 0)
#define UART2EN        (1U << 17)

#define PERIPHERALCLK  16000000U
#define BAUDRATE       115200U

#define TXEN           (1U << 3)
#define UARTEN         (1U << 13)
#define SR_TXE         (1U << 7)
void uart_init(void);
void uart_send_ch(int ch);

static uint16_t compute_baud_rate(uint32_t PeriphClk,
                                  uint32_t BaudRate);
int __io_putchar(int ch){
	uart_send_ch(ch);
			return ch;
}


int main(void)
{


    uart_init();

    while (1)
    {
       printf("OMKAR\n");
    }
}

void uart_init(){

	    RCC->AHB1ENR |= GPIOAEN;


	    GPIOA->MODER &= ~(3U << (2 * 2));
	    GPIOA->MODER |= (2U << (2 * 2));

	    GPIOA->AFR[0] &= ~(0xFU << 8);
	    GPIOA->AFR[0] |=  (7U << 8);

	    RCC->APB1ENR |= UART2EN;


	    USART2->BRR = compute_baud_rate(PERIPHERALCLK,
	                                     BAUDRATE);

	    USART2->CR1 = UARTEN | TXEN;



}


void uart_send_ch(int ch)
{

    while (!(USART2->SR & SR_TXE))
    {
    }

    USART2->DR = (uint8_t)ch;
}



static uint16_t compute_baud_rate(uint32_t PeriphClk,
                                  uint32_t BaudRate)
{
    return (uint16_t)((PeriphClk + (BaudRate / 2U))
                      / BaudRate);
}
