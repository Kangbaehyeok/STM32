#include "stm32f10x.h"
#include "SystemInit.h"

#define AFIO_EXTICR1 (*(volatile unsigned long*)0x40010008)

int a = 0, x = 500, z = 1;

void Delay_ms(unsigned int ms)
{
    volatile unsigned int ncount=1000*ms;
    for(;ncount!=0;ncount--);
}

void EXTI0_IRQHandler(void)
{
    EXTI->PR = 0x00000001;
    
    a++;
    
    Delay_ms(100);
}

void EXTI1_IRQHandler(void)
{
    EXTI->PR = 0x00000002;
    
    x -= 50;
    
    Delay_ms(100);    
}

void EXTI2_IRQHandler(void)
{
    EXTI->PR = 0x00000004;

    x +=50;
    
    Delay_ms(100);
}

void EXTI3_IRQHandler(void)
{
    EXTI->PR= 0x00000008;
    
    if(z%2 == 1)
    {
        EXTI->IMR = 0x00000008;
    }
    else
    {
        EXTI->IMR = 0x0000000F;
    }
    
    z++;
    
    Delay_ms(100);
}

int main(void)  
{
    int led, i, j, k;
    
    RCC->APB2ENR = 0x00D;
    AFIO_EXTICR1 = 0x0000;
    GPIOA->CRL = 0x00008888;
    GPIOB->CRH = 0x11111111;
    
    EXTI->FTSR = 0x0000000F;
    EXTI->RTSR = 0x00000000;
    
    EXTI->IMR = 0x0000000F;
    NVIC->ISER[0] =0x000003C0;
    
    while(1) 
    {
        led = 0x0000;
        
        for(j=7;j>=0;j--)
        {
            k = 0x8000;
            
            for(i=0;i<=j;i++)
            {
                GPIOB->ODR = led+k;
                Delay_ms(x);
                
                k >>= 1;
                
                while(a%2 == 1)
                {
                    GPIOB->ODR  = 0x0000;
                    Delay_ms(500);
                    GPIOB->ODR  = 0xFF00;
                    Delay_ms(500);
                }
            }
            
            led = (led<<1)+0x0100;
        }
        
        GPIOB->ODR = 0x0000;
        Delay_ms(x);
    }
}
