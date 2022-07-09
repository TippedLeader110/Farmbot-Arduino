# 1 "c:\\Users\\Bayhaqi\\Documents\\project\\arduino\\Farmbot-Arduino\\UniversalStep.h"
# 2 "c:\\Users\\Bayhaqi\\Documents\\project\\arduino\\Farmbot-Arduino\\UniversalStep.h" 2

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
            digitalWrite(this->dirPin, 0x0);
        }
        else
        {
            digitalWrite(this->dirPin, 0x1);
        }

        for (int i = 0; i < this->stepPerRevolution*jumlahLangkah; i++)
        {
            digitalWrite(this->stepPin, 0x1);
            delayMicroseconds(speed);
            digitalWrite(this->stepPin, 0x0);
            delayMicroseconds(speed);
        }
    }
};
# 1 "c:\\Users\\Bayhaqi\\Documents\\project\\arduino\\Farmbot-Arduino\\step.ino"
