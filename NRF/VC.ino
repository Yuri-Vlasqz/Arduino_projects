


#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include<Wire.h>                   //biblioteca para o sensor

const int MPU=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int p=0, i, j, F[310],U[310],R[310],k=0,r=0,l;
int SUMY=0,SUMU=0,SUMR=0;

//
// Hardware configuration
//

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 

RF24 radio(7,8);

//
// Topology
//

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

//
// Role management
//
// Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.  
//

// The various roles supported by this sketch
typedef enum { role_ping_out = 1, role_pong_back } role_e;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

// The role of the current running sketch
role_e role = role_pong_back;

void setup(void)
{

  for(p=0;p<310;p++){F[p]=100;}
  p=0;
  
  //
  // Print preamble
  //

  Serial.begin(9600);
  printf_begin();
  printf("\n\rRF24/examples/GettingStarted/\n\r");
  printf("ROLE: %s\n\r",role_friendly_name[role]);
  printf("*** PRESS 'T' to begin transmitting to the other node\n\r");

  //
  // Setup and configure rf radio
  //

  radio.begin();
  //radio.setPALevel(RF24_PA_LOW);
  radio.setAutoAck(false);

  // optionally, increase the delay between retries & # of retries
  radio.setRetries(15,15);

  // optionally, reduce the payload size.  seems to
  // improve reliability
  //tradio.setPayloadSize(8);

  //
  // Open pipes to other nodes for communication
  //

  // This simple sketch opens two pipes for these two nodes to communicate
  // back and forth.
  // Open 'our' pipe for writing
  // Open the 'other' pipe for reading, in position #1 (we can have up to 5 pipes open for reading)

  if ( role == role_ping_out )
  {
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
  }
  else
  {
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);
  }

  //
  // Start listening
  //

  radio.startListening();

  //
  // Dump the configuration of the rf unit for debugging
  //

  radio.printDetails();
  delay(2000);
/*
//SENSOR!!!!!!

 SUMY=0;
  SUMU=0;
  SUMR=0;
  randomSeed(analogRead(0));

  
  //* Setup the Sensor *
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  Serial.begin(9600);



  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX=Wire.read()<<8|Wire.read();    
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();


  //* calibrando o sensor *
  for(p=0;p<34;p++)
    {
      F[p]=((AcX)/100);
      U[p]=((AcY)/100);
      R[p]=((-AcZ)/100); 
      //Serial.print(" | X = "); Serial.print(Y[p]); 
      //Serial.print(" | Y = "); Serial.print(U[p]); 
      //Serial.print(" | Z = "); Serial.println(R[p]);
    
      SUMY=SUMY+F[p];
      SUMU=SUMU+U[p];
      SUMR=SUMR+R[p];
      //Serial.print(" | SUMY = ");Serial.print(SUMY);
      //Serial.print(" | SUMU = ");Serial.print(SUMU);
      //Serial.print(" | SUMR = ");Serial.println(SUMR);
    }
   
  p=0;
    
  SUMY=SUMY/35;
  SUMU=SUMU/35;
  SUMR=SUMR/35;
  
  if(SUMY!=0)
  {SUMY=(SUMY);}
  else
  {SUMY=0;}
  
  if(SUMU!=0)
 {SUMU=(SUMU);}
  else
 {SUMU=0;}
  

  
  if(SUMR!=0)
 {SUMR=(SUMR);}
  else
 {SUMR=0;}
  */
}

