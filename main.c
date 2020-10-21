#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"


int main(void){

    volatile uint32_t x;
    int32_t leitura;

    void Delay();

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
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4 ,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);



    while (1){
        leitura = 0;

        leitura = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);

        if(leitura == 0x01){
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x04);
        }
        if(leitura == 0x10){
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x08);
        }
        if(leitura == 0x00){
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x02);

        }
        else{
            // Apaga todos os leds
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
        }
       }
}
