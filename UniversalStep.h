#include <Arduino.h>

class UniversalStep
{
public:
    int dirPin;
    int stepPin;
    int stepPerRevolution;

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

    UniversalStep(int dirPin, int stepPin, int step)
    {
        this->dirPin = dirPin;
        this->stepPin = stepPin;
        this->stepPerRevolution = step;
    }

    void OneStep(bool counterclockwise, int langkah, int speed = 500)
    {

        if (counterclockwise)
        {
            digitalWrite(this->dirPin, LOW);
        }
        else
        {
            digitalWrite(this->dirPin, HIGH);
        }

        for (int i = 0; i < this->stepPerRevolution*langkah; i++)
        {
            digitalWrite(this->stepPin, HIGH);
            delayMicroseconds(speed);
            digitalWrite(this->stepPin, LOW);
            delayMicroseconds(speed);
        }
    }
};