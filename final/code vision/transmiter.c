#include <io.h>
#include <mega32.h>
#include <delay.h>
#include <stdio.h>
unsigned char ch;
unsigned int ch_2;
unsigned int ch_3;
flash unsigned char segment[]={0b0111111,0b0000110,0b1011011,0b1001111,0b1110110,0b1101101,0b1111101,0b0000111,0b1111111,0b1101111};
unsigned int speed(void){
switch(ch)
{
case 'j':
  {
  if(OCR0<=238){
  OCR0=OCR0+17;
  return OCR0; 
  }
  else return OCR0;
  }
 case 'i': 
 {
 if(OCR0>=17)
 {
    OCR0=OCR0-17;
  return OCR0; 
  }
  else return OCR0;
 }
 case 'l':
  {
  if(OCR2<=238){
  OCR2=OCR2+17;
  return OCR2; 
  }
  else return OCR2;
  }
 case 'k': 
 {
 if(OCR2>=17)
 {
    OCR2=OCR2-17;
  return OCR2; 
  }
  else return OCR2;
 }
 } } 

 
interrupt[USART_RXC] void xy(void)

{
ch=UDR;
ch_3=0;
switch(ch)
{
case 'z':OCR0=0;OCR2=0;break; //no_action
case 'j':OCR0=speed();break;  //increase_speed_1
case 'i':OCR0=speed();break;  //decrase_speed_1
case 'k':OCR2=speed();break;  //increase_speed_2
case 'l':OCR2=speed();break;   //decrease_speed_2

//motors_direction:
//hint pin 0.1 for w motors pin 2.3 for l motors
case 'a': {PORTA=0X00; break;}       //moving circular down wright
case 'b': PORTA=0X03;break;       //moving circular up left
case 'c': PORTA=0X0C;break;    //moving circular up wright
case 'd': PORTA=0X03;break;     //moving circular down left
case 'e': {PORTA=0X03;OCR0=OCR2=170;break;}   //moving anti clockwise
case 'f': {PORTA=0X0C;OCR0=OCR2=170;break; }  //moving clockwise
case 'g': PORTA=0X0F;break;   //moving forward
case 'h': PORTA=0X00;break;   //moving reverse

}
}
interrupt[EXT_INT0] void encoder_pulses(void)
{
       if(ch_3==1);
       else
{
     switch(ch)
{
case 'g':{PORTC=segment[++ch_2];ch_3=1;break;}
case 'h':{PORTC=segment[--ch_2];ch_3=1;break;}
}
}
}

 void main (void)
{
UCSRB=(1<<RXCIE)|(1<<TXCIE)|(1<<RXEN)|(1<<TXEN);
UCSRC=(1<<URSEL)|(UCSZ1)|(1<<UCSZ1);
UBRRL=0X47;
DDRB=0X08;
DDRD=0X80;
DDRA=0XFF;
DDRC=0XFF;
PORTC=segment[0];
TCCR0=0x6D;
TCCR2=0X6F;
GICR=(1<<INT0);
MCUCR=(1<<ISC00)|(1<<ISC01);
GIFR=(1<<INTF0);

#asm("sei");
while (1)
    {
    
    }
    }
