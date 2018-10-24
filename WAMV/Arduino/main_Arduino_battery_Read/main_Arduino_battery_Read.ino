//Rewritten function of readMainBatteryVoltage for mainArduino

byte mainVoltagelast=50;
void readMainBatteryVoltage() {
  // Reads PWM signals from battery Arduino and converts it into a PWM value.

  unsigned long maxlength= 2041; //Max length to measure the length of a signal  

  //Read PWM signal from battery Arduino
  byte PWMmainVoltagepin = A0;
  int mainVoltagePWM = pulseIn(PWMmainVoltagepin, HIGH, maxlength);
  
  //The two cases below are in case the duty cycle of the PWM signal is either 0% (OV) or 100% (50V)
  if (mainVoltagePWM == 0 && mainVoltagelast > 3){
  mainVoltagePWM=2041; //Full battery
  }
  else if (mainVoltagePWM == 0 && mainVoltagelast <=3){
  mainVoltagePWM=0; //No more voltage in battery
  }
  //convert the PWM pulse length as a main Voltage value
  mainVolt=map(mainVoltagePWM, 0, 1023, 0, 50);
  }
