//Include the Wire I2C Library
#include <Wire.h>

#define rtl 0x57 // eepromin sijainti

void setup(void)
{
  Serial.begin(9600);  // väylän nopeus
  Wire.begin();        // herätetään i2c väylä
  
                                
  for (long x = 0x26AC ; ; x++) // aloitetaan lukeminen osoitteesta 0x26AC ja jatketaan kunnes saadaan arvo 0xFF (kohta muistipiirillä jolle ei ole kirjoitettu dataa) 
  {
    byte val = readEEPROM(x);   // kutsutaan lukufunktiota
    
    if (val == 0xFF) {          // katsotaan palautunut arvo, jos 0xFF lopetetaan ohjelma
      break;
    }
    Serial.write(val);          // kirjoitetaan palautunut bitti
  }
}

void loop(){}

byte readEEPROM(long eeaddress) // lukufunktio
{
  Wire.beginTransmission(rtl); // aloita kommunikointi eepromin kanssa

  Wire.write((int)(eeaddress >> 8));  // MSB arvokkain bitti
  Wire.write((int)(eeaddress & 0xFF));  // LSB arvottomin bitti
  Wire.endTransmission();       

  Wire.requestFrom(rtl, 1);   // master (arduino kutsuu bittejä orjalaitteelta (eepromilta)

  byte rdata = 0xFF;          // alustetaan muuttuja
  
  if (Wire.available()) rdata = Wire.read();  // palauttaa bitit jotka on mahdollista lukea muistin kohdalta
  return rdata;
}
