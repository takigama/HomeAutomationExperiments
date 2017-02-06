# Led strip for ESP8266 with homie and hardware

This is a little code base and a hardware board designed to work with homie
and the WS2812 led strips. The hardware component is based on the ESP-01, that
is you print the board, put its components on, then add an ESP-01 (or s).

* [OSHPark Project](https://oshpark.com/shared_projects/YzHUOvOX)
* [Small Demo Video](https://www.youtube.com/watch?v=C1is4zkPhkE)
* [Pointer and Fire Modes](https://www.youtube.com/watch?v=obZJblPsRek)

Technically, the board could be used to drive anything if all you need is 5v
input, 1x5v GPIO and 3 x 3.3v GPIO (TX/RX can be used for multiple things, 
including I2C or just straight GPIO). Note though that GPIO2 drives the 5v
output and care must be taken because pulling GPIO2 low on boot, causes it to
boot in a different mode!

## The Board:
![Board](https://raw.githubusercontent.com/takigama/HomeAutomationExperiments/master/LedStrip/images/esp-01-ledstripcontroller-02.jpg)
![Board2](https://raw.githubusercontent.com/takigama/HomeAutomationExperiments/master/LedStrip/images/esp-01-ledstripcontroller-04.jpg)

## Messages
- devices/#DEVICE_ID/switch/switch/set - changes on/off
- devices/#DEVICE_ID/switch/status - reports status here
- devices/#DEVICE_ID/brightness/brightness/set - change brightness (0-255)
- devices/#DEVICE_ID/color/color/set - changes the colour state (R,G,B)
- devices/#DEVICE_ID/color/color - colour report

Can be used with ranges, i.e. sending 0,20,on to switch will only turn on
leds 0 to 20 - isnt required

## Home Assistant config
looks very roughly like this (its a moving target):
```
light:
  - platform: mqtt
    name: "esplight"
    command_topic: "devices/dev1/switch/switch/set"
    rgb_command_topic: "devices/dev1/led/color/set"
    rgb_value_template: "value.rgb|join(',')"
    brightness_state_topic: "devices/dev1/brightness/brightness/set"
    brightness_command_topic: "devices/dev1/brightness/brightness/set"
    qos: 0
    payload_on: "on"
    payload_off: "off"
    optimistic: false
    state_topic: "devices/dev1/switch/status"

```


## work in progres
Note, i just started this in late october - its very much a work in progress!

## TODO's

### DONE
1. Moved to fastled lib (not really liking it much) - DONE
2. change messages to allow for sub-ranges - DONE
3. add some fixed effects (fire, pointer, tv)

### Not Done
4. make number of leds dynamic (and saved in eeprom) - trickier than i'd hoped





## Hardware
The kicad project is just a little daughter board for an ESP-01 that makes
it easier to control ws2812's. 5V input with a reg on board and a level
shifter for the signal line - see the bom file (html format) for the components
to get on the board. Its much easier to make than it looks, dont let SMD
scare you!

## Hookup

![Hookup's](https://raw.githubusercontent.com/takigama/HomeAutomationExperiments/master/LedStrip/images/board.png)

## Attributions
Level shifter is a reproduction of sparkfun's bi-directional level shifter, as
available here:

[SparkFun Logic Level Converter](https://www.sparkfun.com/products/12009)
