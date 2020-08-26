//Include the Wire I2C Library
#include <Wire.h>    
 
#define rtl 0x57    // eepromin sijainti
 
void setup(void)
{
  Serial.begin(9600);  // väylän nopeus
  Wire.begin();       // herätetään i2c väylä
 
  unsigned int address = 0; // alustetaan muuttuja 


  writeEEPROM(rtl, address, 23); // funktio muistiin kirjoittamiseen, funktiolle annetaan arvot laite, osoite ja data

  Serial.print(readEEPROM(rtl, address));


}
 
void loop(){}
 
void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) // kirjoitusfunktio, jolle annetaan laitteen osoite, muistin osoite ja kirjoitettava data
{
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB arvokkain bitti
  Wire.write((int)(eeaddress & 0xFF)); // LSB arvottomin bitti
  Wire.write(data);                    // kirjoitetaan data 
  Wire.endTransmission();              // katkaistaan siirto
 
  delay(5);
}
 
byte readEEPROM(int deviceaddress, unsigned int eeaddress ) // lukufunktio, jolle annetaan laitteen osoite ja muistin osoite
{
  byte rdata = 0xFF;  // alustetaan muuttuja
 
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB arvokkain bitti
  Wire.write((int)(eeaddress & 0xFF)); // LSB arvottomin bitti
  Wire.endTransmission();              // katkaistaan siirto
 
  Wire.requestFrom(deviceaddress,1);   // master (arduino) kutsuu bittejä orjalaitteelta (eepromilta)
  
  
  if (Wire.available()) rdata = Wire.read(); // palauttaa bitit jotka on mahdollista lukea muistin kohdalta
 
  return rdata;
}
