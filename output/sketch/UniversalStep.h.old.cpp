#line 1 "c:\\Users\\Bayhaqi101\\Documents\\Project\\Farmbot-Arduino\\UniversalStep.h.old.cpp"
#include <Arduino.h>

class UniversalStep
{
    public:
        int dirPin;
        int stepPin;
        int stepPerRevolution;  

        UniversalStep(int dirPin,int stepPin,int step){
            UniversalStep::dirPin = dirPin;
            UniversalStep::stepPin = stepPin;
            UniversalStep::stepPerRevolution = step;
        }

        void OneStep(bool counterclockwise){
            
            if (counterclockwise){
                digitalWrite(this->dirPin, LOW);
            }else{
                digitalWrite(this->dirPin, HIGH);
            }

            for (int i = 0; i < this->stepPerRevolution; i++) {
                digitalWrite(this->stepPin, HIGH);
                delayMicroseconds(1000);
                digitalWrite(this->stepPin, LOW);
                delayMicroseconds(1000);
            }

        }

};