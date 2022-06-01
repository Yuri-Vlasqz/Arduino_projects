//Viral Science  www.youtube.com/c/viralscience
//Alcohol Detector
/*Detecting concentration
scope：
 0.05mg/L—10mg/L
 Alcohol
*/
const int MQ3=0;
const int Buzzer=8;
const int LED=9;
double value;

void setup() {
  Serial.begin(9600);
  pinMode(MQ3, INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(Buzzer,LOW);
  digitalWrite(LED,LOW);

}

void loop()
{
  value= analogRead(MQ3);
  value=value/100;
  Serial.print(value);
  Serial.println(" mg/L");
  /*
  if(value>440)
  {
    digitalWrite(Buzzer,HIGH);
    digitalWrite(LED,HIGH);
  }else{
    digitalWrite(Buzzer,LOW);
    digitalWrite(LED,LOW);
  }
  */
  delay (500);
}
