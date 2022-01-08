# 1 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
# 2 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 2
# 3 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 2
# 4 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 2
# 5 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 2

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
 pinMode(5, 0x1);
 pinMode(2, 0x1);
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
 Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 50 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
             (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 50 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
             "{\"x\": "
# 50 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
             ); &__c[0];}))
# 50 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
             )));
    Serial.print(xpos);
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 52 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 52 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
                ", \"y\": "
# 52 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
                ); &__c[0];}))
# 52 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
                )));
    Serial.print(ypos);
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 54 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 54 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
                ", \"z\": "
# 54 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
                ); &__c[0];}))
# 54 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
                )));
    Serial.print(zpos);
    Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 56 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
                  (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 56 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
                  "}"
# 56 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino" 3
                  ); &__c[0];}))
# 56 "c:\\Users\\Bayhaqi\\Documents\\Kuliah\\Code\\Arduino\\step\\step.ino"
                  )));
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
