int sensor_pin = A0;

int output_value=0;
int output_soma=0;
int output_media=0;

String outc= "";

static uint8_t mydata[] = {0,0,0,0,0,0,0,0,0,0,0};

void setup() {
   Serial.begin(9600);

}

void loop() {

    output_soma=0;
  
    output_value= analogRead(sensor_pin);
    
    output_value = map(output_value,1024,256,0,100);

    output_soma= output_value+output_soma;

    output_media=output_soma/25;
      
    outc.concat(output_value);
    outc.concat(" ");
    outc.concat(output_soma);
    outc.concat(" ");
    outc.concat(output_media);

    Serial.print("V:");
    Serial.println(output_value);
    Serial.print("S:");
    Serial.println(output_soma);
    Serial.print("M:");
    Serial.println(output_media);
    Serial.print("Conc:");
    Serial.println(outc);

  outc.toCharArray((char *)mydata, sizeof(mydata));
    
    outc = "";

    delay(10000);
    
}
