
/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */
#include <SoftwareSerial.h>

#include <Servo.h>

SoftwareSerial sim808(10,11);


Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

int LED_Pin = 23;
int vibr_Pin =22;

int fan1=24;
 #define button_one  25           ///YES BUTTON
#define button_two  26           ///NO BUTTON
#define buzzer  27

int flag1=0;
////////
char phone_no[] = "+919080552981"; // replace with your phone no.
String data[5];
#define DEBUG true
String state,timegps,latitude,longitude;
///////
int led = 13;                // the pin that the LED is atteched to
int sensor = 9;              // the pin that the sensor is atteched to
int state1 = LOW;             // by default, no motion detected
int val = 0; 
float tempC;
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8,7, 5, 4, 3, 2);
const int timeout1=10000;

void sendTabData(String command , const int timeout , boolean debug){

sim808.println(command);
long int time = millis();
int i = 0;

while((time+timeout) > millis()){
while(sim808.available()){
char c = sim808.read();
if (c != ',') {
data[i] +=c;
delay(100);
} else {
i++;
}
if (i == 5) {
delay(100);
goto exitL;
}
}
}exitL:
if (debug) {
state = data[1];
timegps = data[2];
latitude = data[3];
longitude =data[4];
}
}


String sendData (String command , const int timeout ,boolean debug){
String response ="";
sim808.println(command);
long int time = millis();
int i = 0;

while ( (time+timeout ) > millis()){
while (sim808.available()){
char c = sim808.read();
response +=c;
}
}
if (debug) {
//Serial.print(response);
}
return response;
}
void setup() {
Serial.begin(9600);

 myservo.attach(6);  // attaches the servo on pin 9 to the servo object
 pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(buzzer, OUTPUT);
  pinMode(sensor, INPUT);    // initialize sensor as an input
  pinMode(button_one, INPUT);
 pinMode(button_two, INPUT);
 pinMode(fan1, OUTPUT); 
  pinMode(LED_Pin, OUTPUT);
  pinMode(vibr_Pin, INPUT); //set vibr_Pin input for measurment
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");

  sim808.begin(9600);
//Serial.begin(9600);
delay(50);

//sim808.print("AT+CSMP=17,167,0,0");  // set this parameter if empty SMS received
sim808.print("\r");
delay(1000);                    //Wait for a second while the modem sends an "OK"
sim808.print("AT+CMGF=1\r");    //Because we want to send the SMS in text mode
delay(1000);
//send_sms1();
/////////////////////////



////////////////////////////
sendData("AT+CGNSPWR=1",1000,DEBUG);
delay(50);
sendData("AT+CGNSSEQ=RMC",1000,DEBUG);
delay(150);
}


void loop() {
  
   tempC =  0.48828*analogRead(A0);
//   delay(100);
Serial.println(tempC);
  val = digitalRead(sensor);   // read sensor value
//  if (val == HIGH) {           // check if the sensor is HIGH
//   
//    delay(100);                // delay 100 milliseconds 
//    
//    
//      state = HIGH;       // update variable state to HIGH
//    
//  } 
//  else {
//      
//      delay(200);             // delay 200 milliseconds 
//      
//    
//        state = LOW;       // update variable state to LOW
//    
//  }


long measurement =TP_init();
  delay(50);
 // Serial.print("measurment = ");
  Serial.println(measurement);
  if (measurement > 1000){

    delay(100);
    digitalWrite(buzzer,HIGH);
    sendTabData("AT+CGNSINF",1000,DEBUG);
      if (state !=0) {
//Serial.println("State  :"+state);
//Serial.println("Time  :"+timegps);
//Serial.println("Latitude  :"+latitude);
//Serial.println("Longitude  :"+longitude);
Serial.print("http://maps.google.com/maps?q=loc:");
Serial.print(latitude);
Serial.print(",");
Serial.println(longitude);
send_sms1();
  delay(5000);
  digitalWrite(buzzer,LOW);
  
  }
  }


  if ( val==LOW)

{
  digitalWrite(fan1,LOW);

}


  

if (tempC >27  && val==HIGH)

{
digitalWrite(buzzer,HIGH);

digitalWrite(fan1,HIGH);
  flag1=0;
   lcd.clear();
  lcd.setCursor(0, 1);
     lcd.print("DO YOU NEED ANY HELP");
for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }


  
  
  long int time1 = millis();
while((time1+timeout1) > millis())

{
 if(digitalRead(button_one)==LOW)
    {
      delay(100);
     lcd.setCursor(0, 1);
     lcd.print("SENDING SMS1");
  //  Serial.print("SENDING SMS1");
  sendTabData("AT+CGNSINF",1000,DEBUG);
      if (state !=0) {
//Serial.println("State  :"+state);
//Serial.println("Time  :"+timegps);
Serial.print("http://maps.google.com/maps?q=loc:");
Serial.print(latitude);
Serial.print(",");
Serial.println(longitude);

send_sms();
} 
flag1=1;
//goto exitM
}

     
     

//////////
if(digitalRead(button_two)==LOW)
    {
      delay(100);
     lcd.clear();
   flag1=1;
     }





}

 
   
if(flag1==0)
{
    
     delay(100);
     lcd.setCursor(0, 1);
     lcd.print("SENDING SMS2");
   // Serial.println("SENDING SMS2");
      sendTabData("AT+CGNSINF",1000,DEBUG);
      if (state !=0) {
//Serial.println("State  :"+state);
//Serial.println("Time  :"+timegps);
//Serial.println("Latitude  :"+latitude);
//Serial.println("Longitude  :"+longitude);

send_sms();
}

}
delay(5000);
digitalWrite(buzzer,LOW);
} 
//break;


}

void send_sms()
{
sim808.print("AT+CMGS=\"+966500577841\"\r");

delay(400);
sim808.println("EMERGENCY!!");
sim808.print("TEMP:");
sim808.print(tempC);
sim808.println("Deg C");
sim808.print("http://maps.google.com/maps?q=loc:");
sim808.print(latitude);
sim808.print(",");
sim808.println(longitude);
delay(1000);
sim808.write(0x1A);  //Equivalent to sending Ctrl+Z 

 
}



void send_sms1()
{
sim808.print("AT+CMGS=\"+966500577841\"\r");

delay(400);
sim808.println("INTRUDER ALERT");
sim808.print("http://maps.google.com/maps?q=loc:");
sim808.print(latitude);
sim808.print(",");
sim808.println(longitude);
delay(1000);
sim808.write(0x1A);  //Equivalent to sending Ctrl+Z 

 
}


long TP_init(){
  delay(10);
  long measurement=pulseIn (vibr_Pin, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}



