# Arduino-LED-night-light

An Arduino (Nano/Mini Pro) based 5V LED strip light, with capacative sensor, photoresistor and PIR.

Objectives

1. Photosensor (is it dark?) { then PIR function enabled }
2. Touchless switch for on/off (from https://github.com/arduino-libraries/CapacitiveSensor)
3. LED light function fade on/off (from https://learn.adafruit.com/rgb-led-strips/usage)
4. PIR function montion = fade on / x minutes / fade off
5. 1M Ohm resistor for the capacative sensor
 
Primary function will be to turn the LED light strip on and off, with capacative touchless switch, using a PWM fade up/down.
When Photosensor sees lights go off, it enables the PIR.
        When PIR triggers, fade up lights, then hold for X minutes, fade down.
        Interupt and fade light down if switch triggered.
        

The unit will be installed, just under the bed, so that the PIR only has view of the floor area, where the occupant get's in and out of bed.
That way, if you get out of bed at night, the lights will automatically light up and turn off on your return to bed. 

Kit list:

1. Ardunio Nano (dev board) - Mini Pro for production.
2. IRLB8721PBF N-channel MOSFET (which supports 3 to 5v gate logic)
3. LED strip - 2m 5v single colour (warm white)
4. GL5528 Photoresistor
5. DYP-ME003 Pyroelectric PIR Infrared Motion Sensor

