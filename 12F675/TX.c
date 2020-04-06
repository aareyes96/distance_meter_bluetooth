#include <tx.h>
#include <math.h>

int16 val=0;

#INT_TIMER1
void  TIMER1_isr(VOID){
   for(int i=0; i<=2; i++){
      set_adc_channel(i);
      delay_Us(50);
      val=read_adc();
   
      int8 b[2]; b[0]=b[1]=0;
      b[1] = make8(val,0);
      b[0] = make8(val,1);
      putc(b[0]);
      putc(b[1]);
   }
}

void main() {
   setup_adc_ports(sAN0|sAN1|sAN2);
   setup_adc(ADC_CLOCK_INTERNAL);
   
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);//524 ms overflow
  
   enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);

   while(1){   };

}
