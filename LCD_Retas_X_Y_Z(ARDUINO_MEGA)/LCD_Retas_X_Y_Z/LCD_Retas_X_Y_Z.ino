
#include <UTFTGLUE.h>              //use GLUE class and constructor
UTFTGLUE myGLCD(0,A2,A1,A3,A4,A0); //all dummy args
#include<Wire.h>                   //biblioteca para o sensor

const int MPU=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int p=0, i, j, Y[310],U[310],R[310];
int SUMY=0,SUMU=0,SUMR=0;



void setup()
{
  SUMY=0;
  SUMU=0;
  SUMR=0;
  randomSeed(analogRead(0));
  //* Setup the LCD *
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont); 
  myGLCD.clrScr();
  
  //* Setup the Sensor *
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  Serial.begin(9600);

  //* Desenhar Linhas de Grade *
  myGLCD.setColor(0, 0, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.drawLine(1,119, 309,119);
  myGLCD.drawLine(1,192, 309,192);
  myGLCD.drawLine(1,51, 309,51);
  for (int i=9; i<310; i+=10)
    myGLCD.drawLine(i, 114, i, 124);
  for (int i=9; i<310; i+=10)
    myGLCD.drawLine(i, 187, i, 197);
  for (int i=9; i<310; i+=10)
    myGLCD.drawLine(i, 46, i, 56);


  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();


  //* calibrando o sensor *
  for(p=0;p<50;p++)
    {
      Y[p]=((AcX)/100);
      U[p]=((AcY)/100);
      R[p]=((-AcZ)/100); 
      //Serial.print(" | X = "); Serial.print(Y[p]); 
      //Serial.print(" | Y = "); Serial.print(U[p]); 
      //Serial.print(" | Z = "); Serial.println(R[p]);
    
      SUMY=SUMY+Y[p];
      SUMU=SUMU+U[p];
      SUMR=SUMR+R[p];
      //Serial.print(" | SUMY = ");Serial.print(SUMY);
      //Serial.print(" | SUMU = ");Serial.print(SUMU);
      //Serial.print(" | SUMR = ");Serial.println(SUMR);
    }
   
  p=0;
    
  SUMY=SUMY/50;
  SUMU=SUMU/50;
  SUMR=SUMR/50;
  
  if(SUMY!=120)
  {SUMY=(SUMY)-120;}
  else
  {SUMY=0;}
  
  if(SUMU!=193)
  {SUMU=(SUMU)-193;}
  else
  {SUMU=0;}

  
  if(SUMR!=52)
  {SUMR=(SUMR)-52;}
  else
  {SUMR=0;}

  //* desenhar titulos dos eixos *
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRect(310, 0, 319, 239);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.print("X", 312,115);

  myGLCD.setColor(0, 255, 0);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.print("Y", 312,48);
  
  myGLCD.setColor(255 ,0 , 0);
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.print("Z", 312,189);
    
}



void loop()
{ //* valores do Acelerometro *
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();
       
  //* para leitura de valores no monitor/plotter serial *
  //Serial.print("Accelerometer: ");
  
  //Serial.print("X = ");    Serial.print(((AcX)/100)-50);
  //Serial.print(" | Y = "); Serial.print(abs(AcY+25));
  //Serial.print(" | Z = "); Serial.println(abs(AcZ)); 
  //*OU*  
  //Serial.print("X = ");    Serial.print(AcX);
  //Serial.print(" | Y = "); Serial.print(AcY);
  //Serial.print(" | Z = "); Serial.println(AcZ);
  //*OU*  
  Serial.print("X = ");    Serial.print(AcX+1750);
  Serial.print(" | Y = "); Serial.print(AcY+200);
  Serial.print(" | Z = "); Serial.println(AcZ-14000);
 


  //* Vetor com Valores do Acelerometro *
  if(p<310)
  {
    Y[p]=((AcX)/100)-(SUMY);
    U[p]=((AcY)/100)-(SUMU);
    R[p]=((-AcZ)/100)-(SUMR);    
  }
  else
  {
    p=0;
    //* Limpar Grafico Anterior *
    for(j=0;j<310;j++)
    {
      myGLCD.setColor(0,0,0);
      myGLCD.drawLine( j, 120 , j, Y[j]);
      myGLCD.drawLine( j, 193 , j, U[j]);
      myGLCD.drawLine( j, 52, j, R[j]);     
    }
     //myGLCD.clrScr();  //clear screen
    Y[0]=((AcX)/100)-(SUMY);
    U[0]=((AcY)/100)-(SUMU);
    R[0]=((-AcZ)/100)-(SUMR); 
    
    //* ReDesenhar Linhas de Grade *
    myGLCD.setColor(0, 0, 255);
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.drawLine(1,119, 309,119);
    myGLCD.drawLine(1,192, 309,192);
    myGLCD.drawLine(1,51, 309,51);
    for (int i=9; i<310; i+=10)
      myGLCD.drawLine(i, 114, i, 124);
    for (int i=9; i<310; i+=10)
      myGLCD.drawLine(i, 187, i, 197);
    for (int i=9; i<310; i+=10)
      myGLCD.drawLine(i, 46, i, 56);
  }

  

    //* Desenhar Retas do Acelerometro *  
    myGLCD.setColor(255,255,255);// Acx -> branco
    myGLCD.drawLine( p, 120, p, Y[p]);   
    
    myGLCD.setColor(255,0,0);// Acy -> vermelho
    myGLCD.drawLine( p, 193, p, U[p]);    
    
    myGLCD.setColor(0,255,0);// Acz -> verde
    myGLCD.drawLine( p, 52, p, R[p]);
     

    //* proximo valor *
    p++;
    delay(10);

}
