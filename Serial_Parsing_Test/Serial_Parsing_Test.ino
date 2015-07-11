#include <SPI.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(10); //SPI MODE ##########
//LiquidCrystal lcd(11,12,2,3,4,5,6,7,8,9);

// Global Variable Decleartions
int charCount = 0;
int testNumber, testNumberConfirm;
int testTemp;
int successCount;
int trialCount = 0;

// Function Declearations
int clearLine(int a){
  lcd.setCursor(0, a);
  lcd.print("                 ");
  lcd.setCursor(0, a);
}




void setup()
{
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  
  digitalWrite(3, HIGH);
  Serial.begin(4800);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Soft Reset ...");
  delay(1000);
 
  clearLine(0);
  lcd.print("Input test #: ");
  Serial.println("Input test number into serial terminal");
  
  while (1 == 1){
    while (1 == 1){
      if (Serial.available() > 0){
        testNumber = Serial.parseInt();
        break;
      }
    }
  
    clearLine(0);
    lcd.print("Confirm Test #:");
    clearLine(1);
    lcd.print(testNumber);
    delay(200);
    Serial.flush();
    
    Serial.print("Reenter test number to confirm:");
    Serial.println(testNumber);
    
    while (1 == 1){
      if (Serial.available() > 0){
        testNumberConfirm = Serial.parseInt();
        delay(100);
        Serial.flush();
        break;
      }
    }
    
    if (testNumber == testNumberConfirm){
      clearLine(0);
      lcd.print("Confirmed");
      delay(500);
      Serial.println("Number confirmed, proceed");
      break;
      
    } else {
      clearLine(0);
      lcd.print("Fail");
      clearLine(1);
      lcd.print("Reenter test #");
    }
  
  }
  
  clearLine(0);
  lcd.print("Ready for serial");
}
void loop()
{
  successCount = 0;
  testTemp = 0;
    while (Serial.available() > 0){
    // put your main code here, to run repeatedly:
    testTemp = Serial.parseInt();
    if (testTemp == testNumber){
        successCount++;
        Serial.print(testTemp);
    } else if (successCount > 2){
      
      clearLine(0);
      lcd.print("Terminated");
      clearLine(1);
      lcd.print("Passed: ");
      lcd.print(successCount);
      
  
      Serial.print("\nTest ");
      Serial.print("terminated after ");
      Serial.print(successCount);
      Serial.println(" packets recieved.");
      
      delay(2000);
      break;
    }
    Serial.print(".");
    
    clearLine(1);
    lcd.setCursor(0,1);
    lcd.print(charCount);
    charCount++;
    }
}
