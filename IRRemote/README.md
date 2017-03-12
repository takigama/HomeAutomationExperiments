# ESP8266 based IR remote

This project is an ESP8266/homie based IR remote receiver/transmitter
The board uses a ESP12E as its base. There are several parts that can
be left off if not needed. For EG, it uses 4 transistors, one for each
of 4 IR leds, each can handle about 500ma of output at 5v, which means
all 4 together give about 2a across 4 connectors so size appropriately

The board also has a USB uart chip in the form of a FT230XS FTDI chip
which isn't necessary if you already have a USB uart device. Theres
also support for a temperature (DS18B20) single wire interface chip
and a TEMT6000 ambient light sensor connected to the ADC of the ESP
chip. If unneeded, they can be replaced or not connected at all

## Homie + ESP8266

This board was designed with homie in mind and uses MQTT to comm's
with its controller. In my case, Home Assistant. As this hasnt been
written yet, i'll get back to you shortly!

## Image

![Layout](https://raw.githubusercontent.com/takigama/HomeAutomationExperiments/master/IRRemote/3dView.png);

## Warning!

I've not even built this board yet, so here be dragons! yarrr, but
here be the board on OSH Park:

[Link](https://oshpark.com/shared_projects/6rSS0T7z)
