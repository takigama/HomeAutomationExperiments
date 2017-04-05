# ESP8266 based IR remote

This project is an ESP8266/homie based IR remote receiver/transmitter
The board uses a ESP12E as its base. There are several parts that can
be left off if not needed. For EG, it uses 4 transistors, one for each
of 4 IR leds, each can handle about 500ma of output at 5v, which means
all 4 together give about 2a across 4 connectors so size appropriately

The board has a connections for a TEMT6000 Light sensor as well as the
DS18B20 single wire temperature chip. All the spare GPIO's are exposed
as well as the SPI interface to be used for whatever you like. The ADC
pin of the ESP is connected to the light sensor, so if you want to use
it for a different purpose, you can connect it there.

## Homie + ESP8266

This board was designed with homie in mind and uses MQTT to comm's
with its controller. In my case, Home Assistant. As this hasnt been
written yet, i'll get back to you shortly!

## Image

![Layout](https://raw.githubusercontent.com/takigama/HomeAutomationExperiments/master/IRRemote/images/3dView.png)

## Warning!

Only just got the board back from OSHPark, but so far it works ok. I've
managed to control a device via IR after learning its IR message via
learning it using the ESP8266 IR library. Fairly happy so far. Temperature
is also working quite well

![built](https://raw.githubusercontent.com/takigama/HomeAutomationExperiments/master/IRRemote/images/build1.jpg)

## Changes

* kinda want to put in a micro usb to provide power to the board... 
difficult choice to make at the moment.
* flip the ir header? tricky choice.
* push button headers are actually slightly smallr than they should be

[Link](https://oshpark.com/shared_projects/DOv10233)
