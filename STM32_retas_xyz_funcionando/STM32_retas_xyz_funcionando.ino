#include "SPI.h"               //BIBLIOTECAS PARA A TELA
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the stm32, these are the default.
#define TFT_DC PA2
#define TFT_CS PA4


#include<Wire.h>                   //biblioteca para o sensor

const int MPU=0x68; 
int16_t AcX,AcY,AcZ;
int p=0, i, j, I[310],U[310],R[310];
int SUMI=0,SUMU=0,SUMR=0;




// Use hardware SPI (on STM32, #A2, #A4) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


void setup() 
{
  
  SUMI=0;
  SUMU=0;
  SUMR=0;
 
   Serial.begin(9600);
   Wire.setClock(400000);

   //* TESTE DA BIBLIOTYECA DA TELA *
  Serial.println("ILI9341 Test!"); 
 
  tft.begin();

  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
  


  //* Desenhar Linhas de Grade *

  tft.fillScreen(ILI9341_BLACK);
  
  tft.drawFastVLine(120, 0, 320, ILI9341_BLUE);
  tft.drawFastVLine(190, 0, 320, ILI9341_BLUE);
  tft.drawFastVLine(50, 0, 320, ILI9341_BLUE);
  for (int i=9; i<310; i+=10)
    tft.drawFastHLine(115, i, 10, ILI9341_BLUE);
  for (int i=9; i<310; i+=10)
    tft.drawFastHLine(185, i, 10, ILI9341_BLUE);
  for (int i=9; i<310; i+=10)
    tft.drawFastHLine(45, i, 10, ILI9341_BLUE);


  //* Setup the Sensor *
  Wire.begin();
  delay(300);
  Wire.beginTransmission(0x68);
  Wire.write(0x6B); 
  Wire.write(0x00);    
  Wire.endTransmission();
  
  //* DEFINE OS VALORES A SEREM SELECIONADOS PELO SENSOR *
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);  
  Wire.endTransmission();
  Wire.requestFrom(0x68,6);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();



  //* calibrando o sensor *
  for(p=0;p<34;p++)
    {
      I[p]=((AcX)/100);
      U[p]=((AcY)/100);
      R[p]=((AcZ)/100); 

    
      SUMI=SUMI+I[p];
      SUMU=SUMU+U[p];
      SUMR=SUMR+R[p];
     
    }
   
  p=0;
    
  SUMI=SUMI/35;
  SUMU=SUMU/35;
  SUMR=SUMR/35;
  
  if(SUMI!=0)
  {SUMI=(SUMI);}
  else
  {SUMI=0;}
  
  if(SUMU!=0)
  {SUMU=(SUMU);}
  else
  {SUMU=0;}

  
  if(SUMR!=0)
  {SUMR=(SUMR);}
  else
  {SUMR=0;}

    
  
}


void loop()
{
  //* valores do Acelerometro *
    Wire.beginTransmission(0x68);
  Wire.write(0x3B);  
  Wire.endTransmission();
  Wire.requestFrom(0x68,6);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();
  


  //* Vetor com Valores do Acelerometro *
  if(p<310)
  {
    I[p]=((AcX)/100)-(SUMI);
    U[p]=((AcY)/100)-(SUMU);
    R[p]=((AcZ)/100)-(SUMR);    
  }
  else
  {
    p=0;
    //* Limpar Grafico Anterior *
    for(j=0;j<310;j++)
    {
      tft.drawFastHLine( 120 , j, I[j],ILI9341_BLACK);
      tft.drawFastHLine( 190 , j, U[j],ILI9341_BLACK);
      tft.drawFastHLine( 50, j, R[j],ILI9341_BLACK);
    }
     //myGLCD.clrScr();  //clear screen
    I[0]=((AcX)/100)-(SUMI);
    U[0]=((AcY)/100)-(SUMU);
    R[0]=((-AcZ)/100)-(SUMR); 
    
    //* ReDesenhar Linhas de Grade *

  tft.drawFastVLine(120, 0, 319, ILI9341_BLUE);
  tft.drawFastVLine(190, 0, 319, ILI9341_BLUE);
  tft.drawFastVLine(50, 0, 319, ILI9341_BLUE);
  for (int i=9; i<310; i+=10)
    tft.drawFastHLine(115, i, 10, ILI9341_BLUE);
  for (int i=9; i<310; i+=10)
    tft.drawFastHLine(185, i, 10, ILI9341_BLUE);
  for (int i=9; i<310; i+=10)
    tft.drawFastHLine(45, i, 10, ILI9341_BLUE);

  }


      //* Desenhar Retas do Acelerometro *  
    // Acx -> branco
    tft.drawFastHLine(120, p, I[p], ILI9341_WHITE);   
    
    // Acy -> vermelho
    tft.drawFastHLine(190, p, U[p], ILI9341_RED);    
    
    // Acz -> verde
    tft.drawFastHLine(50, p, R[p], ILI9341_GREEN);  
     

    //* proximo valor *
    p++;
    delay(10);
    

 /* tft.setTextColor(ILI9341_GREEN);  tft.setTextSize(1);
  tft.println(I[p]);
  tft.setTextColor(ILI9341_RED);
  tft.println(U[p]);
  tft.setTextColor(ILI9341_WHITE);
  tft.println(R[p]);
if(p>11){tft.fillScreen(ILI9341_BLACK);tft.setCursor(0, 0); p=0;}

delay(25);
*/
 

}
