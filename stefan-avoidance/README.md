# stefan-avoidance

## How it works

It runs a loop to detect obstacles with ultrasonic sensor. If an obstacle is present, it stops and drives backwards, then check it's sorroundings to decide which way is clear.

## Parts list

* 2WD chassis (generic)
* HC-SR04 ultrasonic sensor
* L298N engines controller
* breadboard (generic), wires
* Arduino Nano (3rd revision)

## Schematic

[Schematic can be found here](/stefan-avoidance/img/schematic.png)

## Future plans

* More power - efficient engine controller, as this one wastes 2V in heat