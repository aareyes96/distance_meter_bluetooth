#include <12F675.h>

#device ADC=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#fuses INTRC_IO    //Internal RC Osc, no CLKOUT
#fuses PUT         //Power Up Timer
#fuses NOMCLR      //Master Clear pin used for I/O

#use delay(internal=4000000)
#use FIXED_IO( A_outputs=PIN_A4,PIN_A0 )
#use rs232(baud=9600,parity=N,xmit=PIN_A0,rcv=PIN_A1,bits=8,stream=PORT1)

#define TRIGGER   PIN_A4 
#define ECHO      PIN_A5 

int16 t = 0;
int16 d = 0;
int8 carrier = 0;
int16 out=0;
int16 fall=0;
signed int8 celcius=0;

void medir(void)
{
   output_high(TRIGGER);
   delay_us(20);
   output_low(TRIGGER);
      
   while (!input_state(ECHO)){}
      
   set_timer1(0);
   while (input_state(ECHO)){}
      
   t = get_timer1();
      
   //d = t*(0.01655 + (0.00003*celcius));
   d = t*0.017;
      
   printf("D:%lu T:%d\n",d, celcius);
      
   delay_ms(30);
}

void temperature(void)
{
   set_adc_channel(1);
   delay_us(100);
   out=read_adc();
   
   set_adc_channel(2);
   delay_us(100);
   fall=read_adc();
   
   celcius=(out-fall)*0.488758;
}

void main()
{
   setup_adc_ports(2|4);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);      //65,5 ms overflow

   
   while(TRUE)
   {
      delay_ms(100);
      temperature();
      medir();
   }

}


