#include <SPI.h>
#include <LiquidCrystal.h>
#include <Stepper.h>
//LiquidCrystal lcd(11,12,2,3,4,5,6,7,8,9);
LiquidCrystal lcd(10); //SPI MODE ##########


// Pin Declearation
byte UP_BUTTON = 9;
byte DOWN_BUTTON = 8;

byte STEPPER_YEL_X = 4;
byte STEPPER_BLU_X = 5;
byte STEPPER_GRE_X = 6;
byte STEPPER_RED_X = 7;

// byte STEPPER_YEL_Y = ;
// byte STEPPER_BLU_Y = ;
// byte STEPPER_GRE_Y = ;
// byte STEPPER_RED_Y = ;

// Stepper Property Definition
byte STEPS = 200; // 1.8 degrees per step
byte STEPPER_RPM = 100; // RPM the stepper runs on (150 is about the maximum)
byte UNIT_DISTANCE_X = 10; // Number of steps per one unit distance, X axis
byte UNIT_DISTANCE_Y = 10; // Number of steps per one unit distance, Y axis

Stepper stepperX = Stepper(STEPS, STEPPER_YEL_X, STEPPER_BLU_X, STEPPER_GRE_X, STEPPER_RED_X);
// Stepper stepperY = stepper(STEPS, STEPPER_YEL_Y, STEPPER_BLU_Y, STEPPER_GRE_Y, STEPPER_RED_Y);

// Global Variable Declearations
int packetsRecieved = 0, i,shapeCounter = 1;
char recieved;
float tempX, tempY;
String intData = "";
char intBuffer[4];
int intLength;

char operationMode;
float stepper_LastX;
float stepper_LastY;

// Data structor declearations
struct Node{
    float xCoord;
    float yCoord;
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

void stepperMoveTo(float posX, float posY){
    // only simple step commands for now, will have to impliment stall detection once hardware allows

    // Move X
    Serial.print("MoveX: ");
    Serial.println((posX - stepper_LastX)*UNIT_DISTANCE_X);
    stepperX.step((posX - stepper_LastX)*UNIT_DISTANCE_X);
    // Update last position
    stepper_LastX = posX;

    // Move Y
    // stepperX.step((posY - stepper_LastY)*UNIT_DISTANCE_Y);
    // Update last position
    // stepper_LastY = posY;


    // Will also have to impliment Z actions 

}


// Setup Decleartaions
struct shapeList * shapeListStart;
struct shapeList * currShape;
struct Node * currCoord;

struct Node * tempCoord;
struct shapeList * tempShape;

// Setup function
void setup() {
    
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

    // stepperY.setSpeed(STEPPER_RPM);
    stepperX.setSpeed(STEPPER_RPM);

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
    while (1==1){ // Recieving data from serial, will run until broken

        if (Serial.available() > 0){
            // Store the recieved char and operate on it later
            recieved = Serial.read();
        
         if (recieved == 'X'){
             currCoord -> xCoord = Serial.parseFloat();
             currCoord -> yCoord = Serial.parseFloat();
             
            // LCD debug output
            clearLine(1);
            lcd.print("+ Parsed ints +");
            
            lcd.setCursor(0,1);
            lcd.print( currCoord -> xCoord);
            lcd.print(" ");
            lcd.print( currCoord -> yCoord);


            currCoord -> next = (struct Node *) malloc (sizeof(struct Node));
            //Serial.print("CCN:");
            //Serial.println((long)currCoord -> next);

            tempCoord = currCoord;
            currCoord = currCoord -> next;
            //Serial.println("D");
            
            //lcd.clear();
            //lcd.setCursor(0,1);
            //lcd.print("test");
        }else{
        
        if (recieved == 'M'){
            // Recieved the global end character, will wrap up
            currShape->next = NULL;
            currCoord->next = NULL;
            
            break;
        }

        /*
        if (recieved == '\n'){
            // Recieved linefeed character, indicating the start of another shape
            //Serial.println("S");
            free(currCoord);
            tempCoord->next = NULL; //clean up the tail
            
            currShape->next = (struct shapeList *) malloc (sizeof(struct shapeList));
            //Serial.print("CSN:");
            //Serial.println((long)currShape -> next);
            tempShape = currShape;
            currShape = currShape->next;
            currShape->coords = (struct Node *) malloc (sizeof(struct Node));
            currCoord = currShape->coords;
            
            //Serial.print("CLS:");
            //Serial.println((long)shapeListStart);

            //Serial.print("CS:");
            //Serial.println((long)currShape);

            //Serial.print("CC:");
            //Serial.println((long)currCoord);

            //Serial.println("-------- Shape Done ----------");
        }
        */
        
         }
        }
    } // End RX loop

    Serial.println("Input 's' to execute the path with steppers, 'p' to print storage through serial,");
    Serial.println(" 'r' go back and listen to serial, 'c' to clear memory and listen to serial.");
    clearLine(1);
    lcd.print("Input, See serial");

   /* while(1==1){ // Wait for user input on operatoin to perfrom with data recieved
        if(Serial.available() > 0){
            recieved = Serial.read();
            if(recieved == 's' || recieved == 'S'){
                operationMode = 1;
                Serial.println("Selected, will operate stepper.");
                clearLine(1);
                lcd.print("Stepper Mode");
                break;
            } else if (recieved == 'p' || recieved == 'P'){
                operationMode = 2;
                Serial.println("Selected, print memory content.");
                clearLine(1);
                lcd.print("Print SRAM");
                break;
            } else if (recieved == 'r' || recieved == 'R'){
                operationMode = 3;
                Serial.println("Selected, will listen to serial more.");
                clearLine(1);
                lcd.print("Revert, Serial");
                break;
            } else if (recieved == 'c' || recieved == 'C'){
                operationMode = 4;
                Serial.println("Selected, will clear memory and listen to serial.");
                clearLine(1);
                lcd.print("Clear SRAM, Revert");
                break;
            } else {
                Serial.println("Input recieved, but not understood, try again.");
                clearLine(1);
                lcd.print("Retry input");
            }
        }
    }*/

    operationMode = 1;

    if (operationMode == 1){ // Operation 1, Run steppers
        //Serial.println("-------- Actuate Stepper --------");
        
        // Recieve loop terminated, will recall stored data and print over serial
        currShape = shapeListStart;
        currCoord = shapeListStart->coords;
        //Serial.print("CS:");
        //Serial.println((long)currShape);
        //Serial.print("CC:");
        //Serial.println((long)currCoord);
        
        while (currShape != NULL){
            // Print a header of the surrent shape
            //Serial.print("\n-------- Shape #: ");
            //Serial.print(shapeCounter,DEC);
            //Serial.print(" ---------- \n");
            //Serial.print("CS:");
            //Serial.println((long)currShape);
            
            while (currCoord != NULL){
                delay(50);
                Serial.print("CC:");
                Serial.print((long)currCoord);
             
                stepperMoveTo(currCoord->xCoord,currCoord->yCoord);
                
                tempCoord = currCoord;
                currCoord = currCoord -> next;
                free(tempCoord);
                
            }
            
            //
            // MUST IMPLIMENT, SPAKE SWITCH AND LIFT Z
            //

            tempShape = currShape;
            currShape = currShape -> next;
            shapeCounter++;
            currCoord = currShape -> coords;
            //Serial.print("CC - LOOP:");
            //Serial.println((long)currCoord);
        }
        
        //Serial.println("Done");
    }
  
    if (operationMode == 2){ // Operation 2, Print memory

        Serial.println("-------- Print Memory Content --------");
        
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
    }

    // Operation complete, hold up the process
    while(1==1){
        delay(10000);
    }
}
