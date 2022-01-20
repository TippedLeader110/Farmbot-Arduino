# 1 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
# 2 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 2
# 3 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 2
# 4 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 2
# 5 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 2

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
void setup()
{
 pinMode(5, 0x1);
 pinMode(13, 0x1);
 pinMode(2, 0x1);
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
 Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 69 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
             (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 69 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
             "{\"x\": "
# 69 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
             ); &__c[0];}))
# 69 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
             )));
    Serial.print(xpos);
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 71 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 71 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
                ", \"y\": "
# 71 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
                ); &__c[0];}))
# 71 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
                )));
    Serial.print(ypos);
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 73 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 73 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
                ", \"z\": "
# 73 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
                ); &__c[0];}))
# 73 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
                )));
    Serial.print(zpos);
    Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 75 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
                  (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 75 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
                  "}"
# 75 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
                  ); &__c[0];}))
# 75 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
                  )));
 delay(1000);
}

void checkoutSerial(){
 Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 80 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
             (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 80 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
             "{\"x\": "
# 80 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
             ); &__c[0];}))
# 80 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
             )));
    Serial.print(xpos);
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 82 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 82 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
                ", \"y\": "
# 82 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
                ); &__c[0];}))
# 82 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
                )));
    Serial.print(ypos);
 Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 84 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
             (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 84 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
             ", \"z\": "
# 84 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
             ); &__c[0];}))
# 84 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
             )));
    Serial.print(zpos);
 Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 86 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
             (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 86 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
             ", \"cmd\": "
# 86 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
             ); &__c[0];}))
# 86 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
             )));
    Serial.print(cmd);
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 88 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 88 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
                ", \"status\": "
# 88 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
                ); &__c[0];}))
# 88 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
                )));
    Serial.print(true);
    Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 90 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
                  (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 90 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
                  "}"
# 90 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
                  ); &__c[0];}))
# 90 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
                  )));
 cmd = 0;
 delay(1000);
}

void resetPosition(){
 stx.OneStep(5, 1000);
 first = false;
}

void loop()
{
 digitalWrite(13, 0x1);
 delay(1000);
 digitalWrite(13, 0x0);

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
