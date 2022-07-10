#include <Arduino.h>
#include <Stepper.h>
#include <AccelStepper.h>
#include "UniversalStep.h"
#define air 30

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
int delayTime = 0;
int maxSpeed = 700;
int maxAccel = 700;
void setup()
{
	pinMode(5, OUTPUT);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(air, OUTPUT);
	Serial.begin(9600);
	// Serial.println((String) " DIR :" + stx.GetDirPin() + " STEP :" + stx.GetStepPin() + " STEPROTATION :" + stx.GetStepPerRevolution());
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
	langkah *= 200;
	Serial.println((String) "langkah : " + posisiLangkah + " (" + langkah + ")");
	if (axis == 1)
	{
		stepX.moveTo(langkah);
		stepX.runToPosition();
		xpos = posisiLangkah;

		// stx.OneStep(langkah, speed);
		// xpos = stx.GetLokasi();
	}
	else if (axis == 2)
	{
		stepY.moveTo(langkah);
		stepY.runToPosition();
		ypos = posisiLangkah;

		doCommand(cmd);
		checkoutSerial(2);

		// sty.OneStep(langkah, speed);
		// ypos = sty.GetLokasi();
	}
	else
	{
		stepZ.moveTo(langkah);
		stepZ.runToPosition();
		zpos = posisiLangkah;

		// stz.OneStep(langkah, speed);
		// zpos = stz.GetLokasi();
	}

	// stx.OneStep(true, langkah, 1000);
	// doCommand(cmd);
	// checkoutSerial(1);
}

void printLocation()
{
	Serial.print(F("{\"x\": "));
	Serial.print(xpos);
	Serial.print(F(", \"y\": "));
	Serial.print(ypos);
	Serial.print(F(", \"z\": "));
	Serial.print(zpos);
	Serial.println(F("}"));
	delay(1000);
}

void doCommand(int cm)
{
	if (cm == 1)
	{
	}
	else if (cm == 2)
	{
		digitalWrite(air, LOW);
		delay(8000);
		digitalWrite(air, HIGH);
	}
	else if (cmd == 6)
	{
		stepZ.moveTo(30);
		stepZ.runToPosition();
		zpos = 30;
		checkoutSerial(cmd);
	}
}

void resetPositionZero()
{
	stepZ.moveTo(0);
	stepZ.runToPosition();
	stepY.moveTo(0);
	stepY.runToPosition();
	stepX.moveTo(0);
	stepX.runToPosition();
}

void checkoutSerial(int status)
{
	if (status == 1)
	{
		delay(1000);
		Serial.print(F("{\"x\": "));
		Serial.print(xpos);
		Serial.print(F(", \"y\": "));
		Serial.print(ypos);
		Serial.print(F(", \"z\": "));
		Serial.print(zpos);
		Serial.print(F(", \"cmd\": "));
		Serial.print(cmd);
		Serial.print(F(", \"status\": "));
		Serial.print(status);
		Serial.println(F("}"));
		delay(1000);
	}
	else
	{
		delay(1000);
		Serial.print(F("{"));
		Serial.print(F("\"status\": "));
		Serial.print(status);
		Serial.print(F(", \"cmd\": "));
		Serial.print(cmd);
		Serial.println(F("}"));
		delay(1000);
		cmd = 0;
	}
	delay(5000);
}

void resetPosition()
{
	stx.OneStep(10, 1000);
	sty.OneStep(10, 1000);
	stz.OneStep(10, 1000);
	first = false;
}

void loop()
{
	// Serial.println((String)"START");
	digitalWrite(LED_BUILTIN, HIGH);
	delay(1000);
	digitalWrite(LED_BUILTIN, LOW);

	if (first)
	{
		digitalWrite(air, HIGH);
		Serial.println((String) "start");
		delay(1000);
		resetPosition();
	}

	if (Serial.available() > 1)
	{
		String order = Serial.readStringUntil('\n');
		Serial.println((String) "order :" + order);
		delay(1000);
		int incomingValue = Serial.readStringUntil('\n').toInt();
		Serial.println((String) "value :" + incomingValue);
		delay(1000);
		if (order == "c")
		{
			cmd = incomingValue;
		}
		else if (order == "start")
		{
			Serial.println("start");
		}
		else if (order == "e")
		{
			checkoutSerial(2);
		}
		else if (order == "dd")
		{
			doCommand(cmd);
		}
		else if (order == "m")
		{
			// maxSpeed = incomingValue;
		}
		else if (order == "a")
		{
			// maxAccel = incomingValue;
		}
		else if (order == "x")
		{
			moveAxis(incomingValue, 1);
		}
		else if (order == "y")
		{
			moveAxis(incomingValue, 2);
		}
		else if (order == "z")
		{
			moveAxis(incomingValue, 3);
		}
		else if (order == "dt")
		{
			delayTime = incomingValue;
		}
		else if (order == "d")
		{
			delay(2000);
		}else if (order == "r"){
			resetPositionZero();
		}
		// printLocation();
	}
}
