# The Tasmota Micro board

![Front On](https://raw.githubusercontent.com/takigama/HomeAutomationExperiments/master/Tasmota-Micro/Hardware/images/20181015_023856_ws.jpg)
![Side On](https://raw.githubusercontent.com/takigama/HomeAutomationExperiments/master/Tasmota-Micro/Hardware/images/20181015_024028_ws.jpg)

The tasmota micro (hope they dont mine me calling it that) is based off my
ledstrip controller with alot more flexibility build it. Its quite straight
forward but i'll make an image shortly of where the components go on the
board.

In short, the BOM is:

1. 2 x IRLML6244 (if needed - provides switching output for higher current
   loads) - Q1 and Q2
2. 2 x 2.2uf (or higher), one rated for 3.6v min and the othr rated at
   whatever input voltage you use. C3 - 3.3v, C1 Input voltage
3. 1 x diode (for stopping reverse polarity on the input) - D1
4. MCP1703-3.3 (3.3v regulator rated at 250ma - just enough for this) U1
5. 2 x resistors (you must size these yourself - but notes are provided) R1/2
6. 1 x 20k resistor - R3
7. 1 x MC32603 USB connector (only needed if you wish to poer the thing
   in the way i've show in my pictures, it can be just wired in.
8. Optionally a 2x4 header strip.
9. And of course, you will want an ESP-01S (with the larger flash, though I
   believe it can work ith the smaller 512k flash if you cut the firmware
   down a bit).

All resistors and caps are 0805 size. Diode is SMA.

## Putting it together

Personally, my first one was a hand solder job with a nothing-special type
of soldering iron and I found this to be quite easy (though I used a handheld
magnifying glass to get the components lined up). I put the first one together
with these tools just to make sure it could be done easily enough.

Generally I would normally use solder paste and a heatgun for the SMD
components, then hand solder in the connectors. Also note, in the images, i've
put JST connectors on there, this is just a serving suggestion, its not a
requirement and I wouldn't recommend it.

Also note, for the ESP module in the images, i've put on a 4x2 header so I
can easily remove the ESP-01 module - this isnt a requirement as it makes
the module quite a bit shorter if you choose not to do this. The ESP can still
be flashed if needed while soldered to the board, but you'll need some small
clips to do it.

## Connectors

![Connectors](https://raw.githubusercontent.com/takigama/HomeAutomationExperiments/master/Tasmota-Micro/Hardware/images/layout.png)

### P2

Proves both raw input voltage or raw output voltage - i.e. you can push
power into the unit via one of these pins or provide power at the input
voltage as output (i.e. if your driving from USB these pins are 5v). Maximum
input voltate is 16v according to the MCP1703 tech specs, but I wouldn't
have a need to go beyond 12v myself.

### P3

These are the mosfet switched versions of GPIO2 and the RX line. They also
include current limiting resistors, R1 and R2 - you must size these
appropriaely for your project (or just bridge them and put resistors on
your actual device). Note, these pull to ground!

### P4

This header provides all 4 GPIO's as direct connections on the ESP at the
level of the ESP itself (3.3v), be aware though that depending on the state
of the ESP itself (which can draw about 170ma max - apparently), you can only
draw a maxmimum of about 80ma!.

### P5 

Output from the MCP1703 regulator is provided on these pins. This would
typically be 3.3v but if you've put in your own changes, what comes out
there is up to you, i.e. configure that in the tasmota gui.

### P6

Ground pins

## GPIO's

The device provides 4 GPIO's as well as two that can be switched via
mosfets.

So far i've tested the following components:

1. HC-SR505 movement sensor
2. BME280 - Temp/Pressure/Humidity
3. BMP180 - Temp/Pressure
4. BH1750 - Ambient light
5. CHQ1838 - IR Recv (runs at 3.3v, work well)
6. DS18B20 - Dallas Temp Sensor
7. TSAL6100 - IR Emitter (47ohm resistor on mosfet switch).
8. WS2812 - Addressable led strip.

So far they all work well - keen to try some more if and when i can think of
something.

## Current Limiting Resistors

On the "high current" switches (which are RX and GPIO2 on P3) you must either
provide some current limiting resistors or bridge the resistor tracks and put
the resistors on your device (assuming you need them at all). This also means
they must be sized to suit your needs (if putting them on the board). As an
example, I have one with a 47ohm resistor (to drive the TSAL6000 IR emitter)
and one with a 150ohm resistor (cause why not?).

Also not the mosfet i've put in the bom on this are rated for 6a, however I
wouldn't push my luck with it as the tracks can probably only withstand about
2A depending on the thickness of the solder traces and where you get them made.
Personally, I use OSH Park (note the connector the USB is designed with
circular holes for the USB mount ends - this is because OSH Park dont do oval
drill holes).

## More to come

As I get the opportunity i'll test some other devices to hang off it and will
definitely be continuing to update the board as time permits.

## Thanks...

Thanks to the tasmota guys for making the awesome firmware!
