#include <Arduino.h>
#include <Stepper.h>
#include <AccelStepper.h>
#include "UniversalStep.h"
#define air 28
#define npk 30
#define limit_switch_pin_x 26
#define limit_switch_pin_y 24

UniversalStep stx(5, 2, 200);
UniversalStep sty(6, 3, 200);
UniversalStep stz(7, 4, 200);

int val = 5;
bool first = true;
bool resetFirst = true;
AccelStepper stepX = AccelStepper(1, 2, 5);
AccelStepper stepY = AccelStepper(1, 3, 6);
AccelStepper stepZ = AccelStepper(1, 4, 7);

bool resetPosX = true;
bool resetPosY = true;
bool resetPosZ = false;
int speed = 1000;
int xpos = 0;
int ypos = 0;
int zpos = 0;
int cmd = 0;
int delayTime = 0;
int maxSpeed = 700;
int maxAccel = 700;

int msy = 380;
int may = 2800;

void setup()
{
	pinMode(5, OUTPUT);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(air, OUTPUT);
	pinMode(npk, OUTPUT);
	Serial.begin(9600);
	pinMode(limit_switch_pin_x, INPUT_PULLUP);
	pinMode(limit_switch_pin_y, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(limit_switch_pin_x), stopMotorX, FALLING);

	// Serial.println((String) " DIR :" + stx.GetDirPin() + " STEP :" + stx.GetStepPin() + " STEPROTATION :" + stx.GetStepPerRevolution());
	stepX.setMaxSpeed(maxSpeed);
	stepX.setAcceleration(maxAccel);
	stepY.setMaxSpeed(msy);
	stepY.setAcceleration(may);
	stepZ.setMaxSpeed(msy);
	stepZ.setAcceleration(may);
	disStep();
}

void disStep()
{
	stepY.disableOutputs();
	stepX.disableOutputs();
	stepZ.disableOutputs();
}

void enStep()
{
	stepY.enableOutputs();
	stepX.enableOutputs();
	stepZ.enableOutputs();
}

void moveAxis(int langkah, int axis)
{
	enStep();
	int posisiLangkah = langkah;
	langkah *= 200;
	Serial.println((String) "langkah : " + posisiLangkah + " (" + langkah + ")");
	if (axis == 1)
	{
		stepX.moveTo(langkah);
		stepX.runToPosition();
		xpos = posisiLangkah;
	}
	else if (axis == 2)
	{
		stepY.moveTo(langkah);
		stepY.runToPosition();
		ypos = posisiLangkah;
		disStep();
		doCommand(cmd);
	}
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
		digitalWrite(air, HIGH);
		delay(8000);
		digitalWrite(air, LOW);
	}
	else if (cmd == 7)
	{
		digitalWrite(npk, HIGH);
		delay(30000);
		digitalWrite(npk, LOW);
	}
	else if (cmd == 6)
	{
		stepZ.moveTo(30);
		stepZ.runToPosition();
		delay(5500);
		stepZ.moveTo(0);
		stepZ.runToPosition();
		zpos = 0;
	}
	checkoutSerial("1");
}

void resetPositionZero()
{
	resetPosX = true;
	resetPosY = true;
	// while (loop)
	// {
	//
	// }

	// checkoutSerial("2");

	// home = false;
	// while (!home)
	// {
	// 	if (motor_stop == true)
	// 	{
	// 		stopMotor();
	// 		home = true;
	// 	}
	// 	else
	// 	{
	//
	// 		checkoutSerial("2");
	// 		if (digitalRead(26) == LOW)
	// 		{
	// 			delay(200);
	// 			motor_stop = false;
	// 		}
	// 	}
	// }

	// if (digitalRead(26) == LOW)
	// {
	// 	delay(200);
	// 	motor_stop = false;
	// }
	// else
	// {
	// 	stx.OneStep(10, 1000);
	// 	sty.OneStep(10, 1000);
	// 	stz.OneStep(-10, 1000);
	// 	resetPositionZero();
	// }
}

void checkoutSerial(String status)
{
	if (status == "1")
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
		Serial.print(F(", \"status\": \""));
		Serial.print(status);
		Serial.println(F("\"}"));
		delay(1000);
	}
	else
	{
		delay(1000);
		Serial.print(F("{"));
		Serial.print(F("\"status\": \""));
		Serial.print(status);
		Serial.print(F("\", \"cmd\": "));
		Serial.print(cmd);
		Serial.println(F("}"));
		delay(1000);
	}
	delay(5000);
}

void resetPosition()
{
	// stx.OneStep(10, 1000);
	// sty.OneStep(10, 1000);
	// stz.OneStep(-10, 1000);
	// resetPositionZero();
	first = false;
	cmd = 0;
}

void recPerintah()
{

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
			checkoutSerial("c");
		}
		else if (order == "start")
		{
			Serial.println("start");
		}
		else if (order == "e")
		{
			checkoutSerial("2");
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
		// else if (order == "z")
		// {
		// 	moveAxis(incomingValue, 3);
		// }
		else if (order == "dt")
		{
			delayTime = incomingValue;
		}
		else if (order == "d")
		{
			delay(2000);
		}
		else if (order == "r")
		{
			if (incomingValue == 1)
			{
				resetPositionZero();
			}
			else
			{
				checkoutSerial("2");
			}
		}
		// printLocation();
	}
}

void stopMotorX() // function activated by the pressed microswitch
{
	stepX.setCurrentPosition(0); // reset position
	stepX.stop();				 // stop motor
	stepX.disableOutputs();		 // disable power
	xpos = 0;
	resetPosX = false;
	checkReset();
}

void stopMotorY() // function activated by the pressed microswitch
{
	stepY.setCurrentPosition(0); // reset position
	stepY.stop();				 // stop motor
	stepY.disableOutputs();		 // disable power
	ypos = 0;
	resetPosY = false;
	checkReset();
}

void stopMotorZ() // function activated by the pressed microswitch
{
	stepZ.setCurrentPosition(0); // reset position
	stepZ.stop();				 // stop motor
	stepZ.disableOutputs();		 // disable power
	zpos = 0;
}

void checkReset()
{
	if (!resetPosX && !resetPosZ)
	{
		if(resetFirst){
			resetFirst = false;
			Serial.println((String) "start");
		}else{
			checkoutSerial("2");
		}
	}
}

void resetLoop()
{
	if (resetPosX)
	{
		xpos = 0;
		stx.OneStep(5, 1000);
		if (digitalRead(26) == LOW)
		{
			stopMotorX();
		}
	}

	if (resetPosY)
	{
		ypos = 0;
		sty.OneStep(5, 1200);
		if (digitalRead(24) == LOW)
		{
			stopMotorY();
		}
	}
}

void loop()
{
	delay(200);

	if (digitalRead(26) == LOW)
	{
		// Serial.println("pressed");
	}
	// Serial.println((String)"START");
	digitalWrite(LED_BUILTIN, HIGH);
	// delay(1000);
	digitalWrite(LED_BUILTIN, LOW);

	if (first)
	{
		digitalWrite(air, LOW);
		digitalWrite(npk, LOW);
		// Serial.println((String) "start");
		delay(1000);
		resetPosition();
	}

	recPerintah();
	resetLoop();
}
