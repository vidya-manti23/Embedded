#include "stm32f4xx_hal.h"
#include <stdio.h>

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart2;

/* DHT12 I2C Address */
#define DHT12_ADDR  (0x5C << 1)

uint8_t data[5];
char msg[100];

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART2_UART_Init(void);

int main(void)
{
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART2_UART_Init();

    while (1)
    {
        /* Read 5 bytes from DHT12 sensor */
        HAL_I2C_Master_Receive(&hi2c1,
                               DHT12_ADDR,
                               data,
                               5,
                               HAL_MAX_DELAY);

        /* Extract humidity */
        float humidity = data[0] + (data[1] / 10.0);

        /* Extract temperature */
        float temperature = data[2] + (data[3] / 10.0);

        /* Print through UART */
        sprintf(msg,
                "Temperature = %.1f C   Humidity = %.1f %%\r\n",
                temperature,
                humidity);

        HAL_UART_Transmit(&huart2,
                          (uint8_t*)msg,
                          strlen(msg),
                          HAL_MAX_DELAY);

        HAL_Delay(1000);
    }
}

/* I2C1 Initialization */
static void MX_I2C1_Init(void)
{
    hi2c1.Instance = I2C1;

    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    HAL_I2C_Init(&hi2c1);
}

/* USART2 Initialization */
static void MX_USART2_UART_Init(void)
{
    huart2.Instance = USART2;

    huart2.Init.BaudRate = 9600;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;

    HAL_UART_Init(&huart2);
}

/* GPIO Initialization */
static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
}

/* System Clock Configuration */
void SystemClock_Config(void)
{
    /* Default clock configuration */
}
