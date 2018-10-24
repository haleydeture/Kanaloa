/*
 * Programmer: Daniel Truong
 * Program: Battery_Read_Arduino
 * A program for the battery Arduino that reads the voltage
 * of the battery and sends a PWM signal to the main Arduino
 */

const byte voltMainPin = A1; //Analog Input Pin
const byte AnalogPWMPin = A2; //Analog Output pin

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
readMainBatteryVoltage();
}


void readMainBatteryVoltage() {
  // Reads and smooths battery voltage by taking multiple analogReads and taking the median.
  // Note that reading is still very rough (+/-5V) even when doing this.

  float calib = 0.062;
  unsigned long total = 0;
  float voltMain;
  int voltMainRawMean = 0;
  int voltMainRawMedian = 0;
  const unsigned int nReadings = 50;
  int readings[nReadings];

  // Instantiate readings array with zeros
  for (unsigned int thisReading = 0; thisReading < nReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  // Take readings
  for (unsigned int thisReading = 0; thisReading < nReadings; thisReading++) {
    total = total - readings[thisReading];
    readings[thisReading] = analogRead(voltMainPin);
    total = total + readings[thisReading];
    delay(1);
  }

  // Sort readings
  sortArray(readings,nReadings);                // sort array to take median

  // Calculate mean and median
  voltMainRawMean = total / nReadings;          // mean (doesn't get used)
  voltMainRawMedian = readings[nReadings / 2];  // median

  // Convert to calibrated voltage
  voltMain = voltMainRawMedian * calib;         // convert voltMainRaw to voltMainRaw

  // Catching code for zero read voltage
  if (voltMain < 0.05 && voltMain > -0.05) {
//    Serial.println("CAUTION: Main battery voltage not detected!  Main battery is probably not plugged in!");
//    Serial.println("Setting voltMain = 50 for debugging purposes...");
    voltMain = 50;
  }
int analogPWMvalue = map(voltMain,0,50,0,255);
analogWrite(AnalogPWMPin, analogPWMvalue);
}

void sortArray(int a[], int size) {
  for (int i = 0; i < (size - 1); i++) {
    for (int o = 0; o < (size - (i + 1)); o++) {
      if (a[o] > a[o + 1]) {
        int t = a[o];
        a[o] = a[o + 1];
        a[o + 1] = t;
      }
    }
  }
}
