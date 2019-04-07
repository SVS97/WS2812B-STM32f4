#include "stm32f4xx.h"
#include <stdlib.h>


#define LED_PWM (1 << 15) 		/* port D, pin 15 */
#define LEDC			93					// Should be 1 or greater
#define PORTOUT			GPIOD				// port for WS2812B
#define ClearOutBit		(PORTOUT->ODR = 0); //0 to output
#define SetOutBit		(PORTOUT->ODR = LED_PWM);   //1  to output

#define RED				0x0F				// red initialization
#define GREEN			0xF0				// green initialization
#define BLUE			0x55				// blue initialization

#define    DWT_CYCCNT    *(volatile unsigned long *)0xE0001004
#define    DWT_CONTROL   *(volatile unsigned long *)0xE0001000
#define    SCB_DEMCR     *(volatile unsigned long *)0xE000EDFC
	
unsigned char ledred[LEDC+1] ;		// array of red
unsigned char ledblue[LEDC+1] ;		// array of blue
unsigned char ledgreen[LEDC+1];		// array of green


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
	// reset formation
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
			// byte loading
			if(temp&0x80)
			{
				//formation of bit 1
				SetOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				ClearOutBit;
				__nop();
			}
			else
			{
				//formation of bit 0
				SetOutBit;
				__nop();__nop();__nop();__nop();
				ClearOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
			}
			
			if(temp&0x40)
			{
				//formation of bit 1
				SetOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				ClearOutBit;
				__nop();
			}
			else
			{
				//formation of bit 0
					SetOutBit;
				__nop();__nop();__nop();__nop();
					ClearOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
			}
			
			if(temp&0x20)
			{
				//formation of bit 1
				SetOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				ClearOutBit;
				__nop();
			}
			else
			{
				//formation of bit 0
					SetOutBit;
				__nop();__nop();__nop();__nop();
					ClearOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
			}
			if(temp&0x10)
			{
				//formation of bit 1
				SetOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				ClearOutBit;
				__nop();
			}
			else
			{
				//formation of bit 0
					SetOutBit;
				__nop();__nop();__nop();__nop();
					ClearOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
			}
			if(temp&0x8)
			{
				//formation of bit 1
				SetOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				ClearOutBit;
				__nop();
			}
			else
			{
				//formation of bit 0
					SetOutBit;
				__nop();__nop();__nop();__nop();
					ClearOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
			}
			
			if(temp&0x4)
			{
				//formation of bit 1
				SetOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				ClearOutBit;
				__nop();
			}
			else
			{
				//formation of bit 0
					SetOutBit;
				__nop();__nop();__nop();__nop();
					ClearOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
			}
			if(temp&0x2)
			{
				//formation of bit 1
				SetOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				ClearOutBit;
				__nop();
			}
			else
			{
				//formation of bit 1
					SetOutBit;
				__nop();__nop();__nop();__nop();
					ClearOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
			}
			
			if(temp&0x1)
			{
				//formation of bit 1
				SetOutBit;
				__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
				ClearOutBit;
				__nop();
			}
			else
			{
				//formation of bit 0
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
	
	//forward movement
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
	//disabling the last 4 LED
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
	
		//forward movement
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
		
		//back movement
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
	
	//forward movement
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
	//disabling last and first LED
	ledred[0] =  0;
	ledblue[0] = 0;
	ledgreen[0]= 0;
	
	
	ledred[LEDC] =  0;
	ledblue[LEDC] = 0;
	ledgreen[LEDC]= 0;
		
	//back movement
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
	
	
	
	ledred[LEDC - 1] =  0;
	ledblue[LEDC - 1] = 0;
	ledgreen[LEDC - 1]= 0;
	
	
	ledred[LEDC] =  0;
	ledblue[LEDC] = 0;
	ledgreen[LEDC]= 0;
	
}

void moveBlue (void)
{
	
	//forward moving
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
	
	//back moving
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
