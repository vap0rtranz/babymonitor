Dog Monitor
============

BabyMonitor, is a prototype of a sensor that detects when the baby is crying, and automatically alerts the parents via a phone call, and starts playing lullaby with a simple light touch to soothe the baby. 

The current version is a *working prototype*, which showcases the main ideas. The main design goal is not re-inventing Baby Monitor, but to illustrate how to build the sensor using Arduino.

## Project Layout

* [`/Docs`](Docs) contains the Arduino circuit diagram and the final prototype.
* [`/babyMonitor`](babyMonitor) contains the Arduino sketch. 
   
## Required Materials

- Arduino UNO 
- Breadboard
- Jumper Wires
- Sound Detector
- Arduino GSM Shield 
- Piezo Buzzer
- 2x LED
- 2x 560Ω Resistor
- Box or children's toy


## Connecting the components

- Attach the GSM Shield to Arduino UNO.
- Connect the Sound Detector red cable (+) in Arduino digital pin #5 and black cable (-) into ground pin.
- Connect the Piezo Buzzer red cable (+) in Arduino digital pin #8 and black cable (-) into ground pin.
- Connect the Sound Detector (+) in Arduino digital 3.5V and black cable (-) into ground pin, and Pin A0 to pin #5.
- Connect and Set the LEDs in pin #12 and #11 to light-up. 
- "Twinkle Twinkle Little Star" is the melody that have been used in this project, you can costumize your own melody by going through [this](http://www.arduino.cc/en/Tutorial/PlayMelody) tutorial.
- Put the sensor inside a box or a children's toy. 

## Circuit Diagram 

The full schematic of our completed prototype will look like the following:

![ScreenShot](/Docs/Circuit_Diagram.jpg)


## The Hardware prototype

![ScreenShot](/Docs/prototype_1.jpg)

![ScreenShot](/Docs/prototype_2.jpg)


## Demo

This video showcases a working prototype of [BabyMonitor Sensor](https://vimeo.com/128030506).


## License

MIT license.
