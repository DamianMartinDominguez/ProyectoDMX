/ Code for a controlling 'something' via DMX. To be more specific controlling a UV fixture (blacklight) via DMX. 
// Made by Sven Uijtendaal 

#include <DMXSerial.h>      // get the libary at:  https://github.com/mathertel/DMXSerial  by: mathertel 

// Constants for the program
const int EnablePin = 6;  
const int statusLedPin = 3;

// inputs from the dip switches
const int Input1 = 17;  //A3
const int Input2 = 16;  //A2
const int Input3 = 15;  //A1
const int Input4 = 14;  //A0
const int Input5 = 18;  //A4
const int Input6 = 13; 
const int Input7 = 12; 
const int Input8 = 11; 
const int Input9 = 10; 
const int Input10 = 9; 

// container for the dip switch value
int Dip1 = 0;
int Dip2 = 0;
int Dip3 = 0;
int Dip4 = 0;
int Dip5 = 0;
int Dip6 = 0;
int Dip7 = 0;
int Dip8 = 0;
int Dip9 = 0;
int Dip10 = 0;


int startAddress = 1;  


void setup () {
  DMXSerial.init(DMXReceiver);
  
  pinMode(EnablePin, OUTPUT);
  pinMode(statusLedPin, OUTPUT);
  
  pinMode(Input1, INPUT);
  pinMode(Input2, INPUT);
  pinMode(Input3, INPUT);
  pinMode(Input4, INPUT);
  pinMode(Input5, INPUT);
  pinMode(Input6, INPUT);
  pinMode(Input7, INPUT);
  pinMode(Input8, INPUT);
  pinMode(Input9, INPUT);
  pinMode(Input10, INPUT);


  digitalWrite(EnablePin, 0); // turn lights off
}


void loop() {
  // Calculate how long no data backet was received
  unsigned long lastPacket = DMXSerial.noDataSince();

  // translate the dip switches inputs into a number
 if (digitalRead(Input1) == HIGH) {Dip1 = 1;}
 if (digitalRead(Input1) == LOW)  {Dip1 = 0;}

 if (digitalRead(Input2) == HIGH) {Dip2 = 2;}
 if (digitalRead(Input2) == LOW)  {Dip2 = 0;}

 if (digitalRead(Input3) == HIGH) {Dip3 = 4;}
 if (digitalRead(Input3) == LOW)  {Dip3 = 0;}

 if (digitalRead(Input4) == HIGH) {Dip4 = 8;}
 if (digitalRead(Input4) == LOW)  {Dip4 = 0;}

 if (digitalRead(Input5) == HIGH) {Dip5 = 16;}
 if (digitalRead(Input5) == LOW)  {Dip5 = 0;}

 if (digitalRead(Input6) == HIGH) {Dip6 = 32;}
 if (digitalRead(Input6) == LOW)  {Dip6 = 0;}

 if (digitalRead(Input7) == HIGH) {Dip7 = 64;}
 if (digitalRead(Input7) == LOW)  {Dip7 = 0;}

 if (digitalRead(Input8) == HIGH) {Dip8 = 128;}
 if (digitalRead(Input8) == LOW)  {Dip8 = 0;}

 if (digitalRead(Input9) == HIGH) {Dip9 = 256;}
 if (digitalRead(Input9) == LOW)  {Dip9 = 0;}

 if (digitalRead(Input10) == HIGH) {Dip10 = 512;}
 if (digitalRead(Input10) == LOW)  {Dip10 = 0;}


 startAddress = Dip1 + Dip2 + Dip3 + Dip4 + Dip5 + Dip6 + Dip7 + Dip8 + Dip9 + Dip10; // set the startAddress 


   int dmxUV =  DMXSerial.read(startAddress);          // first fixture channel <---- this is where you read the incomming DMX values 
// int dmxStrobe = DMXSerial.read(startAddress + 1);   // second fixture channel; for future use; maybe I implement a strobe function or add a extra colour 

  
      if (lastPacket < 5000) {                  // it is less than 5 seconds after we received a DMX value 
    analogWrite(EnablePin, dmxUV);          
    digitalWrite(statusLedPin, HIGH);       // display a normal operation and we receive a DMX value
    }
    
      else {
    // turn LED off when there is no data received
    analogWrite(EnablePin, 0);

    // display error message; we receive no DMX value
    digitalWrite(statusLedPin, HIGH);
    delay(100);
    digitalWrite(statusLedPin, LOW);
    delay(100);
    digitalWrite(statusLedPin, HIGH);
    }
    /*  !! NOTE !!
     *  
     *  I used a delay. When using a delay, all functions will freeze, including recieving DMX values. 
     *  The 200ms delay I used here is for me not a problem; I can't operate the fixture in this state anyway. 
     *  If you use this delay during normal operation, the delay is noticable. Use the time function instead.  
     */
  

   

} // last loop

void strobe_program(){
  // future use?
} // last void
