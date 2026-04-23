#include "stm32f4xx.h"

#define LCD_PORT GPIOA

#define RS 5
#define EN 6

#define D4 7
#define D5 8
#define D6 9
#define D7 10

void delay_ms(uint32_t ms);
void lcd_command(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_init(void);
void lcd_send_nibble(uint8_t nibble);
void lcd_pulse_enable(void);

int main(void) {

    RCC->AHB1ENR |= (1 << 0);

    for (int pin = 5; pin <= 10; pin++) {
        LCD_PORT->MODER &= ~(0x3 << (pin * 2));
        LCD_PORT->MODER |=  (0x1 << (pin * 2));
    }

    lcd_init();

    lcd_data('H');
    lcd_data('E');
    lcd_data('L');
    lcd_data('L');
    lcd_data('O');

    while (1);
}

void lcd_pulse_enable(void) {
    LCD_PORT->ODR |= (1 << EN);
    for (volatile int i = 0; i < 1000; i++); // short delay
    LCD_PORT->ODR &= ~(1 << EN);
}

void lcd_send_nibble(uint8_t nibble) {

    LCD_PORT->ODR &= ~((1<<D4)|(1<<D5)|(1<<D6)|(1<<D7));

    if (nibble & 0x01) LCD_PORT->ODR |= (1 << D4);
    if (nibble & 0x02) LCD_PORT->ODR |= (1 << D5);
    if (nibble & 0x04) LCD_PORT->ODR |= (1 << D6);
    if (nibble & 0x08) LCD_PORT->ODR |= (1 << D7);

    lcd_pulse_enable();
}

void lcd_command(uint8_t cmd) {

    LCD_PORT->ODR &= ~(1 << RS);

    lcd_send_nibble(cmd >> 4);
    lcd_send_nibble(cmd & 0x0F);

    delay_ms(2);
}

void lcd_data(uint8_t data) {

    LCD_PORT->ODR |= (1 << RS);

    lcd_send_nibble(data >> 4);
    lcd_send_nibble(data & 0x0F);

    delay_ms(2);
}

void lcd_init(void) {

    delay_ms(40);

    // RESET SEQUENCE (VERY IMPORTANT)
    lcd_send_nibble(0x03);
    delay_ms(5);

    lcd_send_nibble(0x03);
    delay_ms(1);

    lcd_send_nibble(0x03);
    delay_ms(1);

    lcd_send_nibble(0x02); // switch to 4-bit

    lcd_command(0x28);
    lcd_command(0x0C);
    lcd_command(0x06);
    lcd_command(0x01);

    delay_ms(2);
}

void delay_ms(uint32_t ms) {
    for (volatile uint32_t i = 0; i < ms * 4000; i++);
}
