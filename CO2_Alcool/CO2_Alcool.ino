
//Alcohol Detector
/*Detecting concentration
scope：
 0.05mg/L—10mg/L
 Alcohol
*/
const int MQ3=0;
double value;

/* Testing MQ-2 GAS sensor with serial monitor
   Suitable for detecting of LPG, i-butane, propane, methane ,alcohol, Hydrogen or smoke
   More info: http://www.ardumotive.com/how-to-use-mq2-gas-sensor-en.html
   Dev: Michalis Vasilakis // Date: 11/6/2015 // www.ardumotive.com                     */
   
const int gasPin = A2; //GAS sensor output pin to Arduino analog A0 pin

void setup() 
{
  Serial.begin(9600);//Initialize serial port - 9600 bps
  pinMode(MQ3, INPUT);
}

void loop()
{
  value= analogRead(MQ3);
  value=value/100;
  Serial.print(value);
  Serial.println(" mg/L");


  Serial.print("Co2:");
  Serial.println(analogRead(gasPin));

  Serial.println(" ");
  

  
  delay(500); // Print value every 1 sec.  
}
