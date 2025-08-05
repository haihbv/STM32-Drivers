#ifndef __HW_STM32F103C8_H
#define __HW_STM32F103C8_H

#include <stdint.h>

typedef enum
{
  GPIO_PIN_RESET = 0,
  GPIO_PIN_SET
} GPIO_PinState;

typedef enum
{
  GPIO_PIN_0 = 0,
  GPIO_PIN_1,
  GPIO_PIN_2,
  GPIO_PIN_3,
  GPIO_PIN_4,
  GPIO_PIN_5,
  GPIO_PIN_6,
  GPIO_PIN_7,
  GPIO_PIN_8,
  GPIO_PIN_9,
  GPIO_PIN_10,
  GPIO_PIN_11,
  GPIO_PIN_12,
  GPIO_PIN_13,
  GPIO_PIN_14,
  GPIO_PIN_15
} GPIO_Pin;

/* GPIO Configuration */
#define GPIO_MODE_INPUT 0x00U
#define GPIO_MODE_OUTPUT_10MHZ 0x01U
#define GPIO_MODE_OUTPUT_2MHZ 0x02U
#define GPIO_MODE_OUTPUT_50MHZ 0x03U

#define GPIO_CNF_INPUT_ANALOG 0x00U
#define GPIO_CNF_INPUT_FLOATING 0x04U
#define GPIO_CNF_INPUT_PU_PD 0x08U
#define GPIO_CNF_OUTPUT_PP 0x00U
#define GPIO_CNF_OUTPUT_OD 0x04U

/* GPIO Ports */
#define GPIOA 0
#define GPIOB 1
#define GPIOC 2

/* Function Prototypes */

/**
 * @brief  Khoi tao mot chan GPIO voi che do va cau hinh duoc chi dinh
 * @param  Port: Port GPIO (GPIOA, GPIOB hoac GPIOC)
 * @param  Pin: Chan GPIO can cau hinh (GPIO_PIN_0 den GPIO_PIN_15)
 * @param  Mode: Che do hoat dong cua GPIO:
 *          @arg GPIO_MODE_INPUT: Che do input
 *          @arg GPIO_MODE_OUTPUT_10MHZ: Output toc do 10MHz
 *          @arg GPIO_MODE_OUTPUT_2MHZ: Output toc do 2MHz
 *          @arg GPIO_MODE_OUTPUT_50MHZ: Output toc do 50MHz
 * @param  Config: Cau hinh GPIO:
 *          @arg GPIO_CNF_INPUT_ANALOG: Input analog
 *          @arg GPIO_CNF_INPUT_FLOATING: Input floating
 *          @arg GPIO_CNF_INPUT_PU_PD: Input voi pull-up/pull-down
 *          @arg GPIO_CNF_OUTPUT_PP: Output push-pull
 *          @arg GPIO_CNF_OUTPUT_OD: Output open-drain
 * @retval None
 * @note   Ham se tu dong bat clock cho port tuong ung truoc khi cau hinh
 *         Moi chan GPIO chiem 4 bit trong thanh ghi CRL (chan 0-7) hoac CRH (chan 8-15)
 */
void GPIO_Init(uint8_t Port, GPIO_Pin Pin, uint32_t Mode, uint32_t Config);

void GPIO_WritePin(uint8_t Port, GPIO_Pin Pin, GPIO_PinState State);
GPIO_PinState GPIO_ReadPin(uint8_t Port, GPIO_Pin Pin);
void GPIO_TogglePin(uint8_t Port, GPIO_Pin Pin);
uint8_t Button_GetState(void);
void Delay(uint32_t ms);
#endif /* __HW_STM32F103C8_H */
