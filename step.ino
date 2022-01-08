#include <Arduino.h>
#include <Stepper.h>
#include <AccelStepper.h>
#include "UniversalStep.h"

UniversalStep st(5, 2, 200);

int val = 5;
bool first = true;
AccelStepper stepX = AccelStepper(1, 2, 5);
AccelStepper stepY = AccelStepper(1, 3, 6);
AccelStepper stepZ = AccelStepper(1, 4, 7);

int xpos = 0;
int ypos = 0;
int zpos = 0;

void setup()
{
	pinMode(5, OUTPUT);
	pinMode(2, OUTPUT);
	Serial.begin(9600);
	Serial.println((String) " DIR :" + st.GetDirPin() + " STEP :" + st.GetStepPin() + " STEPROTATION :" + st.GetStepPerRevolution());
	stepX.setMaxSpeed(1800);
	stepX.setAcceleration(800);
}

void moveAxis(int langkah, int axis)
{
	int posisiLangkah = langkah;
	langkah *= 200;
	Serial.println((String)"langkah : "+ posisiLangkah + " (" + langkah + ")");
	if(axis==1){
		stepX.moveTo(langkah);
		stepX.runToPosition();
		xpos = posisiLangkah;
	}else if(axis==2){
		stepY.moveTo(langkah);
		stepY.runToPosition();
		ypos = posisiLangkah;
	}else{
		stepZ.moveTo(langkah);
		stepZ.runToPosition();
		zpos = posisiLangkah;
	}
	// st.OneStep(true, langkah, 1000);
}

void printLocation(){
	Serial.print(F("{\"x\": "));
    Serial.print(xpos);
    Serial.print(F(", \"y\": "));
    Serial.print(ypos);
    Serial.print(F(", \"z\": "));
    Serial.print(zpos);
    Serial.println(F("}"));
	delay(1000);
}

void resetPosition(){
	st.OneStep(true, 5, 1000);
	first = false;
}

void loop()
{

	if (first)
	{
		resetPosition();
	}

	if (Serial.available() > 1)
	{
		String order = Serial.readStringUntil('\n');
		Serial.println((String)"order :"+ order);
		int langkah = Serial.readStringUntil('\n').toInt();
		if (order == "xaxis"){
			moveAxis(langkah, 1);
		}else if(order == "yaxis"){
			moveAxis(langkah, 2);
		}else{
			moveAxis(langkah, 3);
		}
		printLocation();

	}
}
