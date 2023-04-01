#include <Arduino.h>
int X=0,C=0,B=0,A=0;   
int Y,R,Q,P;          

void fsm_read()
{
  A = digitalRead(6);
  B= digitalRead(7);
  C = digitalRead(8);
  X= digitalRead(9);
}

void fsm_update()
{  
 
 P=(B&&C&&X);
 Q=(B&&!C&&!X)||(!B&&C&&X)||(A&&!X);
 R=(!X);
 Y=(A&&!X);

  digitalWrite(2, P);
  digitalWrite(3, Q);
  digitalWrite(4, R);
  digitalWrite(5, Y);
  
  digitalWrite(13, HIGH);
  delay(2000);
  digitalWrite(13, LOW);
  delay(2000);
  
}
void setup() {
    pinMode(2, OUTPUT);  
    pinMode(3, OUTPUT); 
    pinMode(4, OUTPUT);   
    pinMode(5, OUTPUT);  
    
    pinMode(13, OUTPUT); 
    
    pinMode(6, INPUT);  
    pinMode(7, INPUT);  
    pinMode(8, INPUT);
    pinMode(9, INPUT);  
    
}


void loop()
 {
fsm_read();
fsm_update();
}
