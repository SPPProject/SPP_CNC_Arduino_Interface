#include <SPI.h>
#include <LiquidCrystal.h>
//LiquidCrystal lcd(11,12,2,3,4,5,6,7,8,9);
LiquidCrystal lcd(10); //SPI MODE ##########

// Global Variable Declearations
int packetsRecieved = 0, i,shapeCounter = 1;
char recieved;
int tempX, tempY;
String intData = "";
char intBuffer[4];
int intLength;

// Data structor declearations
struct Node{
    int xCoord;
    int yCoord;
    struct Node * next;
};

struct shapeList{
     Node * coords;
     struct shapeList * next;
};

struct shapeList * shapes = (shapeList *) malloc (sizeof(shapeList));
struct shapeList * currShape = shapes;
struct Node * currCoord = NULL;

struct Node * tempCoord;
struct shapeList * tempShape;

// Assist function declearations
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


// Setup function
void setup() {
    
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);
    pinMode(7, INPUT_PULLUP);
    
    Serial.begin(4800);
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

// Main event loop (ish)

void loop() {
while (1==1){
    // Recieving data from serial, will run until broken

    if (Serial.available() > 0){
        // Store the recieved char and operate on it later
        recieved = Serial.read();
    
     if (recieved == '('){
         currCoord -> xCoord = Serial.parseInt();
         currCoord -> yCoord = Serial.parseInt();
         
        // LCD debug output
        clearLine(1);
        lcd.print("+ Parsed ints +");
        
        lcd.setCursor(0,1);
        lcd.print( currCoord -> xCoord);
        lcd.print(" ");
        lcd.print( currCoord -> yCoord);


        currCoord -> next = (struct Node *) malloc (sizeof(struct Node));

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
        
        Serial.println("GH");
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
        
        while (currCoord != NULL){
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
