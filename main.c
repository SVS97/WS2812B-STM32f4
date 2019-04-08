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
				break;
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
	unsigned char i = 5;
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
		
		delay_ms(80);
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
			delay_ms(30);
			
			ledred[i-1] =  0;
			ledblue[i-1] = 0;
			ledgreen[i-1]= 0;
			delay_ms(30);
			i++;
			
			loadWS2812B();
			
		} while (i<=LEDC);
		
		//back movement
		 i = LEDC;
		do
		{	ledred[i-1] = 250;
			ledblue[i-1] =   0;
			ledgreen[i-1] =  0;
			delay_ms(15);
			
			
			ledred[i] =      0;
			ledblue[i] =     0;
			ledgreen[i] =    0;
			delay_ms(15);
			i--;
			loadWS2812B();
			
		} while (i>0);
	
	ledred[0] =      0;
	ledblue[0] =     0;
	ledgreen[0] =    0;
	
}

void moveBlue (void)
{
	
	//forward moving
	unsigned char i = 2;
	do
	{	ledred[i] =  0;
		ledblue[i] =  255;
		ledgreen[i] =  0;
		delay_ms(30);
		
		ledred[i-1] =   0;
		ledblue[i-1] =  0;
		ledgreen[i-1] = 0;
		delay_ms(30);
		i++;
		
		loadWS2812B();
		
	} while (i<=LEDC);
	
	//back moving
	i = LEDC;
	do
	{	ledred[i-1] =    0;
		ledblue[i-1] =  255;
		ledgreen[i-1] =  0;
		delay_ms(15);
		
		
		ledred[i] =   0;
		ledblue[i] =  0;
		ledgreen[i] = 0;
		delay_ms(15);
		i--;
		loadWS2812B();
		
	} while (i>=1);
	
	
	
}	

void moveGreen (void)
{
	
	//forward moving
	unsigned char i = 2;
	do
	{	ledred[i] =  0;
		ledblue[i] =  0;
		ledgreen[i] =  255;
		delay_ms(30);
		
		ledred[i-1] =   0;
		ledblue[i-1] =  0;
		ledgreen[i-1] = 0;
		delay_ms(30);
		i++;
		
		loadWS2812B();
		
	} while (i<=LEDC);
	
	//back moving
	i = LEDC;
	do
	{	ledred[i-1] =    0;
		ledblue[i-1] =  0;
		ledgreen[i-1] =  255;
		delay_ms(15);
		
		
		ledred[i] =   0;
		ledblue[i] =  0;
		ledgreen[i] = 0;
		delay_ms(15);
		i--;
		loadWS2812B();
		
	} while (i>=1);
	
	for (int i = 0; i < LEDC; i++)
	{
		ledred[i] =   0;
		ledblue[i] =  0;
		ledgreen[i] = 0;
		

		loadWS2812B();
	
	}
}	

void moveWhite (void)
{
		ledred[0] =  0;
		ledblue[0] =  0;
		ledgreen[0] =  0;
	
	//forward moving
	unsigned char i = 2;
	do
	{	ledred[i] =  255;
		ledblue[i] =  255;
		ledgreen[i] =  255;
		delay_ms(30);
		
		ledred[i-1] =   0;
		ledblue[i-1] =  0;
		ledgreen[i-1] = 0;
		delay_ms(30);
		i++;
		
		loadWS2812B();
		
	} while (i<=LEDC);
	
	//back moving
	i = LEDC;
	do
	{	ledred[i-1] =    255;
		ledblue[i-1] =  255;
		ledgreen[i-1] =  255;
		delay_ms(15);
		
		
		ledred[i] =   0;
		ledblue[i] =  0;
		ledgreen[i] = 0;
		delay_ms(15);
		i--;
		loadWS2812B();
		
	} while (i>=1);
	ledred[0] =   0;
	ledblue[0] =  0;
	ledgreen[0] = 0;
}	

