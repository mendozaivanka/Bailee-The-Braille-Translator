/* 
 Braille Translator
	
 Uses pushbuttons and LED lights 
 to imitate a Braille Grid. Useful 
 for visually impaired people in
 learning uncontracted Braille.
    
 This code is a modification of 
 Marlou de Guzman's Arduino-Braille-Translator:
 
 https://github.com/marloudeguzman/Arduino-Braille-Translator

*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

// pushbuttons
int buttonValue; //Stores analog main button value when button is pressed
int extraButton; //Stores analog extra button value when button is pressed

// LED lights
const int tlLED =  2;      // top left LED pin
const int mlLED =  1;      // mid left LED pin
const int blLED =  0;      // bottom left LED pin
const int trLED =  5;      // top right LED pin
const int mrLED =  4;      // mid right LED pin
const int brLED =  3;      // bottom right LED pin
const int capsLED = A3;		// caps lock LED pin
const int numberLED = A2;		// numbers LED pin

//const int translate = 12;   // translate pushbutton pin
const int buzzer = 13;		// piezo buzzer pin

int tempCounter = 0;  		// LCD cursor increment counter
int turnedOn = 0;			//Switch for the caps lock and letter to number buttons
String letter;
String number;

void resetInput(void){
  digitalWrite(trLED, LOW);  // turn the LED off
  digitalWrite(tlLED, LOW);  // turn the LED off
  digitalWrite(mrLED, LOW);  // turn the LED off
  digitalWrite(mlLED, LOW);  // turn the LED off
  digitalWrite(brLED, LOW);  // turn the LED off
  digitalWrite(blLED, LOW);  // turn the LED off  
}

void setup(){

  // Set up the LED pinS to be an output:
  pinMode(tlLED, OUTPUT);
  pinMode(mlLED, OUTPUT);
  pinMode(blLED, OUTPUT);
  pinMode(trLED, OUTPUT);
  pinMode(mrLED, OUTPUT);
  pinMode(brLED, OUTPUT);
  pinMode(capsLED, OUTPUT);
  pinMode(numberLED, OUTPUT);

  // Set up the Piezo pin to be an output :
  pinMode(buzzer, OUTPUT);
  
  // Initialize the 16x2
  lcd.begin(16, 2);
} 

//Uncontracted Braille Codes
void loop(){
  buttonValue = analogRead(A0); //Read analog value from A0 pin
  /* Main Buttons analog values 
   * topLeft = 511
   * middleLeft = 256
   * bottomLeft = 146
   * deepLeft = 44
   * topRight = 79
   * middleRight = 64
   * bottomRight = 54
   * deepRight = 38
   */
  extraButton = analogRead(A1); //Read analog value from A1 pin
  /* Extra Buttons analog values 
   * firstButton = 49
   * secondButton = 22
   * thirdButton = 33
   * fourthButton = 28
   */
  
  // variable to hold the pushbutton state
  int translateState; //deepRight button
  
  // variables to hold the LED states
  int tlLEDState, mlLEDState, blLEDState, 
  trLEDState, mrLEDState, brLEDState, capsLEDState, numberLEDState;
  
  // sets cursor to upperleft of the LCD display
  lcd.setCursor(tempCounter, 0); //sets cursor to the next LCD square
  if (tempCounter >= 16){
   lcd.scrollDisplayLeft(); //when LCD is full, it will scroll towards the left
   delay(100);
  } /* Work in Progress (Set the characters to next row)
  if (tempCounter == 19){
  	lcd.setCursor(tempCounter  = 0, 1); //sets cursor to the next LCD row
    if (tempCounter <= 19){
      lcd.setCursor(tempCounter, 1); 
      lcd.scrollDisplayLeft(); //when LCD is full, it will scroll towards the left
      delay(100);
  	}
  }*/
   
  // for reset and translate button
  translateState = HIGH; //sets translateState to HIGH
  if (buttonValue >= 35 && buttonValue <= 40){ //Analog Value is 54
    translateState = LOW;
	tone(buzzer, 293.66, 10); // re frequency
  }
  if (buttonValue >= 40 && buttonValue <= 45){ //Analog Value is 44
    resetInput();
    tone(buzzer, 293.66, 10); // re frequency
  }
  
  // reads if which LED light is turn on. Outputs are based here
  tlLEDState = digitalRead(tlLED);
  mlLEDState = digitalRead(mlLED);
  blLEDState = digitalRead(blLED);
  trLEDState = digitalRead(trLED);
  mrLEDState = digitalRead(mrLED);
  brLEDState = digitalRead(brLED);
  capsLEDState = digitalRead(capsLED);
  numberLEDState = digitalRead(numberLED); 
  
  int punctuation; // checks if the last inputted code is a punctuation mark/symbol

  // turns the LED lights and piezo buzzer ON
  if (buttonValue >= 510 && buttonValue <= 515){ //top left button. the exact value of the top left button is 511
    digitalWrite(tlLED, HIGH);  // turn the LED on
	tone(buzzer, 261.63, 10); // do	frequency
  }
  if (buttonValue >= 255 && buttonValue <= 260){ //middle left button. the exact value of the middle left button is 256
    digitalWrite(mlLED, HIGH);  // turn the LED on
	tone(buzzer, 293.66, 10); // re frequency
  }
  if (buttonValue >= 145 && buttonValue <= 150){ //bottom left button. the exact value of the bottom left button is 146
    digitalWrite(blLED, HIGH);  // turn the LED on
	tone(buzzer, 323.63, 10); // mi frequency
  }
  if (buttonValue >= 75 && buttonValue <= 80){ //top right button. the exact value of the top right button is 79
    digitalWrite(trLED, HIGH);  // turn the LED on 
    tone(buzzer, 349.23, 10); // fa frequency
  }
  if (buttonValue >= 60 && buttonValue <= 65){ //middle right button. the exact value of the top right button is 64
    digitalWrite(mrLED, HIGH);  // turn the LED on
	tone(buzzer, 392, 10); // sol frequency
  }
  if (buttonValue >= 50 && buttonValue <= 55){ //bottom right button. the exact value of the top right button is 54
    digitalWrite(brLED, HIGH);  // turn the LED on
	tone(buzzer, 440, 10); // la frequency
  }

  //for extra buttons (features)
  //CapsLock button ----> exact value of the first button is 49
  if (extraButton >= 45 && extraButton <= 50){ //capsLEDState 
     if (turnedOn == 0){
       digitalWrite(capsLED, HIGH);
       turnedOn = 1; 
     } else if (turnedOn == 1){
       digitalWrite(capsLED, LOW);
       turnedOn = 0;
     }
     tone(buzzer, 400, 10);
     delay(100);
  }
  //Set number translation button ----> exact value of the first button is 22
  if (extraButton >= 20 && extraButton <= 25){ //numberLEDState
     if (turnedOn == 0){
       digitalWrite(numberLED, HIGH);
       turnedOn = 1; 
     } else if (turnedOn == 1){
       digitalWrite(numberLED, LOW);
       turnedOn = 0;
     }
     tone(buzzer, 400, 10);
     delay(100);
  }  
  //Back space button ----> exact value of the first button is 33
  if (extraButton >= 30 && extraButton <= 35){ 
      tempCounter = tempCounter - 1;
      lcd.setCursor(tempCounter, 0);
      lcd.print(" ");
    tone(buzzer, 400, 50);
    delay(100);
  }  
  //Forward Space button ----> exact value of the first button is 28
  if (extraButton >= 25 && extraButton <= 30){
	tempCounter = tempCounter + 1;
    lcd.setCursor(tempCounter, 0);
    lcd.print(" ");
    tone(buzzer, 400, 50);
    delay(100);
  }
  
  //translates braille codes into letters or symbols
  // letters and numbers from lines 197 to 624
  //letter A or number 1
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == LOW && mlLEDState == LOW && mrLEDState == LOW && blLEDState == LOW && brLEDState == LOW){
    letter = "A";
    number = "1";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH){
      letter.toLowerCase();
      lcd.print("a");
   } else {
      lcd.print(number);
      if (punctuation == 1){
        punctuation = 0;
      }
   }  
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter B or number 2 
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == LOW && mlLEDState == HIGH && mrLEDState == LOW && blLEDState == LOW && brLEDState == LOW){
  	letter = "B";
    number = "2";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      lcd.print(number);
      if (punctuation == 1){
        punctuation = 0;
      }
   }  
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter C or number 3
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == HIGH && mlLEDState == LOW && mrLEDState == LOW && blLEDState == LOW && brLEDState == LOW){
    letter = "C";
    number = "3";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      lcd.print(number);
      if (punctuation == 1){
        punctuation = 0;
      }
   }  
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter D or number 4
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == HIGH && mlLEDState == LOW && mrLEDState == HIGH && blLEDState == LOW && brLEDState == LOW){
    letter = "D";
    number = "";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      lcd.print(number);
      if (punctuation == 1){
        punctuation = 0;
      }
   }  
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter E or number 5
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == LOW && mlLEDState == LOW && mrLEDState == HIGH && blLEDState == LOW && brLEDState == LOW){
    letter = "E";
    number = "5";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      lcd.print(number);
      if (punctuation == 1){
        punctuation = 0;
      }
   }  
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter F or number 6
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == HIGH && mlLEDState == HIGH && mrLEDState == LOW && blLEDState == LOW && brLEDState == LOW){
    letter = "F";
    number = "6";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      lcd.print(number);
      if (punctuation == 1){
        punctuation = 0;
      }
   }  
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter G or number 7 
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == HIGH && mlLEDState == HIGH && mrLEDState == HIGH && blLEDState == LOW && brLEDState == LOW){
    letter = "G";
    number = "7";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      lcd.print(number);
      if (punctuation == 1){
        punctuation = 0;
      }
   }  
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter H or number 8 
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == LOW && mlLEDState == HIGH && mrLEDState == HIGH && blLEDState == LOW && brLEDState == LOW){
    letter = "H";
    number = "8";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      lcd.print(number);
      if (punctuation == 1){
        punctuation = 0;
      }
   }  
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter I or number 9
  if (translateState == LOW && tlLEDState == LOW && trLEDState == HIGH && mlLEDState == HIGH && mrLEDState == LOW && blLEDState == LOW && brLEDState == LOW){
    letter = "I";
    number = "9";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      lcd.print(number);
      if (punctuation == 1){
        punctuation = 0;
      }
   }  
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter J or number 0 
  if (translateState == LOW && tlLEDState == LOW && trLEDState == HIGH && mlLEDState == HIGH && mrLEDState == HIGH && blLEDState == LOW && brLEDState == LOW){
    letter = "J";
    number = "0";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      lcd.print(number);
      if (punctuation == 1){
        punctuation = 0;
      }
   }  
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter K
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == LOW && mlLEDState == LOW && mrLEDState == LOW && blLEDState == HIGH && brLEDState == LOW){
    letter = "K";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      resetInput();
   }  
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter L 
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == LOW && mlLEDState == HIGH && mrLEDState == LOW && blLEDState == HIGH && brLEDState == LOW){
    letter = "L";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      resetInput();
   } 
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter M
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == HIGH && mlLEDState == LOW && mrLEDState == LOW && blLEDState == HIGH && brLEDState == LOW){
    letter = "M";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      resetInput();
   }  
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter N
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == HIGH && mlLEDState == LOW && mrLEDState == HIGH && blLEDState == HIGH && brLEDState == LOW){
    letter = "N";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      resetInput();
   }  
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter O
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == LOW && mlLEDState == LOW && mrLEDState == HIGH && blLEDState == HIGH && brLEDState == LOW){
    letter = "O";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      resetInput();
   }
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter P
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == HIGH && mlLEDState == HIGH && mrLEDState == LOW && blLEDState == HIGH && brLEDState == LOW){
    letter = "P";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      resetInput();
   } 
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter Q
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == HIGH && mlLEDState == HIGH && mrLEDState == HIGH && blLEDState == HIGH && brLEDState == LOW){
    letter = "Q";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      resetInput();
   }  
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter R
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == LOW && mlLEDState == HIGH && mrLEDState == HIGH && blLEDState == HIGH && brLEDState == LOW){
    letter = "R";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      resetInput();
   }
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter S
  if (translateState == LOW && tlLEDState == LOW && trLEDState == HIGH && mlLEDState == HIGH && mrLEDState == LOW && blLEDState == HIGH && brLEDState == LOW){
    letter = "S";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      resetInput();
   }
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter T
  if (translateState == LOW && tlLEDState == LOW && trLEDState == HIGH && mlLEDState == HIGH && mrLEDState == HIGH && blLEDState == HIGH && brLEDState == LOW){
    letter = "T";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      resetInput();
   }
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter U
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == LOW && mlLEDState == LOW && mrLEDState == LOW && blLEDState == HIGH && brLEDState == HIGH){
    letter = "U";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      resetInput();
   }
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter V
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == LOW && mlLEDState == HIGH && mrLEDState == LOW && blLEDState == HIGH && brLEDState == HIGH){
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      resetInput();
   }
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter W
  if (translateState == LOW && tlLEDState == LOW && trLEDState == HIGH && mlLEDState == HIGH && mrLEDState == HIGH && blLEDState == LOW && brLEDState == HIGH){
    letter = "W";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      resetInput();
   }
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter X
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == HIGH && mlLEDState == LOW && mrLEDState == LOW && blLEDState == HIGH && brLEDState == HIGH){
    letter = "X";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      resetInput();
   }
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter Y
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == HIGH && mlLEDState == LOW && mrLEDState == HIGH && blLEDState == HIGH && brLEDState == HIGH){
    letter = "Y";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      resetInput();
   }
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  //letter Z
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == LOW && mlLEDState == LOW && mrLEDState == HIGH && blLEDState == HIGH && brLEDState == HIGH){
    letter = "Z";
    if (punctuation == 1 && numberLEDState != HIGH || tempCounter == 0 && numberLEDState != HIGH || capsLEDState == HIGH){
      lcd.print(letter);
      punctuation = 0;
   } else if (numberLEDState != HIGH ){
      letter.toLowerCase();
      lcd.print(letter);
   } else {
      resetInput();
   }
  tempCounter = tempCounter + 1; // moves cursor to the next box
  resetInput();
  }
  
  // symbols 
  //alternate space character (from main buttons)
  if (translateState == LOW && tlLEDState == LOW && trLEDState == LOW && mlLEDState == LOW && mrLEDState == LOW && blLEDState == LOW && brLEDState == HIGH){
    tempCounter = tempCounter + 1; // " " space 
    resetInput();
  }
  //apostrophe or single quotation mark
  if (translateState == LOW && tlLEDState == LOW && trLEDState == LOW && mlLEDState == LOW && mrLEDState == LOW && blLEDState == HIGH && brLEDState == LOW){
    lcd.print("'"); //print
    tempCounter = tempCounter + 1; // moves cursor to next box
    resetInput();
  }
  //comma
  if (translateState == LOW && tlLEDState == LOW && trLEDState == LOW && mlLEDState == HIGH && mrLEDState == LOW && blLEDState == LOW && brLEDState == LOW){
    lcd.print(","); //print
    tempCounter = tempCounter + 1; // moves cursor to next box
    resetInput();
  }
  //dash
  if (translateState == LOW && tlLEDState == LOW && trLEDState == LOW && mlLEDState == HIGH && mrLEDState == HIGH && blLEDState == LOW && brLEDState == LOW){
    lcd.print("-"); //print
    tempCounter = tempCounter + 1; // moves cursor to next box
    resetInput();
  }
  //underscore
  if (translateState == LOW && tlLEDState == LOW && trLEDState == LOW && mlLEDState == LOW && mrLEDState == LOW && blLEDState == HIGH && brLEDState == HIGH){
    lcd.print("-"); //print
    tempCounter = tempCounter + 1; // moves cursor to next box
    resetInput();
  }
  //period
  if (translateState == LOW && tlLEDState == LOW && trLEDState == LOW && mlLEDState == HIGH && mrLEDState == HIGH && blLEDState == LOW && brLEDState == HIGH){
    lcd.print("."); //print
    tempCounter = tempCounter + 1; // moves cursor to next box
    punctuation = 1;
    resetInput();
  }
  //question mark
  if (translateState == LOW && tlLEDState == LOW && trLEDState == LOW && mlLEDState == HIGH && mrLEDState == LOW && blLEDState == HIGH && brLEDState == HIGH){
    lcd.print("?"); //print
    tempCounter = tempCounter + 1; // moves cursor to next box
    punctuation = 1;
    resetInput();
  }
  //exclamation point
  if (translateState == LOW && tlLEDState == LOW && trLEDState == LOW && mlLEDState == HIGH && mrLEDState == HIGH && blLEDState == HIGH && brLEDState == LOW){
    lcd.print("!"); //print
    tempCounter = tempCounter + 1; // moves cursor to next box
    punctuation = 1;
    resetInput();
  }
  //number sign
  if (translateState == LOW && tlLEDState == LOW && trLEDState == HIGH && mlLEDState == LOW && mrLEDState == HIGH && blLEDState == HIGH && brLEDState == HIGH){
    lcd.print("#"); //print
    tempCounter = tempCounter + 1; // moves cursor to next box
    resetInput();
  }
  //ampersand
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == HIGH && mlLEDState == HIGH && mrLEDState == LOW && blLEDState == HIGH && brLEDState == HIGH){
    lcd.print("&"); //print
    tempCounter = tempCounter + 1; // moves cursor to next box
    resetInput();
  }
  //At sign
  if (translateState == LOW && tlLEDState == LOW && trLEDState == HIGH && mlLEDState == LOW && mrLEDState == HIGH && blLEDState == HIGH && brLEDState == LOW){
    lcd.print("@"); //print
    tempCounter = tempCounter + 1; // moves cursor to next box
    resetInput();
  }
  //asterisk
  if (translateState == LOW && tlLEDState == LOW && trLEDState == LOW && mlLEDState == LOW && mrLEDState == HIGH && blLEDState == HIGH && brLEDState == LOW){
    lcd.print("*"); //print
    tempCounter = tempCounter + 1; // moves cursor to next box
    resetInput();
  }
  //lesser than
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == LOW && mlLEDState == HIGH && mrLEDState == LOW && blLEDState == LOW && brLEDState == HIGH){
    lcd.print("<"); //print
    tempCounter = tempCounter + 1; // moves cursor to next box
    resetInput();
  }
  //greater than
  if (translateState == HIGH && tlLEDState == LOW && trLEDState == HIGH && mlLEDState == LOW && mrLEDState == HIGH && blLEDState == HIGH && brLEDState == LOW){
    lcd.print(">"); //print
    tempCounter = tempCounter + 1; // moves cursor to next box
    resetInput();
  }
  //reset
  if (translateState == LOW && tlLEDState == HIGH && trLEDState == HIGH && mlLEDState == HIGH && mrLEDState == HIGH && blLEDState == HIGH && brLEDState == HIGH){
    lcd.clear();
  }
} // end of loop()
