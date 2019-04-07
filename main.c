#include "stm32f4xx.h"

//GPIO_InitTypeDef GPIO_InitStructure;

#define LED_PORT GPIOD
#define LED_PWM (1 << 15) /* port D, pin 15 */

#define    DWT_CYCCNT    *(volatile unsigned long *)0xE0001004
#define    DWT_CONTROL   *(volatile unsigned long *)0xE0001000
#define    SCB_DEMCR     *(volatile unsigned long *)0xE000EDFC


static inline void setup_leds(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;    				/* Enable clocking of port D (PWM LED) */
    LED_PORT->MODER |=  GPIO_MODER_MODER15_0;    		/* Enable high level for LED 					 */
}

static inline void switch_leds_off(void){
    LED_PORT->ODR = 0;
}

void DWT_Init(void)
{
  SCB_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;					/* Allow to use the counter */
	DWT_CYCCNT  = 0;  																/* Reset the counting register */
	DWT_CONTROL |= DWT_CTRL_CYCCNTENA_Msk;  					/* Start the counter */
}

/* delta for delay */
static __inline uint32_t delta(uint32_t t0, uint32_t t1)
{
    return (t1 - t0); 
}
void delay_us(uint32_t us)
{
      uint32_t t0 =  DWT->CYCCNT;
      uint32_t us_count_tic =  us * (SystemCoreClock/1000000);
      while (delta(t0, DWT->CYCCNT) < us_count_tic) ;
}

void delay_ms(uint32_t ms)
{
	uint32_t t0 =  DWT->CYCCNT;
  uint32_t us_count_tic =  ms * (SystemCoreClock/1000);
  while (delta(t0, DWT->CYCCNT) < us_count_tic) ;
}

int main(void)
{
  setup_leds();   																	/* LED initialization */
	DWT_Init();																				/* Delay initialization */
 
  while (1)  
	{
		LED_PORT->ODR = LED_PWM;  											
		delay_ms(500);
		switch_leds_off();   														/* Turn of LED */
		delay_ms(500);
 
  }
}
