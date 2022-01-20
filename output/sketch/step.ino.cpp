#line 1 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
#include <Arduino.h>
#include <Stepper.h>
#include <AccelStepper.h>
#include "UniversalStep.h"

UniversalStep stx(5, 2, 200);
UniversalStep sty(6, 3, 200);
UniversalStep stz(7, 4, 200);


int val = 5;
bool first = true;
AccelStepper stepX = AccelStepper(1, 2, 5);
AccelStepper stepY = AccelStepper(1, 3, 6);
AccelStepper stepZ = AccelStepper(1, 4, 7);

int speed = 1000;
int xpos = 0;
int ypos = 0;
int zpos = 0;
int cmd = 0;
int maxSpeed = 1200;
int maxAccel = 700;
#line 24 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
void setup();
#line 39 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
void moveAxis(int langkah, int axis);
#line 68 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
void printLocation();
#line 79 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
void checkoutSerial();
#line 95 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
void resetPosition();
#line 100 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
void loop();
#line 24 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
void setup()
{
	pinMode(5, OUTPUT);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(2, OUTPUT);
	Serial.begin(9600);
	Serial.println((String) " DIR :" + stx.GetDirPin() + " STEP :" + stx.GetStepPin() + " STEPROTATION :" + stx.GetStepPerRevolution());
	stepX.setMaxSpeed(maxSpeed);
	stepX.setAcceleration(maxAccel);
	stepY.setMaxSpeed(maxSpeed);
	stepY.setAcceleration(maxAccel);
	stepZ.setMaxSpeed(maxSpeed);
	stepZ.setAcceleration(maxAccel);
}

void moveAxis(int langkah, int axis)
{
	int posisiLangkah = langkah;
	Serial.println((String)"langkah : "+ posisiLangkah + " (" + langkah + ")");
	if(axis==1){
		// stepX.moveTo(langkah);
		// stepX.runToPosition();
		// xpos = posisiLangkah;

		stx.OneStep(langkah, speed);
		xpos = stx.GetLokasi();

	}else if(axis==2){
		// stepY.moveTo(langkah);
		// stepY.runToPosition();
		// ypos = posisiLangkah;
		sty.OneStep(langkah, speed);
		ypos = sty.GetLokasi();
	}else{
		// stepZ.moveTo(langkah);
		// stepZ.runToPosition();
		// zpos = posisiLangkah;

		stz.OneStep(langkah, speed);
		zpos = stz.GetLokasi();
	}
	// stx.OneStep(true, langkah, 1000);
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

void checkoutSerial(){
	Serial.print(F("{\"x\": "));
    Serial.print(xpos);
    Serial.print(F(", \"y\": "));
    Serial.print(ypos);
	Serial.print(F(", \"z\": "));
    Serial.print(zpos);
	Serial.print(F(", \"cmd\": "));
    Serial.print(cmd);
    Serial.print(F(", \"status\": "));
    Serial.print(true);
    Serial.println(F("}"));
	cmd = 0;
	delay(1000);
}

void resetPosition(){
	stx.OneStep(5, 1000);
	first = false;
}

void loop()
{
	digitalWrite(LED_BUILTIN, HIGH);
	delay(1000);
	digitalWrite(LED_BUILTIN, LOW);

	if (first)
	{
		resetPosition();
	}

	if (Serial.available() > 1)
	{
		String order = Serial.readStringUntil('\n');
		Serial.println((String)"order :"+ order);
		int incomingValue = Serial.readStringUntil('\n').toInt();
		Serial.println((String)"value :"+ incomingValue);
		if(order == "c"){
			cmd = incomingValue;
		}
		else if(order =="e"){
			checkoutSerial();
		}
		else if(order=="m"){
			maxSpeed = incomingValue;
		}else if(order=="a"){
			maxAccel = incomingValue;
		}
		else if (order == "x"){
			moveAxis(incomingValue, 1);
		}else if(order == "y"){
			moveAxis(incomingValue, 2);
		}else{
			moveAxis(incomingValue, 3);
		}
		// printLocation();

	}
}

