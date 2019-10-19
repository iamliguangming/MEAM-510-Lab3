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
static int adcout=0;
int adc = 11;
int main(void)
{
  m_usb_init();
  set(DDRB,7);
  set(TCCR1B,CS10);
  set(TCCR1B,CS12);
  set(TCCR1A,WGM10);
  set(TCCR1B,WGM12);
  set(TCCR1A,COM1C1);
  set(ADMUX,REFS0);
  teensy_clockdivide(0);
  set(ADCSRA,ADPS0);
  set(ADCSRA,ADPS1);
  set(ADCSRA,ADPS2);
  set(DDRC,6);
  set(TCCR3B,CS30);
  set(TCCR3B,CS32);
  set(TCCR3A,WGM30);
  set(TCCR3B,WGM32);
  set(TCCR3A,COM3A1);




  for(;;)
  {
    adc_setup(11);
    adc_read();

    // if (adc == adc1)
    // {
    //   adc = adc2;
    // }
    // else if(adc == adc2)
    // {
    //   adc = adc1;
    // }
     OCR3A = 40-(adcout*(40-7))/682;
     adc_setup(12);
     adc_read();
     OCR1C = 40-(adcout*(40-7))/682;


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
  while (!bit_is_set(ADCSRA,ADIF));
    set(ADCSRA,ADIF);
    m_usb_tx_string("\nADC");
    m_usb_tx_uint(adc);
    m_usb_tx_string("=");
    m_usb_tx_uint(ADC*5/1.024);
    adcout= ADC;
    m_usb_tx_string("mV");
}
