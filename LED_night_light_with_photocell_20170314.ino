/* PIR LED night light
 * Version 0.1
 * 2017/02/02 Richard Graham
 * On PIR High, fade lights on for 5 minutes, then turn it off again.
 *  Okay it loads, and runs to a fashion, but no quite right,
 *  Now instrumented with serial outputs, to check the thresholds.
 *  When next I am here, i will sort it out.
 */

#include <CapacitiveSensor.h>

//Declare everything
int calibrationTime = 60;       // 60 secs according to the datasheet
long time = 0;                  // used in capactive logic
int state = LOW;     
int PIRpin = 7;                 // Digital pin 7 connected to the PIR sensor's output   
int pwm = 9;                    // Digital 9 connected the LED (or MOSFET)  
int brightness = 0;             // Start dark (0-255 scale)
int darkness = 255;             // Start bright 
int fadeAmount = 2;             // How many points to fade the LED by
int debounce = 200;             // debounce factor
long start = millis();          // sketch run time
boolean result;                 // true or false
boolean previous = false;       // defintiely false
int photocell = 0;              // Photocell on A0 
int reading;                    // Photocall reading value goes here

// 1M Ohm resistor between pins 4 & 2, with pin 2 is sensor pin
CapacitiveSensor   touch = CapacitiveSensor(4,2);   


/////////////////////////////
//SETUP
void setup(){
  Serial.begin(9600);
  touch.set_CS_AutocaL_Millis(2000);  //Calibrate the capacative sensor... 
  pinMode(PIRpin, INPUT);             // 
  pinMode(pwm, OUTPUT);
  analogWrite(pwm, 0);                //LED(s) off
  calibrate(); 

  }

////////////////////////////
//LOOP
void loop(){
  reading = analogRead(photocell); 
  if (reading < 100) {
    Serial.print("Photocell: ");
    Serial.println(reading);
    Serial.println("Oooh it's dark");
    PIRread(); 
    }
  CSread();
}       

void PIRread() 
{
  if(digitalRead(PIRpin) == HIGH)
       {
         Serial.println("PIR goes high");
         Sunrise();       //LED on
         Serial.println("5 minutes of light");     
         delay(60000);   //Wait 1 minute (in ms)
         Serial.println("4 minutes of light");     
         delay(60000);   
         Serial.println("3 minutes of light");     
         delay(60000);   
         Serial.println("2 minutes of light");     
         delay(60000);  
         Serial.println("1 minute of light");     
         delay(60000); 
         Serial.println("Hopefully back from the bathroom by now...");
         Sunset();        //LED off
       }         
}

void CSread () 
{
    long total1 =  touch.capacitiveSensor(30);     //a: Sensor resolution
    
    if (total1 > 750){result = true;}              //b: Threshold
    else {result = false;}    
    
    // to toggle the state of state
    if(result == true && previous  == false && millis() - time>debounce){
      
       if(state == LOW){ state = HIGH;}
       else {
             state = LOW;
             time = millis();     
            }
    }
    if(state == HIGH) { 
                       Serial.println("State == HIGH");
                       Sunrise();
                       previous = result;
                      }
    else              {
                       Serial.println("State == LOW");
                       Sunset();
                       previous = result;
                      }
      delay(500);
}

void Sunrise() 
{
  while(brightness < 256)
   {
    Serial.print("Sunrise");
    Serial.println(brightness);
    pinMode(pwm, OUTPUT);                    // declare pwm pin to be an output:
    analogWrite(pwm, brightness);            // set the brightness of LEDs:
    brightness = brightness + fadeAmount;    //change the brightness for next time through the loop:
    delay(50);                               // wait time (ms) 
   }
   darkness = 255;
}

void Sunset() 
{
   while(darkness > 0)
    {
     Serial.print("Sunset");
     Serial.println(darkness);
     pinMode(pwm, OUTPUT);                    // declare pwm pin to be an output:
     analogWrite(pwm, darkness);              // set the brightness of LEDs:
     darkness = darkness - fadeAmount;        //change the brightness for next time through the loop:
     delay(50);                               // wait time (ms)
    }
   analogWrite(pwm, 0); 
   brightness = 0;
}

void calibrate ()
{
    for(int i = 0; i < calibrationTime/10; i++)
              {
                Serial.println("Calibrating...");
                delay(1000);                     // wait 10 seconds
              }
    delay(50);
}
