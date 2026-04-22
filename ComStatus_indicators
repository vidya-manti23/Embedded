#include "stm32f4xx.h"

// Simple delay (works reliably)
void delay(volatile uint32_t count)
{
    while(count--);
}

// Communication status
typedef enum {
    COMM_ONGOING,
    COMM_SUCCESS,
    COMM_FAULT
} CommStatus;

int main(void)
{
    // Enable GPIOA & GPIOB clocks
    RCC->AHB1ENR |= (1 << 0); // GPIOA
    RCC->AHB1ENR |= (1 << 1); // GPIOB

    // PA5 → Green (on-board LED)
    GPIOA->MODER &= ~(3 << (5 * 2));
    GPIOA->MODER |=  (1 << (5 * 2));

    // PB6 → Yellow (external)
    GPIOB->MODER &= ~(3 << (6 * 2));
    GPIOB->MODER |=  (1 << (6 * 2));

    // PB7 → Red (external)
    GPIOB->MODER &= ~(3 << (5 * 2));
    GPIOB->MODER |=  (1 << (5 * 2));

    CommStatus commStatus = COMM_ONGOING;

    while (1)
    {
        // -------- COMMUNICATION ONGOING --------
        commStatus = COMM_ONGOING;

        for (int i = 0; i < 20; i++)  // ~few seconds
        {
            GPIOA->ODR &= ~(1 << 5); // Green OFF
            GPIOB->ODR &= ~(1 << 5); // Red OFF

            GPIOB->ODR ^= (1 << 6);  // Yellow blink
            delay(500000);
        }

        // -------- SUCCESS --------
        commStatus = COMM_SUCCESS;

        GPIOB->ODR &= ~(1 << 6); // Yellow OFF
        GPIOB->ODR &= ~(1 << 5); // Red OFF
        GPIOA->ODR |=  (1 << 5); // Green ON

        delay(3000000);

        // -------- FAULT --------
        commStatus = COMM_FAULT;

        GPIOA->ODR &= ~(1 << 5); // Green OFF
        GPIOB->ODR &= ~(1 << 6); // Yellow OFF

        for (int i = 0; i < 10; i++)
        {
            GPIOB->ODR ^= (1 << 5); // Red blink
            delay(800000);
        }
    }
}
