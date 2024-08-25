#include<avr/io.h>
char tosend[4]="Test";

void spi_setup()
{
  DDRB=(1<<PB1)|(1<<PB2);     //Setting direction of PB1 and PB2 as output
  USICR=(1<<USIWM0);          //Choosing SPI aka three wire mode
}

int sub_main()
{
  short int i=0;
  spi_setup();
  for(i=0;i<=3;i++)
  {
   USIDR=tosend[i];          //Writing data bytes in Data register
   while(USIOIF==0)         //Checking USI data counter overflow flag to detect the end of transmission every byte
   {
    USICR|=(1<<USICLK)|(1<<USITC);  //Enabling clock for transmission and generating clock for slave device
   }
   USISR|=(1<<USIOIF);             //Clearing counter overflow flag
  }
}