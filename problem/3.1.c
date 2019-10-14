/* Name: main.c
 * Author: <Yupeng Li>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file
#include "t_usb.h"//include the usb headerfile
#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10);m_usb_tx_char(13); //Print number x and start off a new line

void adc_setup(int ADCchannel);//subroutine prototype for setting up adc ADCchannel
void adc_read();//subroutine prototype for adc reading

int adc1 = 11;//adc1 is on adc channel 11
int adc2 = 12;//adc2 is on adc channel 12
int adc;//current adc port used
int main(void)//The main function
{
  m_usb_init();//initialize usb communication
  set(ADMUX,REFS0);//set voltage reference to Vcc
  teensy_clockdivide(0);//set teensy_clockdivide to 0
  set(ADCSRA,ADPS0);//set ADC frequency to 125kHz
  set(ADCSRA,ADPS1);//set ADC frequency to 125kHz
  set(ADCSRA,ADPS2);//set ADC frequency to 125kHz
  adc = adc1;//set adc1 as the first used adc port


  for(;;)//loop runs forever
  {
    adc_setup(adc);//set up the current adc
    adc_read();//read adc value
    if (adc == adc1)//if the adc channel read is adc1
    {
      adc = adc2; //switch the adc to be read to adc2
    }
    else if(adc == adc2)//if the adc channel read is adc2
    {
      adc = adc1;//swtich the channel to be read to adc1
    }
  }


    return 0;   /* never reached */
}
void adc_setup(int ADCchannel)//adc setup function
{

  if (ADCchannel == 1)//if using adc channel 1
  {
    set(DIDR0,ADC1D);//Disable the DC input on channel 1
    set(ADCSRA,ADATE);//enable triggering
    set(ADMUX,MUX0);//set the adc channel register
    clear(ADMUX,MUX1);//set the adc channel register
    clear(ADMUX,MUX2); //set the adc channel register
    clear(ADCSRB,MUX5);//set the adc channel register
  }
  /*The following if statements following the same routine of disabling DC input, enabling
  triggering and set the adc channel register*/
  if (ADCchannel == 4)
  {
    set(DIDR0,ADC4D);
    set(ADCSRA,ADATE);
    set(ADMUX,MUX2);
    clear(ADMUX,MUX1);
    clear(ADMUX,MUX0);
    clear(ADCSRB,MUX5);
  }
  if (ADCchannel == 5)
  {
    set(DIDR0,ADC5D);
    set(ADCSRA,ADATE);
    set(ADMUX,MUX2);
    clear(ADMUX,MUX1);
    set(ADMUX,MUX0);
    clear(ADCSRB,MUX5);
  }
  if (ADCchannel == 6)
  {
    set(DIDR0,ADC6D);
    set(ADCSRA,ADATE);
    clear(ADMUX,MUX0);
    set(ADMUX,MUX1);
    set(ADMUX,MUX2);
    clear(ADCSRB,MUX5);
  }
  if (ADCchannel == 7)
  {
    set(DIDR0,ADC7D);
    set(ADCSRA,ADATE);
    set(ADMUX,MUX0);
    set(ADMUX,MUX1);
    set(ADMUX,MUX2);
    clear(ADCSRB,MUX5);
  }
  if (ADCchannel == 8)
  {
    set(DIDR2,ADC8D);
    set(ADCSRA,ADATE);
    clear(ADMUX,MUX0);
    clear(ADMUX,MUX1);
    clear(ADMUX,MUX2);
    set(ADCSRB,MUX5);
  }
  if (ADCchannel == 9)
  {
    set(DIDR2,ADC9D);
    set(ADCSRA,ADATE);
    set(ADMUX,MUX0);
    clear(ADMUX,MUX1);
    clear(ADMUX,MUX2);
    set(ADCSRB,MUX5);
  }
  if (ADCchannel == 10)
  {
    set(DIDR2,ADC10D);
    set(ADCSRA,ADATE);
    clear(ADMUX,MUX0);
    set(ADMUX,MUX1);
    clear(ADMUX,MUX2);
    set(ADCSRB,MUX5);
  }
  if (ADCchannel == 11)
  {
    set(DIDR2,ADC11D);
    set(ADCSRA,ADATE);
    set(ADMUX,MUX0);
    set(ADMUX,MUX1);
    clear(ADMUX,MUX2);
    set(ADCSRB,MUX5);

  }
  if (ADCchannel == 12)
  {
    set(DIDR2,ADC12D);
    set(ADCSRA,ADATE);
    clear(ADMUX,MUX0);
    clear(ADMUX,MUX1);
    set(ADMUX,MUX2);
    set(ADCSRB,MUX5);
  }
  if (ADCchannel == 13)
  {
    set(DIDR2,ADC13D);
    set(ADCSRA,ADATE);
    set(ADMUX,MUX0);
    clear(ADMUX,MUX1);
    set(ADMUX,MUX2);
    set(ADCSRB,MUX5);
  }
}
void adc_read()//The subroutine that reads the ADC value
{
  set(ADCSRA,ADEN);//enabling ADC
  set(ADCSRA,ADSC);//Start Conversion
  if (bit_is_set(ADCSRA,ADIF))//wait for the conversion to finish
  {
    set(ADCSRA,ADIF);//clear the conversion finish flag
    m_usb_tx_string("\nAngle of the   ");//print out the angle reading
    m_usb_tx_uint(adc);//print out the angle reading
    m_usb_tx_string("th joint is    ");//print out the angle reading
    m_usb_tx_uint(ADC*0.27/1.024);//print out the angle reading
    m_usb_tx_string("   degree");//print out the angle reading
  }
}
