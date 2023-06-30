// EEPROM 24C02 library for Arduino, 256 x 8 (2K), v0.2
// 30.06.2017, Arduino IDE v1.8.3, LZ2WSG
//---------------------------------------------------------------------------------------------------------
#include <Arduino.h>
#include <Wire.h>
#include "at24c02.h"
//       _____
//  A0 -|  ^  |- VCC
//  A1 -|     |- WP(GND)
//  A2 -|     |- SCL
// GND -|_____|- SDA

// I2C address is 0x50 = A0(GND), A1(GND), A2(GND)
//---------------------------------------------------------------------------------------------------------
at24c02::at24c02(uint8_t _i2c_addr) {
  m_chip_addr = _i2c_addr;                                  // I2C адрес на EEPROM
}
//---------------------------------------------------------------------------------------------------------
void at24c02::init() {                                      // инициализация
  Wire.begin();
}
//---------------------------------------------------------------------------------------------------------
void at24c02::write(uint8_t m_addr, uint8_t m_data) {       // записва клетка на адрес m_addr с данни m_data
  Wire.beginTransmission(m_chip_addr);
  Wire.write(m_addr);
  Wire.write(m_data);
  Wire.endTransmission();
  delay(5);
}
//---------------------------------------------------------------------------------------------------------
void at24c02::update(uint8_t m_addr, uint8_t m_data) {      // чете клетка и записва данни само при разлика
  uint8_t m_exist_data;                                     // eeprom endurance

  m_exist_data = read(m_addr);
  if (m_data != m_exist_data) {                             // записва ако данните са различни от записаните
    Wire.beginTransmission(m_chip_addr);
    Wire.write(m_addr);
    Wire.write(m_data);
    Wire.endTransmission();
    delay(5);
  }
}
//---------------------------------------------------------------------------------------------------------
uint8_t at24c02::read(uint8_t m_addr) {                     // чете съдържанието на клетка с адрес m_addr
  uint8_t m_data = 0xFF;

  Wire.beginTransmission(m_chip_addr);
  Wire.write(m_addr);
  Wire.endTransmission();
  Wire.requestFrom((uint8_t)m_chip_addr, (uint8_t)1);
  if (Wire.available())
    m_data = Wire.read();
  return m_data;
}
