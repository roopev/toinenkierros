//Include the Wire I2C Library
#include <Wire.h>
#include <EEPROM.h>

#define rtl 0x57 // eepromin sijainti

void setup(void)
{                             // alustetaan muuttujat
  unsigned int address = 0;  // muistin sijainti
  int arvo = 1;             // pariton luku
  
  Serial.begin(9600);  // väylän nopeus
  Wire.begin();       // herätetään 12c väylä

  for (int i = 0 ; i < 100 ; i++) // looppi ajetaan 100 kertaa
  {
  writeEEPROM(address, arvo);             // kutsutaan kirjoitusfunktiota
  delay(10);                             // viive että piiri pysyy menossa mukana

 
  arvo = arvo + 2;               // nostetaan parittoman luvun arvoa kahdella
  address++;                    // nostetaan muistin osoitteen arvoa yhdellä


  }

  address = 0;
  
  for (int i = 0 ; i < 100 ; i++){
  Serial.print(readEEPROM(address));    // kutsutaan lukufunktiota ja printataan arvo
  Serial.print("\n"); 
  address++; 
  }
 
  
}

void loop(){}

void writeEEPROM(unsigned int address, int data ) // kirjoitusfunktio, jolle annetaan muistiosoite ja pariton numero
{
  EEPROM.put(address, data);                     // kirjoitetaan luku muistiin
 
  delay(5);                            
  
 
}

byte readEEPROM(int address) // lukufunktio, jolle annetaan muistiosoite
{
  int arvo = 0;               // alustetaan funktio
  int rdata = EEPROM.get(address, arvo);  // luetaan muistista 
  return rdata;
}
