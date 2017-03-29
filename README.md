# Arduino-LED-night-light

An Arduino (Nano/Mini Pro) based 5V LED strip light, with capacative sensor, photoresistor and PIR.

Objectives

1. Photosensor (is it dark?) { then PIR function enabled }
2. Touchless switch for on/off (from https://github.com/arduino-libraries/CapacitiveSensor)
3. LED light function fade on/off (from https://learn.adafruit.com/rgb-led-strips/usage)
4. PIR function montion = fade on / x minutes / fade off
 
Primary function will be to turn the LED light strip on and off, with capacative touchless switch, using a PWM fade up/down.
        Then when the Photosensor sees lights go off, it enables the PIR function.
        Which, when the PIR sensor triggers, it fades up lights, then hold for 5 minutes, then fades them back down.
        And interupt the 5 minute wait and fade light down, if/when the capactive sensor is triggered.
        

The unit will be installed, just under the bed, so that the PIR only has view of the floor area, where the occupant get's in and out of bed.
That way, if you get out of bed at night, the lights will automatically light up and turn off on your return to bed. 

Issues so far:

1. The photocell reads darkness most of the time under the bed. I could recalibrate or relocate unit/senor(s).
2. The PIR sensor needs to be positioned well to only register when you get out of bed. I could try physical screening to limit its field of view.
3. Not really an issue, but it is still outputting to serial for troubelshooting and calibratiion. 

Kit list:

1. Ardunio Nano to develop this, but it will be on some Chinese Mini Pro clone, because they're dirt cheap
2. IRLB8721PBF N-channel MOSFET (this must support 3-5v gate logic)
3. LED strip - I am using a 2m 5v single colour, warm white.
4. GL5528 Photoresistor
5. DYP-ME003 Pyroelectric PIR Infrared Motion Sensor
6. 1M Ohm resistor for the capacative sensor

Possible later versions:

1. Add two more MOSFETS, an RGB LED strip and RTC, warm whites evening, reds hughes to minimise light disruption. (Or just the one extra MOSFET and a red LED strip)
2. RGB LEDS and temperature probe
3. Adding additional capacative sensors for more functions - temperature by LED colour, colour fade, brightness, mode.
4. High wattage COB LEDs (10-100W) less of a bedtime light, better suited to security light setup. 10W would be easiet as it runs off 12V (as do many 5v Arduinos) and would run with little modification. Going 20W+ and you're looking at 32v-36v'ish to run them and much safer to add optical isolatation between the Arduino and the MOSFET. 
