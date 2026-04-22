#include "stm32f446xx.h"

void delay_ms(uint32_t ms);

int main(void)
{
    // 1. Enable GPIOA clock
    RCC->AHB1ENR |= (1 << 0);

    // 2. Configure PA5, PA6, PA7, PA8 as output //d13 d12 d11 d7
    GPIOA->MODER &= ~((3<<(5*2)) | (3<<(6*2)) | (3<<(7*2)) | (3<<(8*2)));
    GPIOA->MODER |=  ((1<<(5*2)) | (1<<(6*2)) | (1<<(7*2)) | (1<<(8*2)));

    // Push-pull
    GPIOA->OTYPER &= ~((1<<5)|(1<<6)|(1<<7)|(1<<8));

    // Medium speed
    GPIOA->OSPEEDR |= ((1<<(5*2))|(1<<(6*2))|(1<<(7*2))|(1<<(8*2)));

    // No pull-up/pull-down
    GPIOA->PUPDR &= ~((3<<(5*2))|(3<<(6*2))|(3<<(7*2))|(3<<(8*2)));

    // Simulated variables
    uint8_t reverseGear = 1;
    float proximity = 1.0;

    while (1)
    {
        if (reverseGear == 1)
        {
            // Turn OFF all LEDs first
            GPIOA->ODR &= ~((1<<5)|(1<<6)|(1<<7)|(1<<8));


            if (proximity > 0.75)
            {
                GPIOA->ODR |= (1<<5); // pa 5 - d13
            }
            else if (proximity > 0.5) // 5 & 6 - 13,12
            {
                GPIOA->ODR |= (1<<5) | (1<<6);
            }
            else if (proximity > 0.25) // 5,6,7 - 13,12,11
            {
                GPIOA->ODR |= (1<<5) | (1<<6) | (1<<7);
            }
            else //5,6,7,8 - 13,12,11,7
            {
                GPIOA->ODR |= (1<<5) | (1<<6) | (1<<7) | (1<<8);
            }

            // Simulate object getting closer
            proximity -= 0.1;
            if (proximity < 0)
                proximity = 1.0;
        }
        else
        {
            // Reverse OFF → All LEDs OFF
            GPIOA->ODR &= ~((1<<5)|(1<<6)|(1<<7)|(1<<8));
        }

        delay_ms(500);
    }
}

// Simple delay
void delay_ms(uint32_t ms)
{
    for (volatile uint32_t i = 0; i < ms * 1000; i++)
    {
        __asm("nop");
    }
}
