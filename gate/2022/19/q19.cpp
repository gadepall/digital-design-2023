#include<Arduino.h>

int Z,Y,X,W,R,S;
int A,B,C;
void mux_4x1(int C)
{
	digitalWrite(2,C);
}
void setup()
{
	pinMode(2,OUTPUT);
	pinMode(5,INPUT);
	pinMode(6,INPUT);
	pinMode(7,INPUT);
	pinMode(8,INPUT);
}
void loop()
{
	W=digitalRead(5);
	X=digitalRead(6);
	Y=digitalRead(7);
	Z=digitalRead(8);

	A=(!R&&!S&&W)||(!R&&S&&X)||(R&&!S&&Y)||(R&&S&&Z);
	B=(!R&&S)||(R&&!S);
	if(A==B){
		digitalWrite(2,1);
	}
	else{
		digitalWrite(2,0);
	}
}
