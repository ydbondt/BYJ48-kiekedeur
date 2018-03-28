#include "Arduino.h"
#include "kiekedeur.h"

#define IN1  6
#define IN2  7
#define IN3  8
#define IN4  9

int steps = 0;
bool direction = true;
unsigned long last_time;
unsigned long currentMillis ;
long time;

Kiekedeur::Kiekedeur() { 
  Serial.begin(115200);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT); 
}

void setDirection(){
  if(direction==1){ steps++;}
  if(direction==0){ steps--; }
  if(steps>7){steps=0;}
  if(steps<0){steps=7; }
}

void stepper(int xw){
  for (int x=0;x<xw;x++){
    switch(steps){
       case 0:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, HIGH);
       break; 
       case 1:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, HIGH);
       break; 
       case 2:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, LOW);
       break; 
       case 3:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, LOW);
       break; 
       case 4:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break; 
       case 5:
         digitalWrite(IN1, HIGH); 
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break; 
         case 6:
         digitalWrite(IN1, HIGH); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break; 
       case 7:
         digitalWrite(IN1, HIGH); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, HIGH);
       break; 
       default:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
       break; 
    }
    setDirection();
  }
} 


void draai(int clockwise) {
  direction = clockwise;
  int steps_left=4095;
  while(steps_left>0){
    currentMillis = micros();
    if(currentMillis-last_time>=1000){
      stepper(1); 
      time=time+micros()-last_time;
      last_time=micros();
      steps_left--;
    }
  }
}

void Kiekedeur::open() {
  draai(1);
}

void Kiekedeur::toe() {
  draai(0);
}
