/*
 * uart.h
 *
 *  Created on: Sep 6, 2026
 *      Author: omkar
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f4xx.h"

void uart_init(void);
char uart_read(void);

#endif /* UART_H_ */