void MidleGreen (void)
{
		ledred[0] =    0;
		ledblue[0] =   0;
		ledgreen[0] =  0;
	//forward movement
	unsigned char i = LEDC/2;
	unsigned char j = LEDC/2;
	do
	{	ledred[i] =    0;
		ledblue[i] =   0;
		ledgreen[i] =  255;
		delay_ms(25);
		
		ledred[i-1] =  0;
		ledblue[i-1] = 0;
		ledgreen[i-1]= 0;
		delay_ms(25);
		i++;
		
		loadWS2812B();
		
		
		ledred[j-1] =    0;
		ledblue[j-1] =   0;
		ledgreen[j-1] =  255;
		delay_ms(25);
		
		
		ledred[j] =      0;
		ledblue[j] =     0;
		ledgreen[j] =    0;
		delay_ms(25);
		j--;
		loadWS2812B();
		
	} while (i<LEDC);
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
		
	} while (i>LEDC/2);
	while (j<LEDC/2);
	
	
	
	ledred[LEDC/2 + 1] =  0;
	ledblue[LEDC/2 + 1] = 0;
	ledgreen[LEDC/2 + 1]= 0;
	
	
	ledred[LEDC/2] =  0;
	ledblue[LEDC/2] = 0;
	ledgreen[LEDC/2]= 0;
	
}

		

void lightningBlue (void)
{
	
	//���������
	unsigned char i = 0;
	do
	{	ledred[i] =   0;
		ledblue[i] =  255;
		ledgreen[i] = 0;
		delay_ms(30);
				
		
		i++;
		
		loadWS2812B();
		
	} while (i<=LEDC);
	
	for(int j = 0; j < 5; j++)
	{
	//�������
		
	 i = 0;
	do
	{	ledred[i] =   0;
		ledblue[i] =  0;
		ledgreen[i] = 0;
		i++;
		loadWS2812B();
	} while (i<=LEDC);
	delay_ms(30);
	
	//���������
	i = 0;
	do
	{	ledred[i] =   0;
		ledblue[i] =  255;
		ledgreen[i] = 0;
		//delay_ms(50);
				
		
		i++;
		
		loadWS2812B();
		
	} while (i<=LEDC);
	delay_ms(30);
	
}
	//�������
	 i = 0;
	do
	{	ledred[i] =   0;
		ledblue[i] =  0;
		ledgreen[i] = 0;
		delay_ms(30);

		i++;
		
		loadWS2812B();
		
	} while (i<=LEDC);

}




volatile void RelightningWhite (void)
{

	/*���������
	j - �������
	i - ���-�� ������
	*/
	volatile unsigned char j = 0;
	do 
	{
	
		volatile unsigned char i = 0;
		do
		{	ledred[i] =   j;
			ledblue[i] =  j;
			ledgreen[i] = j;
	    delay_us(50);
				
			i++;
		
		loadWS2812B();	
		
		} while (i<=LEDC);
		
	j = j + 10;
	
	} while (j<250); 

	//�������
	 j = 250;
	do
	{
		
		volatile unsigned char i = 0;
		do
		{	ledred[i] =   j;
			ledblue[i] =  j;
			ledgreen[i] = j;
			delay_us(50);
			
			
			i++;
			
			loadWS2812B();
			
		} while (i<=LEDC);
		
		j = j - 10;
		
	} while (j>0);
	
	for (int i = 0; i < LEDC; i++)
	{
		ledred[i] =   0;
		ledblue[i] =  0;
		ledgreen[i] = 0;
		

		loadWS2812B();
	
	}
	
}


void ColorLight (void)
{
	unsigned char n = 0;
	do
	{
	//���������
	
	unsigned char i = 0;
	unsigned char j = 1;
	unsigned char k = 2;

	do
	{	ledred[k] =   0;
		ledblue[i] =  0;
		ledgreen[j] = 0;
		
		ledred[i] =   255;
		ledblue[j] =  255;
		ledgreen[k] = 255;
		delay_us(100);

		i=i+3;
		j=j+3;
		k=k+3;

		loadWS2812B();
		
	} while (i<=LEDC);

	i = 0;
	j = 1;
	k = 2;
	
	do
	{	ledred[i] =   0;
		ledblue[j] =  0;
		ledgreen[k] = 0;

		ledred[j] =   255;
		ledblue[k] =  255;
		ledgreen[i] = 255;
		delay_us(100);

		i=i+3;
		j=j+3;
		k=k+3;
		
		loadWS2812B();
		
	}while (i<=LEDC);

	i = 0;
	j = 1;
	k = 2;
	do
	{	ledred[j] =   0;
		ledblue[k] =  0;
		ledgreen[i] = 0;
				
		
		ledred[k] =   255;
		ledblue[i] =  255;
		ledgreen[j] = 255;

		delay_us(100);

		i=i+3;
		j=j+3;
		k=k+3;

		loadWS2812B();

	}while (i<=LEDC);
n++;
	}while (n<=50);
	
	for (int i = 0; i < LEDC; i++)
	{
		ledred[i] =   0;
		ledblue[i] =  0;
		ledgreen[i] = 0;
		

		loadWS2812B();
	
	}
	
}




