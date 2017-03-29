/* PIR LED night light
 * Version 0.3
 * 2017/03/28 
 * https://github.com/yaquaholic/Arduino-LED-night-light/
 * 
 * On PIR High, fade lights on for 5 minutes, then turn it off again.
 * 
 * Notes:
 * PIR works great, in fact postioning of ther sensor is key. 
 * Photocell, likewise needs to see "room" light and not be hidden in darkness
 * or it will need calibrating in situ. 
 * So either the photocell of the PIR sensor needs a longer lead, to seperate 
 * the two.
 * 
 * This verion still has outputs to serial, as I may try to recalibrate the photocell in situ.
 * Final version won't have/need this.
 * 
 * In this version:
 * Added a 1 second delay to PIRread function, so it actually waits 5 minutes instead of a few seconds. 
 * Comments cleaned up slightly
 */

#include <CapacitiveSensor.h>

//Declare everything
int calibrationTime = 60;       // 60 secs according to my datasheet
long time = 0;                  // next bits used in logic
int state = LOW;     
int x;
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


//SETUP
void setup(){
  Serial.begin(9600);
  touch.set_CS_AutocaL_Millis(2000);  // Calibrate the capacative sensor... 
  pinMode(PIRpin, INPUT);             // PIR input pin setup
  pinMode(pwm, OUTPUT);               // PWM pin for MOSFET signal pin
  analogWrite(pwm, 0);                // LED(s) off
  calibrate();                        // PIR calibrate wait

  }


//LOOP
void loop(){
  reading = analogRead(photocell); 
  if (reading < 100) {                // photocell threshold
    Serial.print("Photocell: ");
    Serial.println(reading);
    Serial.println("Oooh it's dark");
    PIRread();                        // dark enough to start the PIR function
    }
  CSread();                           // then check capacative sensor
}       

void PIRread() 
{
  if(digitalRead(PIRpin) == HIGH)
       {
         Serial.println("PIR goes high");
         Sunrise();                                         //LED on
         for (x =0; x < 300; x ++)
         {    
             Serial.print(300-x/60);
             Serial.println(" minutes of light");
             long total1 =  touch.capacitiveSensor(30);     //Sensor resolution
             if (total1 > 750){break;}                      //Threshold
             delay(1000);                                   //1 second delay
             
         }
         Serial.println("Hopefully back from the bathroom by now...");
         Sunset();                                          //LED off
       }         
}

void CSread () 
{
    long total1 =  touch.capacitiveSensor(30);              //Sensor resolution
    
    if (total1 > 750){result = true;}                       //Touch threshold 750
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
                       Serial.println("LEDs on");
                       Sunrise();
                       previous = result;
                      }
    else              {
                       Serial.println("LEDs off");
                       Sunset();
                       previous = result;
                      }
      delay(500);                            //500 ms delay
}

void Sunrise() 
{
  while(brightness < 256)
   {
    Serial.print("Sunrise");
    Serial.println(brightness);
    pinMode(pwm, OUTPUT);                    // declare pwm pin to be an output
    analogWrite(pwm, brightness);            // set the brightness of LEDs
    brightness = brightness + fadeAmount;    // adjust brightness for next time through the loop
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
     pinMode(pwm, OUTPUT);                    // declare pwm pin to be an output
     analogWrite(pwm, darkness);              // set the brightness of LEDs
     darkness = darkness - fadeAmount;        // adjust darkness for next time through the loop
     delay(50);                               // wait time (ms)
    }
   analogWrite(pwm, 0); 
   brightness = 0;
}

void calibrate ()
{
    for(int i = 0; i < calibrationTime/10; i++)  // remove div by 10 and reduce delay to 1000
              {
                Serial.println("Calibrating...");
                delay(10000);                     // wait 10 seconds
              }
    delay(50);
}
