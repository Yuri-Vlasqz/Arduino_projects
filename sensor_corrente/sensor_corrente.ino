#include "EmonLib.h" //INCLUSÃO DE BIBLIOTECA
double soma=0, media;
int p=0;
 
#define CURRENT_CAL 18.40 //VALOR DE CALIBRAÇÃO (DEVE SER AJUSTADO EM PARALELO COM UM MULTÍMETRO MEDINDO A CORRENTE DA CARGA)
const int pinoSensor = A1; //PINO ANALÓGICO EM QUE O SENSOR ESTÁ CONECTADO
 
EnergyMonitor emon1; //CRIA UMA INSTÂNCIA
 
void setup(){  
  Serial.begin(9600); //INICIALIZA A SERIAL
  emon1.current(pinoSensor, CURRENT_CAL); //PASSA PARA A FUNÇÃO OS PARÂMETROS (PINO ANALÓGIO / VALOR DE CALIBRAÇÃO)

  for(p=0;p<30;p++)
  {
    emon1.calcVI(20,100); //FUNÇÃO DE CÁLCULO (20 SEMICICLOS / TEMPO LIMITE PARA FAZER A MEDIÇÃO)
    double currentDraw = emon1.Irms; //VARIÁVEL RECEBE O VALOR DE CORRENTE RMS OBTIDO}
    soma=currentDraw+soma;
  }
  
  media=soma/30;
  soma=0;
}
 
void loop(){
  emon1.calcVI(20,100); //FUNÇÃO DE CÁLCULO (20 SEMICICLOS / TEMPO LIMITE PARA FAZER A MEDIÇÃO)
  double currentDraw = emon1.Irms; //VARIÁVEL RECEBE O VALOR DE CORRENTE RMS OBTIDO
  
  if (currentDraw-media>0.1)
  {
    Serial.print("Corrente medida: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(currentDraw); //IMPRIME NA SERIAL O VALOR DE CORRENTE MEDIDA
    Serial.println("A"); //IMPRIME O TEXTO NA SERIAL
  for(p=0;p<30;p++)
  {
    emon1.calcVI(20,100); //FUNÇÃO DE CÁLCULO (20 SEMICICLOS / TEMPO LIMITE PARA FAZER A MEDIÇÃO)
    double currentDraw = emon1.Irms; //VARIÁVEL RECEBE O VALOR DE CORRENTE RMS OBTIDO}
    soma=currentDraw+soma;
  }
  
  media=soma/30;
  soma=0;
  }
    
  
}
