#include "stm32f10x.h"
#include "Systeminit.h"

void Delay_ms(unsigned int ms)
{
    volatile unsigned int ncount=1000*ms;
    for(;ncount!=0;ncount--);
}

int main(void)
{
    int led, i, j, k;
    
    RCC->APB2ENR = 0x00000004;
    GPIOA->CRL = 0x11111111;
    
    while(1)
    {
        led = 0x00;
        
        for(j=7;j>=0;j--)
        {
            k = 0x80;
            
            for(i=0;i<=j;i++)
            {
                GPIOA->ODR = led+k;
                Delay_ms(500);
                k >>= 1;
            }
            
            led = (led<<1)+1;
        }
        
        GPIOA->ODR = 0x0000;
        Delay_ms(500);
    }
}