void flash (void)
{
	int i = 0;

do 
{
		ledred[i] =   0;
		ledblue[i] =  0;
		ledgreen[i] = 255;
		delay_ms(15);
	
		ledred[i+32] =   0;
		ledblue[i+32] =  0;
		ledgreen[i+32] = 255;
		delay_ms(15);
	
		ledred[i+56] =   0;
		ledblue[i+56] =  0;
		ledgreen[i+56] = 255;
		delay_ms(15);
		loadWS2812B();
	i++;
} while(i < 38);
	
	delay_ms(50);
	i = LEDC;
	do
	{			
		ledred[i] =   0;
		ledblue[i] =  0;
		ledgreen[i] = 0;

		i--;
		loadWS2812B();
		
	} while (i>=1);
	
	for (int i = 0; i < LEDC; i++)
	{
		ledred[i] =   0;
		ledblue[i] =  0;
		ledgreen[i] = 0;
		

		loadWS2812B();
	
	}

}


void slash (void)
{

	for (int i = 0; i < LEDC; i++)
	{
		if ((i==0) || (i==1) || (i==2) || (i==3) || (i==4) || (i==5) || (i==6) || (i==7) || (i==8) || (i==16) || (i==17) || (i==18) || (i==19) || (i==20) || (i==21) || (i==22) || (i==23) || (i==24)
		|| (i==32) || (i==33) || (i==34) || (i==35) || (i==36) || (i==37) || (i==38) || (i==44) || (i==45) || (i==46) || (i==47) || (i==48) || (i==49) || (i==50) || (i==56) || (i==57) || (i==58) || 
		(i==59) || (i==60) || (i==64) || (i==65) || (i==66)	|| (i==67) || (i==68) || (i==72) || (i==73) || (i==74) || (i==75) || (i==78) || (i==79) || (i==80) || (i==81) ||   (i==84) || (i==85) || (i==86) 
		|| (i==87) || (i==89) || (i==90) || (i==91))
		{
		ledred[i] =   0;
		ledblue[i] =  255;
		ledgreen[i] = 0;
		}
		delay_us(60);
		loadWS2812B();
	}
	for (int i = 0; i < LEDC+1; i++)
	{
		if ((i==9) || (i==10) || (i==11) || (i==12) || (i==13) || (i==14) || (i==15) || (i==25) || (i==26) || (i==26) || (i==27) || (i==28) || (i==29) || (i==30) || (i==31) || (i==39) || (i==40) || (i==41)
		|| (i==42) || (i==43) || (i==51) || (i==52) || (i==53) || (i==54) || (i==55) || (i==61) || (i==62) || (i==63) || (i==69) || (i==70) || (i==71) || (i==76) || (i==77) || (i==82) || (i==83) || 
		(i==88) || (i==92))
		{
		ledred[i] =   255;
		ledblue[i] =  0;
		ledgreen[i] = 0;
		}
		delay_us(60);
		loadWS2812B();
	}
		
	
	for (int i = 0; i < LEDC; i++)
	{
		ledred[i] =   0;
		ledblue[i] =  0;
		ledgreen[i] = 0;
		

		loadWS2812B();
	
	}
	
	
	
	for (int i = 0; i < LEDC; i++)
	{
		if ((i==0) || (i==1) || (i==2) || (i==3) || (i==4) || (i==5) || (i==6) || (i==7) || (i==8) || (i==16) || (i==17) || (i==18) || (i==19) || (i==20) || (i==21) || (i==22) || (i==23) || (i==24)
		|| (i==32) || (i==33) || (i==34) || (i==35) || (i==36) || (i==37) || (i==38) || (i==44) || (i==45) || (i==46) || (i==47) || (i==48) || (i==49) || (i==50) || (i==56) || (i==57) || (i==58) || 
		(i==59) || (i==60) || (i==64) || (i==65) || (i==66)	|| (i==67) || (i==68) || (i==72) || (i==73) || (i==74) || (i==75) || (i==78) || (i==79) || (i==80) || (i==81) ||   (i==84) || (i==85) || (i==86) 
		|| (i==87) || (i==89) || (i==90) || (i==91))
		{
		ledred[i] =   255;
		ledblue[i] =  0;
		ledgreen[i] = 0;
		}
		delay_us(60);
		loadWS2812B();
	}
	for (int i = 0; i < LEDC+1; i++)
	{
		if ((i==9) || (i==10) || (i==11) || (i==12) || (i==13) || (i==14) || (i==15) || (i==25) || (i==26) || (i==26) || (i==27) || (i==28) || (i==29) || (i==30) || (i==31) || (i==39) || (i==40) || (i==41)
		|| (i==42) || (i==43) || (i==51) || (i==52) || (i==53) || (i==54) || (i==55) || (i==61) || (i==62) || (i==63) || (i==69) || (i==70) || (i==71) || (i==76) || (i==77) || (i==82) || (i==83) || 
		(i==88) || (i==92))
		{
		ledred[i] =   0;
		ledblue[i] =  0;
		ledgreen[i] = 255;
		}
		delay_us(60);
		loadWS2812B();
	}
	
	for (int i = 0; i < LEDC; i++)
	{
		ledred[i] =   0;
		ledblue[i] =  0;
		ledgreen[i] = 0;
		

		loadWS2812B();
	
	}
	
	
	
	
		for (int i = 0; i < LEDC; i++)
	{
		if ((i==0) || (i==1) || (i==2) || (i==3) || (i==4) || (i==5) || (i==6) || (i==7) || (i==8) || (i==16) || (i==17) || (i==18) || (i==19) || (i==20) || (i==21) || (i==22) || (i==23) || (i==24)
		|| (i==32) || (i==33) || (i==34) || (i==35) || (i==36) || (i==37) || (i==38) || (i==44) || (i==45) || (i==46) || (i==47) || (i==48) || (i==49) || (i==50) || (i==56) || (i==57) || (i==58) || 
		(i==59) || (i==60) || (i==64) || (i==65) || (i==66)	|| (i==67) || (i==68) || (i==72) || (i==73) || (i==74) || (i==75) || (i==78) || (i==79) || (i==80) || (i==81) ||   (i==84) || (i==85) || (i==86) 
		|| (i==87) || (i==89) || (i==90) || (i==91))
		{
		ledred[i] =   255;
		ledblue[i] =  0;
		ledgreen[i] = 0;
		}
		delay_us(60);
		loadWS2812B();
	}
	for (int i = 0; i < LEDC+1; i++)
	{
		if ((i==9) || (i==10) || (i==11) || (i==12) || (i==13) || (i==14) || (i==15) || (i==25) || (i==26) || (i==26) || (i==27) || (i==28) || (i==29) || (i==30) || (i==31) || (i==39) || (i==40) || (i==41)
		|| (i==42) || (i==43) || (i==51) || (i==52) || (i==53) || (i==54) || (i==55) || (i==61) || (i==62) || (i==63) || (i==69) || (i==70) || (i==71) || (i==76) || (i==77) || (i==82) || (i==83) || 
		(i==88) || (i==92))
		{
		ledred[i] =   0;
		ledblue[i] =  255;
		ledgreen[i] = 0;
		}
		delay_us(60);
		loadWS2812B();
	}
	
	for (int i = 0; i < LEDC; i++)
	{
		ledred[i] =   0;
		ledblue[i] =  0;
		ledgreen[i] = 0;
		

		loadWS2812B();
	
	}
	
		
	
}


int main(void)
{
  setup_leds();   																	/* LED initialization */
	DWT_Init();																				/* Delay initialization */
  while (1)  
	{

		
		CometWhite();
		MidleGreen();
		moveRed();
		lightningBlue();
		moveWhite();
		RelightningWhite();
		moveBlue();
		ColorLight();
		flash();
		flash();
		moveGreen();
		slash();
		slash();
 
  }
}
