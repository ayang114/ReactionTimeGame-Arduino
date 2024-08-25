#include "Timer.h"

const int B[] = {9, 10, 11, 12, 13};
const int button = 2; 
int tracker = 0; //Keeps track of which direction the LED should go
int i = 0;

const int digit1Pin = 3; // LEFT #
const int digit2Pin = 4; // RIGHT #

char segmentPins[] = {32, 33, 34, 35, 36, 37, 38};

int counter;
int tens; 
// int ones;n


//DONT TOUCH==========================================================
void displayNumTo7Seg(unsigned int targetNum, int digitPin) {
    // A map of integers to the respective values needed to display
    // a value on one 7 seg digit.
    unsigned char encodeInt[10] = {
        // 0     1     2     3     4     5     6     7     8     9
        0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67,
    };


    // Make sure the target digit is off while updating the segments iteratively
    //Turn off
    digitalWrite(digitPin, HIGH);


    // Update the segments
    for (int k = 0; k < 7; ++k) {
        digitalWrite(segmentPins[k], encodeInt[targetNum] & (1 << k));
    }


    // Turn on the digit again
    digitalWrite(digitPin, LOW);
}
//DONT TOUCH==========================================================

//got a vague understanding of how the two digits
//are to be lit up simultaneously alongside
//the concept of "continuously keeping
// both lights updated by turning them on and off
// really quickly and updating segments via function" by Jacob Korte
enum SM3_STATE { SM3_SMStart, SM3_LeftNumber, SM3_RightNumber } SM3_STATE;
void Tick_SM2() { 
   switch (SM3_STATE) { 
      case SM3_SMStart:
          SM3_STATE = SM3_RightNumber;
         break;
         
      case SM3_LeftNumber:
         if (1) {
            SM3_STATE = SM3_RightNumber;
         }
         break;

      case SM3_RightNumber:
         if (1) {
            SM3_STATE = SM3_LeftNumber;
         }
         break;
      default:
         SM3_STATE = SM3_LeftNumber;
         break;
   }

   switch (SM3_STATE) { 
      case SM3_SMStart:
         break;

      case SM3_LeftNumber:
        tens = counter / 10;
        digitalWrite(digit2Pin, HIGH);
        displayNumTo7Seg(tens, digit1Pin);
        break;

      case SM3_RightNumber:
        tens = counter % 10;
        //ones = counter % 10;
        digitalWrite(digit1Pin, HIGH);
        // digitalWrite(digit2Pin, HIGH);
        // digitalWrite(digit2Pin, LOW);
        displayNumTo7Seg(tens, digit2Pin);
        // displayNumTo7Seg(ones, digit2Pin);
        break;
   }
}





enum SM2_STATES { SM2_SMStart, SM2_RightRight, SM2_Left, SM2_Right, SM2_Mid, SM2_LeftLeft, SM2_RightRightWait, SM2_LeftWait, SM2_RightWait, SM2_MidWait,    SM2_LeftLeftWait} SM2_STATE;

