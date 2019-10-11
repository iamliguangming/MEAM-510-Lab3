/* Name: main.c
 * Author: <Yupeng Li>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file
#include "t_usb.h"//include the usb headerfile
#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10);m_usb_tx_char(13); //Print number x and start off a new line

void adc_setup(int ADCchannel);
void adc_read();

int adc1 = 11;
int adc2 = 12;
int adc;
int main(void)
{
  m_usb_init();
  set(ADMUX,REFS0);
  teensy_clockdivide(0);
  set(ADCSRA,ADPS0);
  set(ADCSRA,ADPS1);
  set(ADCSRA,ADPS2);
  adc = adc1;


  for(;;)
  {
    adc_setup(adc);
    adc_read();
    if (adc == adc1)
    {
      adc = adc2;
    }
    else if(adc == adc2)
    {
      adc = adc1;
    }
  }


    return 0;   /* never reached */
}
void adc_setup(int ADCchannel)
{
  if (ADCchannel == 1)
  {
    set(DIDR0,ADC1D);
    set(ADCSRA,ADATE);
    set(ADMUX,MUX0);
    clear(ADMUX,MUX1);
    clear(ADMUX,MUX2);
    clear(ADCSRB,MUX5);
  }
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
void adc_read()
{
  set(ADCSRA,ADEN);
  set(ADCSRA,ADSC);
  if (bit_is_set(ADCSRA,ADIF))
  {
    set(ADCSRA,ADIF);
    m_usb_tx_string("\nADC");
    m_usb_tx_uint(adc);
    m_usb_tx_string("=");
    m_usb_tx_uint(ADC*5/1.024);
    m_usb_tx_string("mV");
  }
}
