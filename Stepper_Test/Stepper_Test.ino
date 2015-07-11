// Preprocesser Operations
#include <SPI.h>
#include <LiquidCrystal.h>
#include <Stepper.h>

LiquidCrystal lcd(10); //SPI MODE ##########
//LiquidCrystal lcd(11,12,2,3,4,5,6,7,8,9);

// Pin Declearation
byte UP_BUTTON = 9;
byte DOWN_BUTTON = 8;

byte STEPPER_YEL = 4;
byte STEPPER_BLU = 5;
byte STEPPER_GRE = 6;
byte STEPPER_RED = 7;

// Stepper Property Definition
byte STEPS = 200;

// Global Variable Decleartions
bool testMode;
int testRpm = 0;

Stepper stepper(STEPS, STEPPER_YEL, STEPPER_BLU, STEPPER_GRE, STEPPER_RED);

// Function Declearations
int clearLine(int a){
	lcd.setCursor(0, a);
	lcd.print("                 ");
	lcd.setCursor(0, a);
}


void setup()
{
	//pinMode(2, INPUT_PULLUP);
	//pinMode(3, INPUT_PULLUP);
	//pinMode(4, INPUT_PULLUP);
	//pinMode(5, INPUT_PULLUP);
	pinMode(UP_BUTTON, INPUT_PULLUP);
	pinMode(DOWN_BUTTON, INPUT_PULLUP);

	Serial.begin(4800);
	// set up the LCD's number of columns and rows: 
	lcd.begin(16, 2);
	// Print a message to the LCD.
	lcd.print("Soft Reset ...");
	delay(500);
 
	clearLine(0);
	lcd.print("Steeper Test ...");
	Serial.println("Steeper Test Initiated");
	Serial.println("Enter RPM through serial");
	delay(200);

	clearLine(0);
	lcd.print("Current RPM:");
	clearLine(1);
	lcd.print("0 - Waiting");
 }

 void loop(){
 	if (Serial.available() > 0){
 		testRpm = Serial.parseInt();
 		stepper.setSpeed(testRpm);
		clearLine(1);
		lcd.print(testRpm);
 	}

	if (digitalRead(UP_BUTTON) == LOW){
		// UP button was pressed, jog forward
		stepper.step(STEPS);
		Serial.println("UP");

	} else if (digitalRead(DOWN_BUTTON) == LOW){
		stepper.step(0 - STEPS);
		Serial.println("DOWN");

	}
}
