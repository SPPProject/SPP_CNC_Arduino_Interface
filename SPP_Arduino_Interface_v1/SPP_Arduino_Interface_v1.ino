#include <SPI.h>
#include <LiquidCrystal.h>
//LiquidCrystal lcd(11,12,2,3,4,5,6,7,8,9);
LiquidCrystal lcd(10); //SPI MODE ##########


// Pin Declearation
byte UP_BUTTON = 9;
byte DOWN_BUTTON = 8;

byte STEPPER_YEL = 4;
byte STEPPER_BLU = 5;
byte STEPPER_GRE = 6;
byte STEPPER_RED = 7;

// Stepper Property Definition
byte STEPS = 200; // 1.8 degrees per step

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

// Setup Decleartaions
struct shapeList * shapeListStart;
struct shapeList * currShape;
struct Node * currCoord;

struct Node * tempCoord;
struct shapeList * tempShape;

// Setup function
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

    // Test stuff, sizes of things
    Serial.println("Sizes of things:");
    Serial.print("Size of int:");
    Serial.println(sizeof(int));
    Serial.print("Size of Node:");
    Serial.println(sizeof(struct Node));
    Serial.print("Size of shapeList:");
    Serial.println(sizeof(struct shapeList));
    Serial.print("Size of Node pointer:");
    Serial.println(sizeof(struct Node *));
    Serial.print("Size of shapeList pointer:");
    Serial.println(sizeof(struct shapeList *));

    // Initialize structs and pointers
    shapeListStart = (struct shapeList *) malloc (sizeof(struct shapeList));
    currShape = shapeListStart;
    shapeListStart -> coords = (struct Node *) malloc (sizeof(struct Node));
    currCoord = shapeListStart -> coords;

    Serial.print("CLS:");
    Serial.println((long)shapeListStart);

    Serial.print("CS:");
    Serial.println((long)currShape);

    Serial.print("CC:");
    Serial.println((long)currCoord);
    
    Serial.println("-------- Init Done ----------");


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
        Serial.print("CCN:");
        Serial.println((long)currCoord -> next);

        tempCoord = currCoord;
        currCoord = currCoord -> next;
        //Serial.println("D");
        
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
        free(currCoord);
        tempCoord->next = NULL; //clean up the tail
        
        currShape->next = (struct shapeList *) malloc (sizeof(struct shapeList));
        Serial.print("CSN:");
        Serial.println((long)currShape -> next);
        tempShape = currShape;
        currShape = currShape->next;
        currShape->coords = (struct Node *) malloc (sizeof(struct Node));
        currCoord = currShape->coords;
        
        Serial.print("CLS:");
        Serial.println((long)shapeListStart);

        Serial.print("CS:");
        Serial.println((long)currShape);

        Serial.print("CC:");
        Serial.println((long)currCoord);

        Serial.println("-------- Shape Done ----------");
    }
    
    
     }
    }
}
    

    Serial.println("-------- Start output --------");
    
    
    
    // Recieve loop terminated, will recall stored data and print over serial
    currShape = shapeListStart;
    currCoord = shapeListStart->coords;
    Serial.print("CS:");
    Serial.println((long)currShape);
    Serial.print("CC:");
    Serial.println((long)currCoord);
    
    while (currShape != NULL){
        // Print a header of the surrent shape
        Serial.print("\n-------- Shape #: ");
        Serial.print(shapeCounter,DEC);
        Serial.print(" ---------- \n");
        Serial.print("CS:");
        Serial.println((long)currShape);
        
        while (currCoord != NULL){
            Serial.print("CC:");
            Serial.print((long)currCoord);
            Serial.print("(");
            Serial.print(currCoord->xCoord);
            Serial.print(",");
            Serial.print(currCoord->yCoord);
            Serial.println(")");
            
            tempCoord = currCoord;
            currCoord = currCoord -> next;
            free(tempCoord);
            
        }
        
        tempShape = currShape;
        currShape = currShape -> next;
        shapeCounter++;
        currCoord = currShape -> coords;
        Serial.print("CC - LOOP:");
        Serial.println((long)currCoord);
    }
    
    Serial.println("Done");
    while(1==1){
        delay(10000);
    }
    

}