void Tick_StateMachine2() { 
   switch(SM2_STATE) { 
      case SM2_SMStart:
          i = 0;
          SM2_STATE = SM2_RightRight;
         break;


      case SM2_RightRight:
         if ((digitalRead(button) == LOW) && tracker == 0 && !(i < 10)) {
            i = 0;
            tracker = tracker + 1;
            SM2_STATE = SM2_Right;
         }
         else if ((digitalRead(button) == HIGH) && (i < 10)) {
            counter = 0;
            SM2_STATE = SM2_RightRight;
         }
         else {
            SM2_STATE = SM2_RightRight;
         }
         break;


      case SM2_RightRightWait:
        if ((digitalRead(button) == HIGH)) {
            SM2_STATE = SM2_RightRightWait;
         }
         else if ((digitalRead(button) == LOW) && tracker == 0) {
            tracker = tracker + 1;
            SM2_STATE = SM2_Right;
         }
         break;


      case SM2_Right:
         if ((digitalRead(button) == LOW) && tracker == 1 && !(i < 10)) {
            i = 0;
            tracker = tracker + 1;
            SM2_STATE = SM2_Mid;
         }
         else if ((digitalRead(button) == LOW) && tracker == 7 && !(i < 10)) {
            i = 0;
            tracker = 0;
            SM2_STATE = SM2_RightRight;
         }
         else if ((digitalRead(button) == HIGH) && (i < 10)) {
            counter = 0;
            SM2_STATE = SM2_Right;
         }
         else {
            SM2_STATE = SM2_Right;
         }
         break;


      case SM2_RightWait:
        if ((digitalRead(button) == HIGH)) {
            SM2_STATE = SM2_RightWait;
         }
         else if ((digitalRead(button) == LOW) && tracker == 1) {
            tracker = tracker + 1;
            SM2_STATE = SM2_Mid;
         }
         else if ((digitalRead(button) == LOW) && tracker == 7) {
            tracker = 0;
            SM2_STATE = SM2_RightRight;
         }
         break;


      case SM2_Mid:
         if ((digitalRead(button) == LOW) && tracker == 2 && !(i < 10)) {
            i = 0;
            tracker = tracker + 1; 
            SM2_STATE = SM2_Left;
         }
         else if ((digitalRead(button) == LOW) && tracker == 6 && !(i < 10)) {
            i = 0;
            tracker = tracker + 1;
            SM2_STATE = SM2_Right;
         }
         else if ((digitalRead(button) == HIGH) /*&& (i < 10)*/) {
          counter = counter + 1;
            SM2_STATE = SM2_MidWait;
          }
         else {
            SM2_STATE = SM2_Mid;
         }
         break;


      case SM2_MidWait:
        if ((digitalRead(button) == HIGH)) {
            SM2_STATE = SM2_MidWait;
         }
         else if ((digitalRead(button) == LOW) && tracker == 2) {
          //counter = counter + 1;
            tracker = tracker + 1; 
            SM2_STATE = SM2_Left;
         }
         else if ((digitalRead(button) == LOW) && tracker == 6) {
          //counter = counter + 1;
            tracker = tracker + 1;
            SM2_STATE = SM2_Right;
         }
         break;
         

      case SM2_Left:
         if ((digitalRead(button) == LOW) && tracker == 3 && !(i < 10)) {
            i = 0;
            tracker = tracker + 1;
            SM2_STATE = SM2_LeftLeft;
         }
         else if ((digitalRead(button) == LOW) && tracker == 5 && !(i < 10)) {
            i = 0;
            tracker = tracker + 1;
            SM2_STATE = SM2_Mid;
         }
         else if ((digitalRead(button) == HIGH) && (i < 10)) {
            counter = 0;
            SM2_STATE = SM2_Left;
         }
         else {
            SM2_STATE = SM2_Left;
         }
         break;


      case SM2_LeftWait:
        if ((digitalRead(button) == HIGH)) {
            SM2_STATE = SM2_LeftWait;
         }
         else if ((digitalRead(button) == LOW) && tracker == 3) {
            tracker = tracker + 1;
            SM2_STATE = SM2_LeftLeft;
         }
         else if ((digitalRead(button) == LOW) && tracker == 5) {
            tracker = tracker + 1;
            SM2_STATE = SM2_Mid;
         }
         break;


      case SM2_LeftLeft:
         if ((digitalRead(button) == LOW) && tracker == 4 && !(i < 10)) {
            i = 0;
            tracker = tracker + 1;
            SM2_STATE = SM2_Left;
         }
         else if ((digitalRead(button) == HIGH) && (i < 10)) {
            counter = 0;
            SM2_STATE = SM2_LeftLeft;
         }
         else {
            SM2_STATE = SM2_LeftLeft;
         }
         break;

      case SM2_LeftLeftWait:
         if ((digitalRead(button) == LOW) && tracker == 4) {
            tracker = tracker + 1;
            SM2_STATE = SM2_Left;
         }
         else if ((digitalRead(button) == HIGH)) {
            SM2_STATE = SM2_LeftLeftWait;
         }
         else {
            SM2_STATE = SM2_LeftLeftWait;
         }

         break;


      default:
         SM2_STATE = SM2_RightRight;
         break;
   }
   switch(SM2_STATE) { 
      case SM2_SMStart:
         
         break;


      case SM2_RightRight:
          digitalWrite(B[0], LOW);
          digitalWrite(B[1], LOW);
          digitalWrite(B[2], LOW);
          digitalWrite(B[3], LOW);
          digitalWrite(B[4], HIGH);
          i++;
         break;

      case SM2_Right:
          digitalWrite(B[0], LOW);
          digitalWrite(B[1], LOW);
          digitalWrite(B[2], LOW);
          digitalWrite(B[3], HIGH);
          digitalWrite(B[4], LOW);
          i++;
         break;
         
      case SM2_Mid:
          digitalWrite(B[0], LOW);
          digitalWrite(B[1], LOW);
          digitalWrite(B[2], HIGH);
          digitalWrite(B[3], LOW);
          digitalWrite(B[4], LOW);
          i++;
         break;

      case SM2_Left:
          digitalWrite(B[0], LOW);
          digitalWrite(B[1], HIGH);
          digitalWrite(B[2], LOW);
          digitalWrite(B[3], LOW);
          digitalWrite(B[4], LOW);
          i++;
         break;

      case SM2_LeftLeft:
          digitalWrite(B[0], HIGH);
          digitalWrite(B[1], LOW);
          digitalWrite(B[2], LOW);
          digitalWrite(B[3], LOW);
          digitalWrite(B[4], LOW);
          i++;
         break;
  
        case SM2_MidWait:
          //counter = counter + 1;
         break;
         
   }
}

void setup() {
// TURNED OFF CAUSE ITS TOO BRIGHT AND HURTS MY EYES
/*
  pinMode(B[0], OUTPUT);
  pinMode(B[1], OUTPUT);
  pinMode(B[2], OUTPUT);
  pinMode(B[3], OUTPUT);
  pinMode(B[4], OUTPUT);
*/

  pinMode(button, INPUT);

  digitalWrite(B[0], LOW);
  digitalWrite(B[1], LOW);
  digitalWrite(B[2], LOW);
  digitalWrite(B[3], LOW);
  digitalWrite(B[4], LOW);

  pinMode(digit1Pin, OUTPUT);
  pinMode(digit2Pin, OUTPUT);
  
  pinMode(segmentPins[0], OUTPUT);
  pinMode(segmentPins[1], OUTPUT);
  pinMode(segmentPins[2], OUTPUT);
  pinMode(segmentPins[3], OUTPUT);
  pinMode(segmentPins[4], OUTPUT);
  pinMode(segmentPins[5], OUTPUT);
  pinMode(segmentPins[6], OUTPUT);
  pinMode(segmentPins[7], OUTPUT);
  pinMode(segmentPins[8], OUTPUT);

  TimerSet(10);
  TimerOn();

  Serial.begin(9600);
}

void loop() {

  Tick_SM2();
  Tick_StateMachine2();

  while(!TimerFlag){}
  TimerFlag = 0;

}
