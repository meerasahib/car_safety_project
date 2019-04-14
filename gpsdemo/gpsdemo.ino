#include <SoftwareSerial.h>
#include<stdio.h>
#include<string.h>
#define DEBUG true


SoftwareSerial mySerial(10,11); 
        
void setup()
{
  Serial.begin(9600);
 mySerial.begin(9600); 
}

void loop()
{
   getgps();
   while(1)
   {
        sendData( "AT+CGNSINF",1000,DEBUG);   
        delay(1000);
        
   }
 
}
void getgps(void)
{
   sendData( "AT+CGNSPWR=1",1000,DEBUG); 
   sendData( "AT+CGNSSEQ=RMC",1000,DEBUG); 
}


String sendData(String command, const int timeout, boolean debug)
{
    String response = "";    
    mySerial.println(command); 
    long int time = millis();   
    while( (time+timeout) > millis())
    {
      while(mySerial.available())
      {       
        char c = mySerial.read(); 
        response+=c;
      }  
    }    
    if(debug)
    {
      Serial.print(response);
    }    
    return response;
}
