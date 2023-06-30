// The code was taken here: https://www.kn34pc.com/spr/arduino_24c02.html

#include "at24c02.h"

at24c02 eeprom(0x50);                             // 0x50 = A0(GND), A1(GND), A2(GND)

char ch;

void setup() {
  Serial.begin(57600);
  eeprom.init();
}

void loop() {
  Serial.println("Fix EEPROM 24C02 of Saleae Logic Analyzer 24MHz8Ch (Clone):");
  Serial.println("r - Read EEPROM");
  Serial.println("w - Write data. Fix the EEPROM");
  Serial.println();

  while (1) {
    if (Serial.available() > 0) {
      ch = Serial.read();

      if (ch == 'r')                              // read
        eeprom_read();

      if (ch == 'w') {                           
        eeprom_blank();                           // blank and read
        eeprom_write_data();               // write data and read
        eeprom_read();
      }
    }
  }
}

void eeprom_read() {
  Serial.print("         ");
  for (uint8_t i = 0; i < 16; i++) {
    Serial.print('0');
    Serial.print(i, HEX);
    Serial.print(' ');
  }
  Serial.println();

  for (uint8_t j = 0; j < 16; j++) {
    Serial.print("000000");
    Serial.print(j, HEX);
    Serial.print("0 ");
    for (uint8_t k = 0; k < 16; k++) {
      uint8_t read_byte = eeprom.read(j * 16 + k);
      if (read_byte < 16)
        Serial.print('0');
      Serial.print(read_byte, HEX);
      Serial.print(' ');
    }
    Serial.println();
  }
  Serial.println();
}

void eeprom_blank() {
   for (uint16_t i = 0; i < 256; i++)
    eeprom.write(i, 0xFF);
}

byte fileData[17] = {0xC0, 0x25, 0x09, 0x81, 0x38, 0x01, 0x00, 0x00, 0x7D, 0x2C, 0x5D, 0x84, 0x8E, 0x2C, 0xE2, 0xA3, 0x7F};
void eeprom_write_data() {
  for (uint16_t i = 0; i < 17; i++)
    eeprom.update(i, fileData[i]);
}
