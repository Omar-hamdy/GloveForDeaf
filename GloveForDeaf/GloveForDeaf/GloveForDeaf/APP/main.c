/*
 * GloveForDeaf.c
 *
 * Created: 2/4/2023 6:49:28 PM
 * Author : Lenovo
 */ 

#include "main.h"



int main(void)
{
	//Array for fingers
	 Uint8_t arr[5];
	 
	 //we were using variable for each finger
	 /*
	 uint8_t F1=0;
	 uint8_t F2=0;
	 uint8_t F3=0;
	 uint8_t F4=0;
	 uint8_t F5=0;
	 */
	 
	 
	

	//lcd, adc init
	LCD_Initialize();
	LCD_Clear();
	ADC_Initialization(AVCC, ADC_PRE128);
	//avcc to choose same micro controller voltage
	//pre scalar 128 to make sure freq below 200khz
	
	//output pins to choose whether sensor is powered..
	//when 2 sensors are connected to same adc pin
	DIO_SetPin_Direction(DIO_PORTC, DIO_PIN3, DIO_OUTPUT);
	DIO_SetPin_Direction(DIO_PORTC, DIO_PIN4, DIO_OUTPUT);
	DIO_SetPin_Direction(DIO_PORTC, DIO_PIN5, DIO_OUTPUT);
	DIO_SetPin_Direction(DIO_PORTC, DIO_PIN6, DIO_OUTPUT);
	
    while (1) 
    {
		
		_delay_ms(200);//program delay
		
		
		//fingers readings
		//channel 0
		//finger 1
		DIO_SetPin_Value(DIO_PORTC, DIO_PIN3, DIO_HIGH);
		_delay_ms(100);//wait for voltage high
		(ADC_Read(ADC_CH0)*5)/1024;//neglect first conversion (channel selection problem)
		_delay_ms(1);
		arr[0] = (ADC_Read(ADC_CH0)*5)/1024;
		DIO_SetPin_Value(DIO_PORTC, DIO_PIN3, DIO_LOW);
		
		//finger 2
		DIO_SetPin_Value(DIO_PORTC, DIO_PIN4, DIO_HIGH);
		_delay_ms(100);
		(ADC_Read(ADC_CH0)*5)/1024;//neglect first conversion
		_delay_ms(1);
		arr[1] = (ADC_Read(ADC_CH0)*5)/1024;
		DIO_SetPin_Value(DIO_PORTC, DIO_PIN4, DIO_LOW);
		
		//channel 2
		(ADC_Read(ADC_CH2)*5)/1024;//neglect
		_delay_ms(1);
		//finger 3
		arr[2] = (ADC_Read(ADC_CH2)*5)/1024;
		
		//channel 3
		//finger 4
		DIO_SetPin_Value(DIO_PORTC, DIO_PIN5, DIO_HIGH);
		_delay_ms(100);
		(ADC_Read(ADC_CH3)*5)/1024;//neglect
		_delay_ms(1);
		arr[3] = (ADC_Read(ADC_CH3)*5)/1024;
		DIO_SetPin_Value(DIO_PORTC, DIO_PIN5, DIO_LOW);
		
		//finger 5
		DIO_SetPin_Value(DIO_PORTC, DIO_PIN6, DIO_HIGH);
		_delay_ms(100);
		(ADC_Read(ADC_CH3)*5)/1024;//neglect
		_delay_ms(1);
		arr[4] = (ADC_Read(ADC_CH3)*5)/1024;
		DIO_SetPin_Value(DIO_PORTC, DIO_PIN6, DIO_LOW);
		
		
		
		//write on lcd how much do fingers bent	
		
		//we were displaying finger variables
		/*
		LCD_Write_Number(F1);
		LCD_Write_Number(F2);
		LCD_Write_Number(F3);
		LCD_Write_Number(F4);
		LCD_Write_Number(F5);
		*/
		
		 
		char str1[5]; //string contains individual characters ex: {4},{3},{2},...
		char str2[5]; //string contains all numbers in one string ex: 43214
		
		sprintf( (char*)str1,"%d", arr[0]);		//converts numbers in array to characters
		strcat(str2,str1);						//concatenate numbers together in one string 
		sprintf( (char*)str1,"%d", arr[1]);
		strcat(str2,str1);
		sprintf( (char*)str1,"%d", arr[2]);
		strcat(str2,str1);
		sprintf( (char*)str1,"%d", arr[3]);
		strcat(str2,str1);
		sprintf( (char*)str1,"%d", arr[4]);
		strcat(str2,str1);
		 
		 Uint16_t x=0;
		 x = atoi(str2);					//converts string into one number
		LCD_Clear(); //clear display every loop
		LCD_Write_String((Uint8_t*)str2);				//write how much each finger bent from 0 to 4
											//0 for straight, 1 or 2 or 3 for slightly bent, 4 for max bent
		LCD_Write_Character(' ');
		LCD_Write_Number(x);				//displaying converted number for testing switch cases

		
		//deaf signs
		//each x value has a sign
		//problem:  we make sure that sign do not interfere with each others
		//solved 
		switch(x)
		{
			case 0:
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"HELLO");
			break;
			case 440:
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"I LOVE YOU");
			break;
			case 40:
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"I REALLY LOVE YOU");
			break;
			case 40444:
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"YOU");
			break;
			case 44444:
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"YES");
			break;
			case 1144 ... 3344:
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"NO");
			break;
			case 11000 ... 33000:
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"PERFECT");
			break;
			case 4444:
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"GOOD JOB");
			break;
			case 41444 || 42444 || 43444:
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"QESTION?");
			break;
			case 41144 ... 43344:
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"QOUTES");
			break;
			default:
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"LOADING..");
			break;
		}
		
		// we were using if condition with finger variables
		/*
		if(F1==0 && F2==0 && F3==0 && F4==0 && F5==0)
		{
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"HELLO");
		}
		else if(F1==0 && F2==0 && F3==4 && F4==4 && F5==0)
		{
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"I LOVE YOU");
		}
		else if(F1==0 && F2==0 && F3==0 && F4==4 && F5==0)
		{
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"I REALLY LOVE YOU");
		}
		else if(F1==4 && F2==0 && F3==4 && F4==4 && F5==4)
		{
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"YOU");
		}
		else if(F1==4 && F2==4 && F3==4 && F4==4 && F5==4)
		{
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"YES");
		}
		
		else if(F1==0 && (F2==1||F2==2||F2==3) && (F3==1 ||F3==2||F3==3) && F4==4 && F5==4)
		{
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"NO");
		}

		else if((F1==1||F1==2||F1==3) && (F2==1||F2==2||F2==3) && F3==0 && F4==0 && F5==0)
		{
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"PERFECT");
		}

		else if(F1==0 && F2==4 && F3==4 && F4==4 && F5==4)
		{
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"GOOD JOB");
		}
		
		else if(F1==4 && (F2==1||F2==2||F2==3) && F3==4 && F4==4 && F5==4)
		{
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"QESTION?");
		}
		
		else if(F1==4 && (F2==1||F2==2||F2==3) && (F3==1 ||F3==2||F3==3) && F4==4 && F5==4)
		{
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"QOUTES");
		}
		else
		{
			LCD_Write_Command(0xC0);
			LCD_Write_String((Uint8_t*)"LOADING..");
		}
		*/ 
		/*
		F1=0;
		F2=0;
		F3=0;
		F4=0;
		F5=0;
		*/
		
		
		//zeroing the values to avoid overwrite
		arr[0]=0;
		arr[1]=0;
		arr[2]=0;
		arr[3]=0;
		arr[4]=0;
		
		*str1=0;
		*str2=0;
		
		x=0;
		

    }
}

