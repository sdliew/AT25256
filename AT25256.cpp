#include    "AT25256.h"

void AT25256::begin() 
{
//  byte clr;
//  DDRB |= (1<<5) | (1<<3);
  /*Enable SPI as master, and SCK f/16*/
  SPCR = (1<<SPE) | (1<<MSTR);// | (1<<SPR0);
//  clr = SPSR;
//  clr = SPDR;
  delay(10);
}

u_char AT25256::SPI_transmit( u_char data )
{
   SPDR = data;
   
   /*Wait for transmission to complete*/
   while(!(SPSR & (1<<SPIF)));
   
   return SPDR;
}

void AT25256::write_enable()
{
  digitalWrite(SLAVESELECT,LOW);  //enableable device
  SPI_transmit(AT25_WREN_CMD);    //write enable instruction
  digitalWrite(SLAVESELECT,HIGH); //disable device
  delay(10);
}

u_char AT25256::read_status_register()
{
  u_char data = 0;
  digitalWrite(SLAVESELECT,LOW);  //enableable device
  data = SPI_transmit(AT25_RDSR_CMD);    //read status registry
  digitalWrite(SLAVESELECT,HIGH); //disable device
  delay(10);
  return data;
}

void AT25256::write_status_register(u_char data)
{
  digitalWrite(SLAVESELECT,LOW);  //enableable device
  SPI_transmit(AT25_WRSR_CMD);    //write instruction
  SPI_transmit(data);
  digitalWrite(SLAVESELECT,HIGH); //disable device
  delay(10);
}


void AT25256::write_byte( u_short address, u_char data )
{

  digitalWrite(SLAVESELECT,LOW);
  SPI_transmit(AT25_WRITE_CMD); //write instruction

  //Send next page of data
  SPI_transmit((address & 0x0FF00) >> 8);   //send MSByte address first
  SPI_transmit(address & 0x0FF);      //send LSByte address
  SPI_transmit(data);
  digitalWrite(SLAVESELECT,HIGH); //release chip
  delay(10);
}

void AT25256::write_page( u_short address, u_char *data )
{
  int i;
  u_char *ptr = data;
  digitalWrite(SLAVESELECT,LOW);
  SPI_transmit(AT25_WRITE_CMD); //write instruction

  //Send next page of data
  SPI_transmit((address & 0x0FF00) >> 8);   //send MSByte address first
  SPI_transmit(address & 0x0FF);      //send LSByte address
  
  for (i=0;(*ptr != 0) && (i<PAGESIZE);i++)
    SPI_transmit(*ptr++);

  digitalWrite(SLAVESELECT,HIGH); //release chip
  delay(10);
}

u_char AT25256::read_byte( u_short address, u_char data )
{
  digitalWrite(SLAVESELECT,LOW);
  SPI_transmit(AT25_READ_CMD);
  SPI_transmit((address & 0x0FF00) >> 8);  
  SPI_transmit(address & 0x0FF);  
  data = SPI_transmit(0xFF);  
  digitalWrite(SLAVESELECT,HIGH);
  
  return data;
}

int AT25256::read_page( u_short address, u_char *data )
{
  int i;

  digitalWrite(SLAVESELECT,LOW);
  SPI_transmit(AT25_READ_CMD); //read instruction

  //Send next page of data
  SPI_transmit((address & 0x0FF00) >> 8);   //send MSByte address first
  SPI_transmit(address & 0x0FF);      //send LSByte address
  
  for (i=0;(i<PAGESIZE);i++)
    data[i] = SPI_transmit(0xFF);

  digitalWrite(SLAVESELECT,HIGH); //release chip
  delay(10);
  
  return i;
}
