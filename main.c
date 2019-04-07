#include "stm32f4xx.h"
#include <stdlib.h>


#define LED_PWM (1 << 15) 		/* port D, pin 15 */
#define LEDC			93					// Should be 1 or greater
#define PORTOUT			GPIOD				// порт дл€ WS2812B
#define ClearOutBit		(PORTOUT->ODR = 0); //0 на выход
#define SetOutBit		(PORTOUT->ODR = LED_PWM);   //1 на выход

#define RED				0x0F				// инициализаци€ красного цвета
#define GREEN			0xF0				// инициализаци€ зелЄного цвета
#define BLUE			0x55				// инициализаци€ синего цвета

#define    DWT_CYCCNT    *(volatile unsigned long *)0xE0001004
#define    DWT_CONTROL   *(volatile unsigned long *)0xE0001000
#define    SCB_DEMCR     *(volatile unsigned long *)0xE000EDFC
	
unsigned char ledred[LEDC+1] ;		// массив красных
unsigned char ledblue[LEDC+1] ;		// массив синих
unsigned char ledgreen[LEDC+1];		// массив зеленых


static inline void setup_leds(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;    				/* Enable clocking of port D (PWM LED) */
    PORTOUT->MODER |=  GPIO_MODER_MODER15_0;    		/* Enable high level for LED 					 */
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


void loadWS2812B (void)
{
		
	unsigned	char a,b,temp;
	// формирование сброса
	PORTOUT->ODR = 0;
	__nop();
		//--------------------------------
	for(a=0;a<LEDC;a++)
	{
		for(b=0;b<3;b++)
		{
			switch (b)
			{
				case 0 :
				temp=ledgreen[a];
				break;
				case 1 :
				temp=ledred[a];
				break;
				case 2 :
				temp=ledblue[a];
				default:
				temp = 0;
			} 
			// загрузка байта
			if(temp&0x80)
			{
				//формирование бита 1
				SetOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				ClearOutBit;
				__nop();
			}
			else
			{
				//формирование бита 0
				SetOutBit;
				__nop();__nop();__nop();__nop();
				ClearOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
			}
			
			if(temp&0x40)
			{
				//формирование бита 1
				SetOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				ClearOutBit;
				__nop();
			}
			else
			{
				//формирование бита 0
					SetOutBit;
				__nop();__nop();__nop();__nop();
					ClearOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
			}
			
			if(temp&0x20)
			{
				//формирование бита 1
				SetOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				ClearOutBit;
				__nop();
			}
			else
			{
				//формирование бита 0
					SetOutBit;
				__nop();__nop();__nop();__nop();
					ClearOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
			}
			if(temp&0x10)
			{
				//формирование бита 1
				SetOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				ClearOutBit;
				__nop();
			}
			else
			{
				//формирование бита 0
					SetOutBit;
				__nop();__nop();__nop();__nop();
					ClearOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
			}
			if(temp&0x8)
			{
				//формирование бита 1
				SetOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				ClearOutBit;
				__nop();
			}
			else
			{
				//формирование бита 0
					SetOutBit;
				__nop();__nop();__nop();__nop();
					ClearOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
			}
			
			if(temp&0x4)
			{
				//формирование бита 1
				SetOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				ClearOutBit;
				__nop();
			}
			else
			{
				//формирование бита 0
					SetOutBit;
				__nop();__nop();__nop();__nop();
					ClearOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
			}
			if(temp&0x2)
			{
				//формирование бита 1
				SetOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				ClearOutBit;
				__nop();
			}
			else
			{
				//формирование бита 0
					SetOutBit;
				__nop();__nop();__nop();__nop();
					ClearOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
			}
			
			if(temp&0x1)
			{
				//формирование бита 1
				SetOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				ClearOutBit;
				__nop();
			}
			else
			{
				//формирование бита 0
					SetOutBit;
				__nop();__nop();__nop();__nop();
					ClearOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
			}
		}
	}
}






void CometWhite (void)
{
	
	//движение вперЄд
	unsigned char i = 6;
	do
	{	ledred[i] =    255;
		ledblue[i] =   255;
		ledgreen[i] =  255;
		
		
		ledred[i-1] =   255/4;
		ledblue[i-1] =  255/4;
		ledgreen[i-1] = 255/4;
		
		ledred[i-2] =   255/8;
		ledblue[i-2] =  255/8;
		ledgreen[i-2] = 255/8;
		
		ledred[i-3] =   255/16;
		ledblue[i-3] =  255/16;
		ledgreen[i-3] = 255/16;
		
		ledred[i-4] =   255/32;
		ledblue[i-4] =  255/32;
		ledgreen[i-4] = 255/32;
		
		ledred[i-5] =   0;
		ledblue[i-5] =  0;
		ledgreen[i-5] = 0;
		
		delay_ms(50);
		i++;
		
		loadWS2812B();
		
	} while (i<=LEDC);
	//тушение оставшихс€ 4 —ƒ
	ledred[LEDC-1] =   0;
	ledblue[LEDC-1] =  0;
	ledgreen[LEDC-1] = 0;
	
	ledred[LEDC-2] =   0;
	ledblue[LEDC-2] =  0;
	ledgreen[LEDC-2] = 0;
	
	ledred[LEDC-3] =   0;
	ledblue[LEDC-3] =  0;
	ledgreen[LEDC-3] = 0;
	
	ledred[LEDC-4] =   0;
	ledblue[LEDC-4] =  0;
	ledgreen[LEDC-4] = 0;
	
}

void moveRed (void)		
{
	
		//движение вперЄд
		unsigned char i = 0;
		do
		{	ledred[i] =  250;
			ledblue[i] =   0;
			ledgreen[i] =  0;
			delay_ms(50);
			
			ledred[i-1] =  0;
			ledblue[i-1] = 0;
			ledgreen[i-1]= 0;
			delay_ms(50);
			i++;
			
			loadWS2812B();
			
		} while (i<=LEDC);
		
		//движение назад
		 i = LEDC;
		do
		{	ledred[i-1] = 250;
			ledblue[i-1] =   0;
			ledgreen[i-1] =  0;
			delay_ms(50);
			
			
			ledred[i] =      0;
			ledblue[i] =     0;
			ledgreen[i] =    0;
			delay_ms(50);
			i--;
			loadWS2812B();
			
		} while (i>0);
	
	ledred[0] =      0;
	ledblue[0] =     0;
	ledgreen[0] =    0;
	
}


void MidleGreen (void)
{
	
	//движение в пр€мом направлении
	unsigned char i =15;
	unsigned char j =15;
	do
	{	ledred[i] =    0;
		ledblue[i] =   0;
		ledgreen[i] =  250;
		delay_ms(25);
		
		ledred[i-1] =  0;
		ledblue[i-1] = 0;
		ledgreen[i-1]= 0;
		delay_ms(25);
		i++;
		
		loadWS2812B();
		
		
		ledred[j-1] =    0;
		ledblue[j-1] =   0;
		ledgreen[j-1] =  250;
		delay_ms(25);
		
		
		ledred[j] =      0;
		ledblue[j] =     0;
		ledgreen[j] =    0;
		delay_ms(25);
		j--;
		loadWS2812B();
		
	} while (i<LEDC);
	while (j>=1);
	//тушение первого и последнего —ƒ
	ledred[0] =  0;
	ledblue[0] = 0;
	ledgreen[0]= 0;
	
	
	ledred[29] =  0;
	ledblue[29] = 0;
	ledgreen[29]= 0;
		
	//движение в обратном направлении
	i =LEDC;
	j =0;
	do
	{	ledred[i] =  0;
		ledblue[i] =   0;
		ledgreen[i] =  0;
		delay_ms(25);
		
		ledred[i-1] =  0;
		ledblue[i-1] = 0;
		ledgreen[i-1]= 250;
		delay_ms(25);
		i--;
		
		loadWS2812B();
		
		
		ledred[j] =      0;
		ledblue[j] =     0;
		ledgreen[j] =   250;
		
		ledred[j-1] =  0;
		ledblue[j-1] =   0;
		ledgreen[j-1] =  0;
		delay_ms(25);
		
		
		
		
		j++;
		loadWS2812B();
		
	} while (i>15);
	while (j<14);
	
	
	//тушение 14-го и 15-го —ƒ
	ledred[14] =  0;
	ledblue[14] = 0;
	ledgreen[14]= 0;
	
	
	ledred[15] =  0;
	ledblue[15] = 0;
	ledgreen[15]= 0;
	
}

void moveBlue (void)
{
	
	//движение вперЄд
	unsigned char i = 2;
	do
	{	ledred[i] =  0;
		ledblue[i] =  255;
		ledgreen[i] =  0;
		delay_ms(50);
		
		ledred[i-1] =   0;
		ledblue[i-1] =  0;
		ledgreen[i-1] = 0;
		delay_ms(50);
		i++;
		
		loadWS2812B();
		
	} while (i<=LEDC);
	
	//движение назад
	i = LEDC;
	do
	{	ledred[i-1] =    0;
		ledblue[i-1] =  255;
		ledgreen[i-1] =  0;
		delay_ms(50);
		
		
		ledred[i] =   0;
		ledblue[i] =  0;
		ledgreen[i] = 0;
		delay_ms(50);
		i--;
		loadWS2812B();
		
	} while (i>=1);
	
	
	
}			



int main(void)
{
  setup_leds();   																	/* LED initialization */
	DWT_Init();																				/* Delay initialization */
 //__enable_irq();
  while (1)  
	{

		/*
		SetOutBit;											
		delay_ms(500);
		ClearOutBit; */  														/* Turn of LED */
		//delay_ms(500);
		
		//CometWhite();
		moveRed();
		moveBlue();
		//MidleGreen();
 
  }
}
