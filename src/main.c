/* Name: main.c
 * Author: <Yupeng Li>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "teensy_general.h"  // includes the resources included in the teensy_general.h file
#include "t_usb.h"//include the usb headerfile
#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10);m_usb_tx_char(13); //Print number x and start off a new line

void adc_setup(int ADCchannel);//Subroutine takes in ADC number and setup the designated ADC channel
void adc_read();//Subroutine which reads the current ADC channel
static int adcout=0;//a static integer used to store the adc value from the subroutine
int main(void)//the main loop
{
  m_usb_init();//initialize usb communication
  set(DDRB,7);//set B7 as output pin
  set(TCCR1B,CS10);//set 1024 prescalar for timer 1
  set(TCCR1B,CS12);//set 1024 prescalar for timer 1
  set(TCCR1A,WGM10);//set the timer 1 to work in mode5
  set(TCCR1B,WGM12);//set the timer 1 to work in mode5
  set(TCCR1A,COM1C1);//set 1C to clear at OCR1C and set at rollover
  set(ADMUX,REFS0);//set the reference voltage of ADC to be Vcc
  teensy_clockdivide(0);//set the default clock frequency to be 16MHz
  set(ADCSRA,ADPS0);//set the ADC prescalar to be /128 (125kHz)
  set(ADCSRA,ADPS1);//set the ADC prescalar to be /128 (125kHz)
  set(ADCSRA,ADPS2);//set the ADC prescalar to be /128 (125kHz)
  set(DDRC,6);//set C6 as the output pin
  set(TCCR3B,CS30);//set /1024 prescalar for timer 3
  set(TCCR3B,CS32); //set /1024 prescalar for timer 3
  set(TCCR3A,WGM30);//set timer 3 to work in mode 5
  set(TCCR3B,WGM32);//set timer 3 to work in mode 5
  set(TCCR3A,COM3A1);//set timer 3A to clear at OCR3A and set at rollover




  for(;;)//loop runs forever
  {
    adc_setup(11);//setup ADC11 B4
    adc_read();//read the input from ADC11 using the subroutine
    OCR3A = 40-(adcout*(40-7))/682;//based on testing, at 7 tick the servo goes to right dead end and at 40 ticks the servo goes to left dead end
    adc_setup(12);//set up ADC12 B5
    adc_read();//read the input from ADC12 using the subroutine
    OCR1C = 40-(adcout*(40-7))/682;


  }


    return 0;   /* never reached */
}
void adc_setup(int ADCchannel)//the subroutine which takes in the ADC channel number
{

  if (ADCchannel == 1)//if using adc channel 1
  {

    set(DIDR0,ADC1D);//Disable the DC input on channel 1
    set(ADCSRA,ADATE);//enable triggering
    set(ADMUX,MUX0);//set the adc channel register
    clear(ADMUX,MUX1);//set the adc channel register
    clear(ADMUX,MUX2);//set the adc channel register
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
void adc_read()//the subroutine which reads ADC value
{
  set(ADCSRA,ADEN);//enabling ADC
  set(ADCSRA,ADSC);//starting conversion
  while (!bit_is_set(ADCSRA,ADIF));//wait for the conversion to finish
    set(ADCSRA,ADIF);//clear the conversion complete flag
    // m_usb_tx_string("\nADC");
    // m_usb_tx_uint(adc);
    // m_usb_tx_string("=");
    // m_usb_tx_uint(ADC*5/1.024);
    adcout= ADC;//update the static integer value for the ADC output
    // m_usb_tx_string("mV");
}