void loop(void)
{
  p++;
  /*
  //SENSOR!!!

  //* valores do Acelerometro *
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
  //Serial.print("X = ");    Serial.print(AcX+1750);
  //Serial.print(" | Y = "); Serial.print(AcY+200);
  //Serial.print(" | Z = "); Serial.println(AcZ-14000);
 


  //* Vetor com Valores do Acelerometro *
  if(p<310)
  {
    F[p]=((AcX)/100)-(SUMY);
    U[p]=((AcY)/100)-(SUMU);
    R[p]=((-AcZ)/100)-(SUMR);    
  }
  else
  {
    p=0;
   }
     //myGLCD.clrScr();  //clear screen
    F[0]=((AcX)/100)-(SUMY);
    U[0]=((AcY)/100)-(SUMU);
    R[0]=((-AcZ)/100)-(SUMR); 

  Serial.print("X = ");    Serial.print(F[p]);
  Serial.print(" | Y = "); Serial.print(U[p]);
  Serial.print(" | Z = "); Serial.println(R[p]);
 // printf("X = ...\n\r");printf("F[p]\n\r",F[p]);
 // printf("Y = ...\n\r");printf("U[p]\n\r",U[p]);
 // printf("Z = ...\n\r");printf("R[p]\n\r",R[p]);


    //* proximo valor *
    p++;
*/


  
  //
  // Ping out role.  Repeatedly send the current time
  //

  if (role == role_ping_out)
  {
    // First, stop listening so we can talk.
    radio.stopListening();

    // Take the time, and send it.  This will block until complete
    unsigned long time = millis();
    printf("Now sending %lu...",time);
    bool ok = radio.write( &time, sizeof(unsigned long) );

   // const char text[] = "Hello World";
   // radio.write(&text, sizeof(text));
  //  Serial.print(text);
   // Serial.print( ", ");
   // Serial.println( sizeof(text));
    
    if (ok)
      printf("ok...");
    else
      printf("failed.\n\r");

    // Now, continue listening
    radio.startListening();

    // Wait here until we get a response, or timeout (250ms)
    unsigned long started_waiting_at = millis();
    bool timeout = false;
    while ( ! radio.available() && ! timeout )
      if (millis() - started_waiting_at > 200 )
        timeout = true;

    // Describe the results
    if ( timeout )
    {
      printf("Failed, response timed out.\n\r");
   //   Serial.println("//");
    }
    else
    {
      // Grab the response, compare, and send to debugging spew
    //  unsigned long got_time;
    //  radio.read( &got_time, sizeof(unsigned long) );



      // Spew it
     // printf("Got response %lu, round-trip delay: %lu\n\r",got_time,millis()-got_time);
     // Serial.println("//");
    }

      
    // Try again 1s later
    delay(2000);
  }

  //
  // Pong back role.  Receive each packet, dump it out, and send it back
  //

 if ( role == role_pong_back )
  {
    // if there is data ready
    if ( radio.available() )
    {
      // Dump the payloads until we've gotten everything
      //unsigned long got_time;
      bool done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
       // done = radio.read( &got_time, sizeof(unsigned long) );
        
        done = radio.read( &F[p],500 );

       // printf("F: %d...\n\r",F[p]);

        

        if(F[p]!=0&&F[p]!=100){R[k]=F[p];k++;}
              
        
            printf("Acele %d\n\r",R[k-1]);           

       

         if(k==300)
        {                
          for(k=1;k<300;k++)
          {
            printf("Acele plot: %d\n\r",R[k]);
          }
          printf("Foi?\n\r");
          k=0;        
        }
        
      
        
      //char text[32] = "N rolou";
     // radio.read(&text, sizeof(text));
     // Serial.println(text);

     /*
      if(p==300){
        // Spew it

      for(k=0;k<310;k++){
      //  printf("Got payload %lu...",got_time);
        if(F[k]!=100&&F[k]!=0){
        printf("Acele %d...",F[k]);
        printf("Foi?.\n\r");
        }
      }
      p=0;
      }
   */

        
    
    
      }


  // Delay just a little bit to let the other unit
  // make the transition to receiver(min delay==2000)
  delay(2000);
      }
  

      // First, stop listening so we can talk
     // radio.stopListening();

      // Send the final one back.
     // radio.write( &got_time, sizeof(unsigned long) );
    //  printf("Sent response.\n\r");
    //  Serial.println("//");

      // Now, resume listening so we catch the next packets.
     // radio.startListening();
    }
  

  //
  // Change roles
  //

  if ( Serial.available() )
  {
    char c = toupper(Serial.read());
    if ( c == 'T' && role == role_pong_back )
    {
      printf("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK\n\r");

      // Become the primary transmitter (ping out)
      role = role_ping_out;
      radio.openWritingPipe(pipes[0]);
      radio.openReadingPipe(1,pipes[1]);
    }
    else if ( c == 'R' && role == role_ping_out )
    {
      printf("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK\n\r");
      
      // Become the primary receiver (pong back)
      role = role_pong_back;
      radio.openWritingPipe(pipes[1]);
      radio.openReadingPipe(1,pipes[0]);
    }
  }
  if(p>300){p=0;}
}
// vim:cin:ai:sts=2 sw=2 ft=cpp
