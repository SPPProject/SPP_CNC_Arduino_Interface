#include <LiquidCrystal.h>
LiquidCrystal lcd(11,12,2,3,4,5,6,7,8,9);
int packetsRecieved = 0, i;
char recieved;

typedef struct{
  int xCoord;
  int yCoord;
  Node * next;
  
}Node;


typedef struct{
   Node coords;
   shapeList * next:
   
}shapeList;


int clearLine(int a){
  lcd.setCursor(0, a);
  
  for (i=1;i<17;i++){
    lcd.print(" ");
  }
}

int printPackNumber(int PR){
  lcd.setCursor(9, 0);
  lcd.print(PR);
}


void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  delay(1000);
  clearLine(0);
  lcd.setCursor(0, 0);
  lcd.print("Packet#:");
  printPackNumber(packetsRecieved);
  packetsRecieved++;
  clearLine(1);
  lcd.setCursor(0, 1);
  
  shapeList * shapes = (shapeList *) malloc (sizeof(shapeList));
  
  
  
}

void loop() {
  
/*if (Serial.available() > 0) { 
  recieved = Serial.read();
  
  if(recieved == '!' || recieved == '\n'){
    printPackNumber(packetsRecieved);
    packetsRecieved++;
    clearLine(1);
    lcd.setCursor(0, 1);
    //Serial.print("Cleared line, ready for packet# %d \n",packetsRecieved);
  }else{
  lcd.print(recieved);
    //Serial.print("Recieved data %c, part of packet %d",packetsRecieved);
  }
}*/

if (Serial.available() > 0){


}
