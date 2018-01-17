Dog Monitor
============

Dog Monitor is a prototype sensor that detects when the dog barks, and notifies the owner via SMS text message.  It also notifies on temperature and CO (carbon monoxide). 

This monitor was based on Tahar's Baby Monitor prototype (tzano on Github)

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
- 2x 560Ω Resistor
- Arduino case / Box 

## Connecting the components

- Attach the GSM Shield to Arduino UNO.
- Connect the Sound Detector red cable (+) in Arduino digital pin #5 and black cable (-) into ground pin.
- Connect the Sound Detector (+) in Arduino digital 3.5V and black cable (-) into ground pin, and Pin A0 to pin #5.
- Put the sensor inside a box.

## Circuit Diagram 

The full schematic of our completed prototype will look like the following:

![ScreenShot](/Docs/Circuit_Diagram.jpg)


## The Hardware prototype

![ScreenShot](/Docs/prototype_1.jpg)

![ScreenShot](/Docs/prototype_2.jpg)


## Demo

## License

MIT license.
