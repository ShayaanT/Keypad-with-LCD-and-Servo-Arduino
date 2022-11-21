

//Shayaan Tanvir
//11 - 15 - 2020
//keypad connected to an lcd display that turns a servo
#include <Servo.h>

#include <LiquidCrystal_I2C.h>


#include <Wire.h>

#include <Keypad.h>


#define Password_Length 8 

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int signalPin = 10;
int pos = 0;    // variable to store the servo position
const int buzzer = 11;

char Data[Password_Length]; 
char Master[Password_Length] = "6476857"; 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 16, 2);  

void setup(){
  lcd.init(); 
  lcd.backlight();
  pinMode(signalPin, OUTPUT);
  pinMode(buzzer, OUTPUT);

  myservo.attach(10);  // attaches the servo on pin 10 to the servo object
  myservo.write(0);
}

void loop(){

  lcd.setCursor(0,0);
  lcd.print("Enter Password:");

  customKey = customKeypad.getKey();
  if (customKey){
    Data[data_count] = customKey; 
    lcd.setCursor(data_count,1); 
    lcd.print(Data[data_count]); 
    data_count++; 
    }

  if(data_count == Password_Length-1){
    lcd.clear();

    if(!strcmp(Data, Master)){
      lcd.print("Correct");
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
         myservo.write(pos);              // tell servo to go to position in variable 'pos'
         delay(15);                       // waits 15ms for the servo to reach the position
  }
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
  }
      digitalWrite(signalPin, HIGH); 
      delay(5000);
      digitalWrite(signalPin, LOW);
      }
    else{
      lcd.print("Incorrect");
      tone(buzzer, 1000);
      delay(500);
      noTone(buzzer);
      }
    
    lcd.clear();
    clearData();  
  }
}

void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
  return;
}
