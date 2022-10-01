#include <Wire.h>
#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads;
float Voltage = 0.0; //ADC output
float Oxy = 0.0; //concentration
int requiredLevel = 59;
int solenoidA =4; // Ambient Air
int solenoidB =6;  // Pure Oxygen
int potentiometer = 0;//Potentiometer at pin A0

void setup() {
  // put your setup code here, to run once:
  pinMode(solenoidA, OUTPUT);
  pinMode(solenoidB, OUTPUT);
  pinMode(potentiometer, INPUT);
  ads.setGain(GAIN_SIXTEEN);
  Serial.begin(115200);
  ads.begin();
}

void loop() {
  Serial.print("User Value");
  requiredLevel=map(analogRead(potentiometer),0,1023,0,100);//read and map user value
  Serial.print(requiredLevel);
  int16_t adc0; // 16 bits ADC read of input A0
  adc0 = ads.readADC_SingleEnded(0);  //reading input Video Code
  Voltage = (float(adc0) * 0.18763835 /15.28); //converting to voltage Video Code
  Oxy = float (((Voltage-21)/.97)+21);//converting to percentage Video Code
  //Voltage = ads.computeVolts(adc0);
if(Oxy<float(requiredLevel-5)){
  digitalWrite(solenoidB, LOW);
}
else if(Oxy>float(requiredLevel+5)){
  digitalWrite(solenoidB, HIGH);
}
  Serial.print("AIN0: ");
  Serial.print(adc0);
  Serial.print("\tVoltage: ");
  Serial.println(Voltage, 2);
  Serial.println();  
delay(500);
}
