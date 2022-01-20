#line 1 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\UniversalStep.h"
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