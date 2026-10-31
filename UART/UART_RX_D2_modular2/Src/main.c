#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"

#include "uart.h"


int main(void)
{


    uart_init();

    while (1)
    {
       printf("OMKAR\n");
    }
}

