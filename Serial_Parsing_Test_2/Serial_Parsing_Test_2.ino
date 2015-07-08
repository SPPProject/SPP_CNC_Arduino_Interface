#include <LiquidCrystal.h>
LiquidCrystal lcd(11,12,2,3,4,5,6,7,8,9);

int clearLine(int a){
  lcd.setCursor(0, a);
  lcd.print("                 ");
  lcd.setCursor(0, a);
}

void setup()
{
  Serial.begin(1200);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Soft Reset ...");
  delay(1000);
  
  clearLine(0);
  lcd.print("Buffer Count:");
  clearLine(1);
  lcd.print(0);
}

int testTemp;
int testCounter = 0;

void loop()
{
  if (Serial.available() > 0){
    //testTemp = Serial.parseInt();
    testTemp = Serial.read();
    Serial.print((char)testTemp);
    //Serial.print(" ");
    
    //clearLine(1);
    //lcd.print(Serial.available());
  }
  
}
