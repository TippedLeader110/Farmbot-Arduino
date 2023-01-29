#line 1 "c:\\Users\\Bayhaqi101\\Documents\\Project\\Farmbot-Arduino\\UniversalStep.h"
#include <Arduino.h>

class UniversalStep
{
public:
    int dirPin;
    int stepPin;
    int stepPerRevolution;
    int lokasi;
    int jumlahLangkah;

    int GetDirPin() const
    {
        return dirPin;
    }

    int GetStepPin() const
    {
        return stepPin;
    }

    int GetStepPerRevolution() const
    {
        return stepPerRevolution;
    }

    int GetLokasi(){
        return this->lokasi;
    }

    UniversalStep(int dirPin, int stepPin, int step)
    {
        this->dirPin = dirPin;
        this->stepPin = stepPin;
        this->stepPerRevolution = step;
        this->lokasi = 0;
        this->jumlahLangkah = 0;
    }

    bool checkArah(int posisi){
        if(this->lokasi > posisi){
            this->jumlahLangkah = lokasi - posisi;
            return false;
        }else{
            this->jumlahLangkah = posisi - this->lokasi;
            return true;
        }
    }

    void OneStep(int posisi, int speed = 500)
    {
        this->jumlahLangkah = 0;

        if (checkArah(posisi))
        {
            digitalWrite(this->dirPin, LOW);
        }
        else
        {
            digitalWrite(this->dirPin, HIGH);
        }

        for (int i = 0; i < this->stepPerRevolution*jumlahLangkah; i++)
        {
            digitalWrite(this->stepPin, HIGH);
            delayMicroseconds(speed);
            digitalWrite(this->stepPin, LOW);
            delayMicroseconds(speed);
        }
    }
};
#line 1 "c:\\Users\\Bayhaqi101\\Documents\\Project\\Farmbot-Arduino\\step.ino"
#include <Arduino.h>
#include <Stepper.h>
#include <AccelStepper.h>
#include "UniversalStep.h"
#define air 28
#define npk 30
#define limit_switch_pin_x 26
#define limit_switch_pin_y 24
#define limit_switch_pin_z 22

UniversalStep stx(5, 2, 200);
UniversalStep sty(6, 3, 200);
UniversalStep stz(7, 4, 200);

int val = 5;
bool first = true;
bool resetFirst = true;
AccelStepper stepX = AccelStepper(1, 2, 5);
AccelStepper stepY = AccelStepper(1, 3, 6);
AccelStepper stepZ = AccelStepper(1, 4, 7);

int countFirst = 0;
bool terhubung = false;
bool resetPosX = true;
bool resetPosY = true;
bool resetPosZ = true;
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
	pinMode(limit_switch_pin_z, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(limit_switch_pin_x), stopMotorX, FALLING);

	// Serial.println((String) " DIR :" + stx.GetDirPin() + " STEP :" + stx.GetStepPin() + " STEPROTATION :" + stx.GetStepPerRevolution());
	stepX.setMaxSpeed(maxSpeed);
	stepX.setAcceleration(maxAccel);
	stepY.setMaxSpeed(msy);
	stepY.setAcceleration(may);
	stepZ.setMaxSpeed(300);
	stepZ.setAcceleration(300);
	// stepZ.setSpeed(160);
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
	langkah *= 200;
	int posisiLangkah = langkah;
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
		digitalWrite(air, HIGH);
		delay(3000);
		digitalWrite(air, LOW);
		int posDown = 70 * 200;
		stepX.moveTo(xpos + (10 * 200));
		stepX.runToPosition();
		stepZ.moveTo(posDown * (-1));
		stepZ.runToPosition();
		zpos = 0;
	}
	checkoutSerial("1");
}

void resetPositionZero()
{
	resetPosX = true;
	resetPosY = true;
	resetPosZ = true;
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
		// delay(1000);
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
		// delay(1000);
	}
	delay(2000);
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
			terhubung = true;
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
	resetPosZ = false;
	checkReset();
}

void checkReset()
{
	if(resetPosX){
		Serial.println((String) "X True");
	}else{
		Serial.println((String) "X False");
	}

	if(resetPosY){
		Serial.println((String) "Y True");
	}else{
		Serial.println((String) "Y False");
	}

	if(resetPosZ){
		Serial.println((String) "Z True");
	}else{
		Serial.println((String) "Z False");
	}

	if (!resetPosX && !resetPosY && !resetPosZ)
	{
		if (resetFirst && countFirst == 0)
		{
			resetFirst = false;
			countFirst++;
			Serial.println((String) "start");
		}
		else if (!resetFirst && terhubung)
		{
			checkoutSerial("2");
		}
	}
}

void resetLoop()
{

	if (resetPosZ)
	{
		// Serial.println((String) "resetPosZ true");

		zpos = 0;
		stz.OneStep(7, 4500);
		// stepZ.moveTo(10);
		// stepZ.setCurrentPosition(0);
		// stepX.runToPosition();
		if (digitalRead(limit_switch_pin_z) == LOW)
		{
			stopMotorZ();
		}
	}

	if (resetPosX)
	{
		// Serial.println((String) "resetPosX true");
		xpos = 0;
		stx.OneStep(5, 1800);
		if (digitalRead(limit_switch_pin_x) == LOW)
		{
			stopMotorX();
		}
	}

	if (resetPosY)
	{
		// Serial.println((String) "resetPosY true");
		ypos = 0;
		sty.OneStep(5, 1200);
		if (digitalRead(limit_switch_pin_y) == LOW)
		{
			stopMotorY();
		}
	}
}

void loop()
{
	// delay(200);

	if (digitalRead(24) == LOW)
	{
		// Serial.println("pressed z");
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

