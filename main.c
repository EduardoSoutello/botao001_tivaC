#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

/**
 * main.c
 */
int main(void){

    volatile uint32_t x;
    int32_t leitura;


    //Habilitar o clock para PORTF
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //Espera que seja terminada a habilitação da porta
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){
    }
    // remove o bug de travamento da chave SW2
    HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= GPIO_PIN_0;

    //Pino 0 e 4 declarados como entrada
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);      // botao SW2 e SW1

    //Pino 1, 2 e 3 como saida.
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);     //LED vermelho , azul e verde



    // Configurar resistores internos e nivel de corrente 2mA
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4 ,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);



    while (1){
        // Apaga os leds
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);

        if((GPIO_PIN_0 ==1)&(GPIO_PIN_4 ==0)){
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x04);
        }
        if((GPIO_PIN_0 ==0)&(GPIO_PIN_4 ==1)){
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x08);
        }
        if((GPIO_PIN_0 ==0) & (GPIO_PIN_4 ==0)){
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x02);
        }

        /*
         apos codigo funcionar deletar esse trecho
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x02);
           for (x = 0; x < 200000; x++);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
           for (x = 0; x < 200000; x++);

           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x04);
           for (x = 0; x < 200000; x++);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
           for (x = 0; x < 200000; x++);

           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x08);
           for (x = 0; x < 200000; x++);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
           for (x = 0; x < 200000; x++);
            */

       }

}
