# stefan

![Stefan photo](/stefan/img/stefan.jpeg?raw=true)

## How it works

It runs a parallel loop to detect obstacle with either of sensors. If an obstacle is present (or motion is picked up by PIR), LED turns on to display an image.

## Parts list

* 2WD chassis (generic)
* HC-SR04 ultrasonic sensor
* HC-SR501 PIR sensor
* 8x8 LED with MAX7219 controller
* breadboard (generic), wires
* Arduino UNO R3 or similar - you need 6 digital sockets

## Schematic

![Stefan schematic](/stefan/img/schematic.png)

## Future plans

* GPT-4 connectivity with microphone and speaker
* Gimbal with camera for face tracking
* Motors shield (perhaps L293D) to enable follower functionality and voice control