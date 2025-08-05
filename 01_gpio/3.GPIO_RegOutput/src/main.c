#include <stdint.h>
#include <stdio.h>

// GPIO register map
typedef struct
{
	volatile uint32_t CRL;	// 0x00u
	volatile uint32_t CRH;	// 0x04u
	volatile uint32_t IDR;	// 0x08u
	volatile uint32_t ODR;	// 0x0Cu
	volatile uint32_t BSRR; // 0x10u
	volatile uint32_t BRR;	// 0x14u
	volatile uint32_t LCKR; // 0x18u
} GPIO_TypeDef;

// RCC register map
typedef struct
{
	volatile uint32_t CR;		// 0x00u
	volatile uint32_t CFGR;		// 0x04u
	volatile uint32_t CIR;		// 0x08u
	volatile uint32_t APB2RSTR; // 0x0Cu
	volatile uint32_t APB1RSTR; // 0x10u
	volatile uint32_t AHBENR;	// 0x14u
	volatile uint32_t APB2ENR;	// 0x18u
	volatile uint32_t APB1ENR;	// 0x1Cu
	volatile uint32_t BDCR;		// 0x20u
	volatile uint32_t CSR;		// 0x24u
} RCC_TypeDef;

#define GPIOA ((GPIO_TypeDef *)0x40010800) // GPIOA base address
#define GPIOC ((GPIO_TypeDef *)0x40011000) // GPIOC base address
#define RCC ((RCC_TypeDef *)0x40021000)	   // RCC base address
#define Write_Reg(address, value) *((volatile uint32_t *)(address)) = value
#define Read_Reg(address, bit_mask) *((volatile uint32_t *)(address)) & (bit_mask)

void delay_ms(unsigned int ms);
void Enabled_Clock(void);
void MyGPIO_Init(void);
void LedOn(unsigned char Pin_Number);
void LedOff(unsigned char Pin_Number);

int main(void)
{
	/* Bat Clock cho Port C*/
	// RCC_APB2ENR |= (1 << 4);
	// RCC_APB2ENR |= RCC_APB2Periph_GPIOC;
	// RCC->APB2ENR = (1 << 4);

	/* Cau hinh chan 13 */

	/* Clear CNF13[1:0] v� MODE13[1:0] */

	// C1: GPIOC_CRH &= ~(0xF << 20);
	// GPIOC->CRH &= 0xFFF0FFFFF;

	// MODE13 = 0b11 (Output 50 MHz), CNF13 = 0b00 (Push-pull)

	// C2: GPIOC_CRH |=  (0x2 << 20);
	// GPIOC->CRH |= 0x300000;

	/* New Code: PA7 */

	Enabled_Clock();
	MyGPIO_Init();
	while (1)
	{
		/* Bat Led */
		// GPIOC->ODR &= ~(1U << 13);
		// delay_ms(500);

		/* Tat Led */
		// GPIOC->ODR |= (1U << 13);
		// delay_ms(500);

		/* New Code */

		LedOn(7);
		delay_ms(0x1FF);

		LedOff(7);
		delay_ms(0x1FF);
	}
}

void delay_ms(unsigned int timeout)
{
	volatile unsigned int t1, t2;
	for (t1 = 0; t1 < timeout; t1++)
	{
		for (t2 = 0; t2 < 0x2aff; t2++)
		{
			__asm__("nop"); // tao delay ngan mat dung 1 chu ky CPU
		}
	}
}

void Enabled_Clock(void)
{
	uint32_t Temp_Reg;

	/* Set mode PA7 */
	Temp_Reg = RCC->APB2ENR;
	Temp_Reg |= (1u << 2); // Enable GPIOA
	Write_Reg(&RCC->APB2ENR, Temp_Reg);
}

void MyGPIO_Init(void)
{
	uint32_t Temp_Reg;

	/* Set mode PA7 */
	Temp_Reg = GPIOA->CRL;
	Temp_Reg &= ~((uint32_t)0xF << 28); // Clear 4 bit PA7 va giu nguyen cac bit khac
	Temp_Reg |= ((uint32_t)0x3 << 28);
	Write_Reg(&GPIOA->CRL, Temp_Reg); // Ghi gia tri vao thanh ghi CRL cua GPIOA va phai truyen dia chi
}

void LedOn(unsigned char Pin_Number)
{
	Write_Reg(&GPIOA->BSRR, 1u << Pin_Number);
}

void LedOff(unsigned char Pin_Number)
{
	Write_Reg(&GPIOA->BSRR, 1u << (Pin_Number + 16));
}
