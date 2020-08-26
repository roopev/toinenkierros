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

  for (int i = 0 ; i < 200 ; i++) // looppi ajetaan 200 kertaa
  {
  byte high = highByte(arvo);             // pilkotaan muuttuja kahteen osaan, tarkoituksena kirjoittaa muistiin yli 255 lukuisia arvoja
  byte low = lowByte(arvo);
  
  writeEEPROM(address, high);             // kutsutaan kirjoitusfunktiota kahteen kertaan high & low
  delay(5);                             
  address++;
  writeEEPROM(address, low);
  arvo = arvo + 2;               // nostetaan parittoman luvun arvoa kahdella
  address++;;                    // nostetaan muistin osoitteen arvoa yhdellä


  }

  address = 0;                  // nollataan muistiosoitteen muuttuja
  
  for (int i = 0 ; i < 200 ; i++){
    
    int combine = readEEPROM(address);  // luetaan ensimmäinene osa muuttujasta
    
    address++;                          // nostetaan muistin osoitteen arvoa yhdellä
   
    combine = combine*256;              // binäärikikkailua, koitan selittää esityksessä
    
    combine |= readEEPROM(address);     // yhdistetään toinen osa muuttujasta ja yhdistetään se ensimmäiseen osaan
    
    Serial.print(combine);              // tulostetaan muuttuja
    Serial.print("\n"); 
    
    address++; 
  }
 
  
}

void loop(){}

void writeEEPROM(unsigned int address, int data ) //kirjoitusfunktio, jolle annetaan muistiosoite ja pariton numero
{
  EEPROM.put(address, data);
 
  delay(5);                            // 3 ms kirjoitusaika
  
 
}

byte readEEPROM(int address) // lukufunktio, jolle annetaan muistiosoite
{
  int arvo = 0;
  int rdata = EEPROM.get(address, arvo);
  return rdata;
}
