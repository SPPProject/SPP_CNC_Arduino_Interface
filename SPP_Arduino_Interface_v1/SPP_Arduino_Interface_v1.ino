#include <LiquidCrystal.h>
LiquidCrystal lcd(11,12,2,3,4,5,6,7,8,9);
int packetsRecieved = 0, i,shapeCounter = 1;
char recieved;
int tempX, tempY;



typedef struct Node{
  unsigned char xCoord;
  unsigned char yCoord;
  Node * next;
  
}Node;


typedef struct shapeList{
   Node * coords;
   shapeList * next;
   
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

// shapes remain static as the start of the list, currShape will follow the progress
shapeList * shapes = (shapeList *) malloc (sizeof(shapeList));
shapeList * currShape = shapes;
Node * currCoord = NULL;


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

while (1==1){
  // Recieving data from serial, will run until broken
  
  if (Serial.available() > 0){
    // Store the recieved char and operate on it later
    recieved = Serial.read();
    
    // Debug LCD Print
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
  
  
  
  if (recieved == '!'){
    // Recieved the global end character, will wrap up
    currShape->next = NULL;
    currCoord->next = NULL;
    
    break;
  }
  
  if (recieved == '\n'){
    // Recieved linefeed character, indicating the start of another shape
    currCoord->next = NULL; //sort of clean up the tail
    
    currShape->next = (shapeList *) malloc (sizeof(shapeList));
    currShape = currShape->next;
    currShape->coords = (Node *) malloc (sizeof(Node));
    currCoord = currShape->coords;
  }
  
  if (recieved == '('){
    // Recieved a starting round bracket, indicating start of a corrdinate
    tempX = (unsigned char) Serial.parseInt();
    tempY = (unsigned char) Serial.parseInt();
    
    currCoord -> xCoord = tempX;
    currCoord -> yCoord = tempY;
    currCoord -> next = (Node*) malloc (sizeof(Node));
    currCoord = currCoord -> next;
  }
  
  
   }
  }
  
  // Recieve loop terminated, will recall stored data and print over serial
  currShape = shapes;
  currCoord = currShape->coords;
  
  while (currShape != NULL){
    // Print a header of the surrent shape
    Serial.print('-------- Shape #: %d ---------- \n',shapeCounter);
    
    while (currCoord->next != NULL){
      Serial.print('(%u',currCoord->xCoord);
      Serial.print(',%u) ',currCoord->yCoord);
      currCoord = currCoord -> next;
    }
    
    currShape = currShape -> next;
    shapeCounter++;
  } 
  

}
