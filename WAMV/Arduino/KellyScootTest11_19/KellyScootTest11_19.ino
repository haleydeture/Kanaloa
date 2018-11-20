#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm;

const int pwmpin=4;

void setup() {
  // put your setup code here, to run once:
pinMode(pwmpin,OUTPUT);
Serial.begin(9600);
pwm.begin();
pwm.setPWMFreq(490);
}
void loop() {
  // put your main code here, to run repeatedly:
pulsetest1();
//continuous1();
}


//For analogWrite(
//80 min
//180 max

void continuous1(void){
  //Continuously ramp up from 0-3V and down from 3V-0V
  for(int i=0;i<128;i++){
  analogWrite(pwmpin,i);
  Serial.println(i);
  delay(100);
  //pwm.setPin(pwmpin,i,false);
}
for(int i=128;i>0;i=i-1){
  //pwm.setPin(pwmpin,i,false);
  analogWrite(pwmpin,i);
  Serial.println(i);
  delay(100);
}
}

void pulsetest1(void){
  //Tests Thrusters Ability to reset speed in air
  //Fastests switch so far: 130ms (delay(300);) Determined Audibly
  //However, for visual differences in speed, it is dependent on the maximum speed (higher speeds=more time in delays);
analogWrite(pwmpin,50);
delay(130);
analogWrite(pwmpin,128); //High Speed
delay(3000);
analogWrite(pwmpin,50); // Reset
delay(1000);
analogWrite(pwmpin,95); //Medium Speed
delay(3000);
analogWrite(pwmpin,50); //Reset
delay(500);
analogWrite(pwmpin,58);//Low Speed
delay(7000);
}

void continuous2(void){
//Continuously ramp up and down voltage between 1V and 2V
//Hope it doesn't get stuck forward...
for(int i=400;i< 1800;i++){
  pwm.setPin(pwmpin,i,false);
  delay(10);
}
for(int i=1800; i>400; i--){
  pwm.setPin(pwmpin,i,false);
  delay(10);
}
}


void pulsetest2(void){
  //Sets Thruster to 10%, 30% and 50%.
  pwm.setPin(pwmpin,400,false); //10%
delay(3000);
pwm.setPin(pwmpin,1200,false); //30%
delay(3000);
pwm.setPin(pwmpin,2048,false); //50%
delay(3000);
pwm.setPin(pwmpin,2400,false); //10%
delay(1000);
pwm.setPin(pwmpin,1200,false); //30%
delay(3000);
}
