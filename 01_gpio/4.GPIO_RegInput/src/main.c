#include "hw_stm32f103c8t6.h"

static const GPIO_Pin LED_PINS[] = {GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15};
static const uint8_t LED_COUNT = sizeof(LED_PINS) / sizeof(LED_PINS[0]);
static const uint8_t LED_PORT = GPIOC;

typedef enum
{
    DIR_LEFT_TO_RIGHT = 0,
    DIR_RIGHT_TO_LEFT
} Led_Direction;

static volatile Led_Direction ledDirection = DIR_LEFT_TO_RIGHT;

static void RunLEDSequence(void)
{
    int8_t i;

    /* Sáng dần */
    if (ledDirection == DIR_LEFT_TO_RIGHT)
    {
        for (i = 0; i < LED_COUNT; i++)
        {
            GPIO_WritePin(LED_PORT, LED_PINS[i], GPIO_PIN_SET);
            Delay(300);
        }
    }
    else
    {
        for (i = LED_COUNT - 1; i >= 0; i--)
        {
            GPIO_WritePin(LED_PORT, LED_PINS[i], GPIO_PIN_SET);
            Delay(300);
        }
    }

    /* Tắt dần */
    if (ledDirection == DIR_LEFT_TO_RIGHT)
    {
        for (i = 0; i < LED_COUNT; i++)
        {
            GPIO_WritePin(LED_PORT, LED_PINS[i], GPIO_PIN_RESET);
            Delay(300);
        }
    }
    else
    {
        for (i = LED_COUNT - 1; i >= 0; i--)
        {
            GPIO_WritePin(LED_PORT, LED_PINS[i], GPIO_PIN_RESET);
            Delay(300);
        }
    }
}

void LEDChaseEffect(void);

int main(void)
{
    uint8_t i;
    uint8_t effect_mode = 0; // 0: Sequence, 1: Chase

    /* Cấu hình LED là output push-pull */
    for (i = 0; i < LED_COUNT; i++)
    {
        GPIO_Init(LED_PORT, LED_PINS[i], GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_OUTPUT_PP);
        GPIO_WritePin(LED_PORT, LED_PINS[i], GPIO_PIN_RESET);
    }

    /* Cấu hình nút nhấn */
    GPIO_Init(GPIOB, GPIO_PIN_1, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PU_PD);
    GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

    while (1)
    {
        /* Kiểm tra nút nhấn */
        if (Button_GetState() == GPIO_PIN_RESET)
        {
            /* Đợi nút nhả ra */
            while (Button_GetState() == GPIO_PIN_RESET)
                ;

            /* Đảo chiều hoặc đổi hiệu ứng */
            if (effect_mode == 0)
            {
                ledDirection ^= 1; // Đảo chiều
            }
            else
            {
                effect_mode ^= 1; // Chuyển đổi hiệu ứng
            }

            Delay(100);
        }

        /* Chạy hiệu ứng được chọn */
        if (effect_mode == 0)
        {
            RunLEDSequence(); // Hiệu ứng sáng/tắt dần
        }
        else
        {
            LEDChaseEffect(); // Hiệu ứng đuổi LED
        }
    }
}
void LEDChaseEffect(void)
{
    int8_t i;

    if (ledDirection == DIR_LEFT_TO_RIGHT)
    {
        for (i = 0; i < LED_COUNT; i++)
        {
            GPIO_WritePin(LED_PORT, LED_PINS[i], GPIO_PIN_SET);
            Delay(200);

            if (i > 0)
            {
                GPIO_WritePin(LED_PORT, LED_PINS[i - 1], GPIO_PIN_RESET);
            }
        }

        GPIO_WritePin(LED_PORT, LED_PINS[LED_COUNT - 1], GPIO_PIN_RESET);
    }
    else
    {
        for (i = LED_COUNT - 1; i >= 0; i--)
        {
            GPIO_WritePin(LED_PORT, LED_PINS[i], GPIO_PIN_SET);
            Delay(200);

            if (i < LED_COUNT - 1)
            {
                GPIO_WritePin(LED_PORT, LED_PINS[i + 1], GPIO_PIN_RESET);
            }
        }

        GPIO_WritePin(LED_PORT, LED_PINS[0], GPIO_PIN_RESET);
    }
}
