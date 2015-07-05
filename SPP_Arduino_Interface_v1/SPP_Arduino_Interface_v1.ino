#include <LiquidCrystal.h>
LiquidCrystal lcd(11,12,2,3,4,5,6,7,8,9);
int packetsRecieved = 0, i,shapeCounter = 1;
char recieved;
unsigned char tempX, tempY;


struct Node{
  unsigned char xCoord;
  unsigned char yCoord;
  struct Node * next = NULL;
};

struct shapeList{
   Node * coords = NULL;
   struct shapeList * next = NULL;
};


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
struct shapeList * shapes = (shapeList *) malloc (sizeof(shapeList));
struct shapeList * currShape = shapes;
struct Node * currCoord = NULL;

struct Node * tempCoord;
struct shapeList * tempShape;


void setup() {
  
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Setup Reset");
  delay(1000);
  clearLine(0);
  lcd.setCursor(0, 0);
  lcd.print("Ready");
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

  // Some initialization 
  //currShape->next = (shapeList *) malloc (sizeof(shapeList));
  //currShape = currShape->next;
  //currShape->coords = (Node *) malloc (sizeof(Node));
  //currCoord = currShape->coords;

while (1==1){
  // Recieving data from serial, will run until broken
  
  if (Serial.available() > 0){
    // Store the recieved char and operate on it later
    recieved = Serial.read();
    
    /*
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
  */
  
   if (recieved == '('){
    
    // Recieved a starting round bracket, indicating start of a corrdinate
    tempX = (unsigned char) Serial.parseInt();
    tempY = (unsigned char) Serial.parseInt();
    
    lcd.setCursor(0,0);
    lcd.print("+ Parsed ints +");
    
    lcd.setCursor(0,1);
    lcd.print(tempX);
    lcd.print(" ");
    lcd.println(tempY);
    
   // Serial.print("SaveOP1 ");
    
    currCoord -> xCoord = tempX;
    
    currCoord -> yCoord = tempY;
    
    currCoord -> next = (struct Node*) malloc (sizeof(struct Node));

   
    Serial.print(currCoord -> xCoord);
    Serial.print(" ");
    Serial.println(currCoord -> yCoord);
        
    currCoord = currCoord -> next;
    Serial.println("D");
    
    //lcd.clear();
    //lcd.setCursor(0,1);
    //lcd.print("test");
  }else{
  
  if (recieved == '!'){
    // Recieved the global end character, will wrap up
    currShape->next = NULL;
    currCoord->next = NULL;
    
    break;
  }
  
  if (recieved == '\n'){
    // Recieved linefeed character, indicating the start of another shape
    Serial.println("S");
    currCoord->next = NULL; //sort of clean up the tail
    
    currShape->next = (struct shapeList *) malloc (sizeof(struct shapeList));
    currShape = currShape->next;
    currShape->coords = (struct Node *) malloc (sizeof(struct Node));
    currCoord = currShape->coords;
    
    Serial.println("SD");
  }
  
  
   }
  }
}
  
  Serial.println("Hellos");
  
  
  
  // Recieve loop terminated, will recall stored data and print over serial
  currShape = shapes;
  currCoord = currShape->coords;
  
  while (currShape != NULL){
    // Print a header of the surrent shape
    Serial.print("\n-------- Shape #: ");
    Serial.print(shapeCounter,DEC);
    Serial.print(" ---------- \n");
    
    while (currCoord->next != NULL){
      Serial.print("(");
      Serial.print(currCoord->xCoord);
      Serial.print(",");
      Serial.print(currCoord->yCoord);
      Serial.print(")");
      
      Serial.println("Move to next 1");
      tempCoord = currCoord;
      currCoord = currCoord -> next;
      free(tempCoord);
      
      Serial.println("Move to next 2");
    }
    
    Serial.println("Move Shape 1");
    tempShape = currShape;
    currShape = currShape -> next;
    free(currShape);
    shapeCounter++;
    Serial.println("Move Shape 2");
  }
  
  Serial.println("Done");
  while(1==1){
    delay(10000);
  }
  

}
