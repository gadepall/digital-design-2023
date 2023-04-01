#include<Arduino.h>

int clockPin = 2; //clock input pin
int q1Pin = 3; //Q output of flip-flop 1 of first IC 7474
int q2Pin = 4; //Q output of flip-flop 2 of first IC 7474
int dPin = 5; //D input of flip-flop of second IC 7474
int qPin = 6; //Q output of flip-flop of second IC 7474


void setup(){
	pinMode(qPin,INPUT);
	pinMode(clockPin,OUTPUT);
	pinMode(q1Pin,OUTPUT);
	pinMode(q2Pin,OUTPUT);
	pinMode(dPin,OUTPUT);
	pinMode(13,OUTPUT);

	//Initialize outputs
	digitalWrite(clockPin,LOW);
	digitalWrite(q1Pin,LOW);
	digitalWrite(q2Pin,LOW);
	digitalWrite(qPin,LOW);
}

void jk_flipflop(int q1){ //code for JK flip-flop with LSB of 2 bit counter as input to both J and K
	int q = digitalRead(qPin);
	int d = q1^q;
	digitalWrite(dPin,d);
	digitalWrite(13,q);
}

void loop(){
	digitalWrite(clockPin,LOW);
	delay(10);
	digitalWrite(clockPin,HIGH);

	int q1=digitalRead(q1Pin);
	int q2=digitalRead(q2Pin);

	q1=!q1;
	if(q1==HIGH) q2=!q2;

	digitalWrite(q1Pin,q1);
	digitalWrite(q2Pin,q2);
	jk_flipflop(q1);
	delay(1000);
}
