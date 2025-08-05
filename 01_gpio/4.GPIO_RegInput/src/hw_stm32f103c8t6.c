#include "hw_stm32f103c8t6.h"

/* Register Definitions */
#define RCC_APB2ENR (*((volatile uint32_t *)0x40021018))
#define GPIOA_BASE 0x40010800
#define GPIOB_BASE 0x40010C00
#define GPIOC_BASE 0x40011000

#define GPIO_CRL_OFFSET 0x00
#define GPIO_CRH_OFFSET 0x04
#define GPIO_IDR_OFFSET 0x08
#define GPIO_ODR_OFFSET 0x0C
#define GPIO_BSRR_OFFSET 0x10

/* Helper Macros */
#define GPIO_PORT(Port) ((Port == GPIOA) ? GPIOA_BASE : (Port == GPIOB) ? GPIOB_BASE \
                                                                        : GPIOC_BASE)

void GPIO_Init(uint8_t Port, GPIO_Pin Pin, uint32_t Mode, uint32_t Config)
{
    volatile uint32_t *CR;
    uint32_t tmpreg;
    uint32_t pinpos;

    /* Enable GPIO Clock */
    if (Port == GPIOA)
        RCC_APB2ENR |= (1 << 2);
    else if (Port == GPIOB)
        RCC_APB2ENR |= (1 << 3);
    else if (Port == GPIOC)
        RCC_APB2ENR |= (1 << 4);

    /* Get CR register address */
    if (Pin < 8)
    {
        CR = (volatile uint32_t *)((uintptr_t)GPIO_PORT(Port) + GPIO_CRL_OFFSET);
        pinpos = Pin * 4;
    }
    else
    {
        CR = (volatile uint32_t *)((uintptr_t)GPIO_PORT(Port) + GPIO_CRH_OFFSET);
        pinpos = (Pin - 8) * 4;
    }

    /* Configure pin */
    tmpreg = *CR;
    tmpreg &= ~(0x0Fu << pinpos);
    tmpreg |= ((Mode | Config) << pinpos);
    *CR = tmpreg;
}

void GPIO_WritePin(uint8_t Port, GPIO_Pin Pin, GPIO_PinState State)
{
    volatile uint32_t *BSRR = (volatile uint32_t *)((uintptr_t)GPIO_PORT(Port) + GPIO_BSRR_OFFSET);
    *BSRR = (State == GPIO_PIN_SET) ? (1 << Pin) : (1 << (Pin + 16));
}

GPIO_PinState GPIO_ReadPin(uint8_t Port, GPIO_Pin Pin)
{
    volatile uint32_t *IDR = (volatile uint32_t *)((uintptr_t)GPIO_PORT(Port) + GPIO_IDR_OFFSET);
    return (*IDR & (1 << Pin)) ? GPIO_PIN_SET : GPIO_PIN_RESET;
}

void GPIO_TogglePin(uint8_t Port, GPIO_Pin Pin)
{
    volatile uint32_t *ODR = (volatile uint32_t *)((uintptr_t)GPIO_PORT(Port) + GPIO_ODR_OFFSET);
    *ODR ^= (1 << Pin);
}

uint8_t Button_GetState(void)
{
    static uint8_t last_state = 1;
    uint8_t current_state = GPIO_ReadPin(GPIOB, GPIO_PIN_1);

    /* Simple debounce */
    if (current_state != last_state)
    {
        Delay(10);
        current_state = GPIO_ReadPin(GPIOB, GPIO_PIN_1);
        last_state = current_state;
    }

    return current_state;
}

void Delay(uint32_t ms)
{
    volatile uint32_t i, j;
    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 0x2aff; j++)
        {
            __asm__("nop");
        }
    }
}
