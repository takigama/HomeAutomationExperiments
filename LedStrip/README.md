# Led strip for ESP8266 with homie and hardware

This is a little code base and a hardware board designed to work with homie
and the WS2812 led strips. The hardware component is based on the ESP-01, that
is you print the board, put its components on, then add an ESP-01 (or s).

[OSHPark Project](https://oshpark.com/shared_projects/YzHUOvOX)

## Messages
- devices/#DEVICE_ID/switch/switch/set - changes on/off
- devices/#DEVICE_ID/switch/status - reports status here
- devices/#DEVICE_ID/brightness/brightness/set - change brightness (0-255)
- devices/#DEVICE_ID/led/color/set - changes the colour state (R,G,B)
- devices/#DEVICE_ID/led/color - colour report

## Home Assistant config
looks very roughly like this:
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

## Hardware
The kicad project is just a little daughter board for an ESP-01 that makes
it easier to control ws2182's. 5V input with a reg on board and a level
shifter for the signal line - see the bom file (html format) for the components
to get on the board.

## Attributions
Level shifter is a reproduction of sparkfun's bi-directional level shifter, as
available here: [SparkFun Logic Level Converter](https://www.sparkfun.com/products/12009)
