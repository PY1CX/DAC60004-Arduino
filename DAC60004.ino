#include <SPI.h>

//DAC60004 parameters
#define DAC60004_CH_A 0x0000
#define DAC60004_CH_B 0x1000
#define DAC60004_CH_C 0x7000
#define DAC60004_CH_D 0xF000

//CS Pin of DAC60004
const int DAC60004_CS_PIN = 53;

boolean updateDAC(int channel, int value);
boolean resetDAC (void);

void setup()
{
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  Serial.begin(115200);
  pinMode(DAC60004_CS_PIN, OUTPUT);
  SPI.setClockDivider(SPI_CLOCK_DIV2);



}
void loop()
{
  updateDAC(0, 4095);
}

/**
 * 
 * updateDAC - Updates the DAC60004 value to a assigned
 * channel and a assigned value. 
 * 
 * Parameters:
 * int channel - The channel that needs to be updated
 * int value   - The desired output value of the DAC
 * output.
 *
 * Returns true
 * 
 * Felipe Navarro
 * 
 */
boolean updateDAC(int channel, int value)
{
  byte MSB, LSB;
  switch(channel){
    case 0:
    value += DAC60004_CH_A;
    break;
    case 1:
    value += DAC60004_CH_B;
    break;
  }
  LSB = (int(value)) & 0xFF;
  MSB = ((int(value)) & 0xff00) >> 8;
  digitalWrite(DAC60004_CS_PIN, LOW);
  SPI.transfer(0x03); 
  SPI.transfer(MSB);
  SPI.transfer(LSB);
  SPI.transfer(0x00);
  digitalWrite(DAC60004_CS_PIN, HIGH); //delay(1000);
  return true; 
}
/**
 * 
 * resetDAC - Little function to reset the DAC60004
 * using the "Software Reset" command in page 22 of
 * the datasheet.
 *
 * Return true
 * 
 * Felipe Navarro
 * Not tested yet
 */
boolean resetDAC()
{
  digitalWrite(DAC60004_CS_PIN, LOW);
  SPI.transfer(0xE7);
  //Bit D23 to D00 doesn't matter so we are going to send 0's
  for (int x = 0; x < 3; x++)
  {
  SPI.transfer(0x00);
  }
  digitalWrite(DAC60004_CS_PIN, HIGH);
  return true;
}
