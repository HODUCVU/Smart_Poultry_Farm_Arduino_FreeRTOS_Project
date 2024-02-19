#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SDA 18  // A4
#define SCL 19  // A5

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void TaskDisplay(void * pvParamenters);