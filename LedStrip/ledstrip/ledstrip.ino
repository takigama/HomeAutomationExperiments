
/*
 * This code orginally borrowed from http://www.instructables.com/id/ESP8266-controlling-Neopixel-LEDs-using-Arduino-ID/
 * and has since been updated quite alot from its original codebase
 */

#include <Homie.h>
#include <FastLED.h>

#define FW_NAME "lsc01-esp-home-mqtt-ws2812"
#define FW_VERSION "0.0.2"

#define NUM_LEDS 60
#define DATA_PIN 2

CRGB leds[NUM_LEDS];

void updateState();


// our led strip
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 500; 
int showType = 0;

// the "Requested" values for rgb
uint32_t rRedLeft;
uint32_t rGreenLeft;
uint32_t rBlueLeft;
uint32_t rRedRight;
uint32_t rGreenRight;
uint32_t rBlueRight;

// the "brightness" value
uint32_t brightnessLeft = 255;
uint32_t brightnessRight = 255;

// current light state
bool LightStateLeft = true;
bool LightStateRight = true;

// number of ws2812's connected
int numPixels = NUM_LEDS;
int halfPixels = numPixels/2;

// homie nodes for our setables
HomieNode ledNode("led", "color");
HomieNode brightnessNode("led", "brightness");
HomieNode lightSwitch("led", "switch");

HomieNode ledNodeLeft("left", "color");
HomieNode brightnessNodeLeft("left", "brightness");
HomieNode lightSwitchLeft("left", "switch");

HomieNode ledNodeRight("right", "color");
HomieNode brightnessNodeRight("right", "brightness");
HomieNode lightSwitchRight("right", "switch");











int myColorWipeLeft(uint8_t r, uint8_t g, uint8_t b)
{

  if(brightnessLeft!=255) {
    int fb = 255-brightnessLeft;
    for(int i=0; i<halfPixels; i++) {
      leds[i].r = r;
      leds[i].g = g;
      leds[i].b = b;
      leds[i].fadeLightBy(fb);
    }
  } else {
    for(int i=0; i<halfPixels; i++) {
      leds[i].r = r;
      leds[i].g = g;
      leds[i].b = b;
    }
  }
}

int myColorWipeRight(uint8_t r, uint8_t g, uint8_t b)
{
  if(brightnessRight!=255) {
    int fb = 255-brightnessRight;
    for(int i=halfPixels; i<numPixels; i++) {
      leds[i].r = r;
      leds[i].g = g;
      leds[i].b = b;
      leds[i].fadeLightBy(fb);
    }
  } else {
    for(int i=halfPixels; i<numPixels; i++) {
      leds[i].r = r;
      leds[i].g = g;
      leds[i].b = b;
    }
  }
}






/*
 * Update the light state (i.e. colorWipe it) based on the
 * settings i've been told
 */
void updateStateLeft()
{

  // handle left

  if(LightStateLeft && brightnessLeft != 0) {
    myColorWipeLeft(rRedLeft, rGreenLeft, rBlueLeft);
  } else {
    myColorWipeLeft(0, 0, 0);
  }

  String val = String(rRedLeft) + "," + String(rGreenLeft) + "," + String(rBlueLeft);
  ledNodeLeft.setProperty( "color").send(val);
  if(LightStateLeft) {
    lightSwitchLeft.setProperty("status").send("on");
  } else {
    lightSwitchLeft.setProperty("status").send("off");
  }
  brightnessNodeLeft.setProperty("brightness").send(String(brightnessLeft));

  FastLED.show();
}

void updateStateRight()
{

  // handle left

  if(LightStateRight && brightnessRight != 0) {
    myColorWipeRight(rRedRight, rGreenRight, rBlueRight);
  } else {
    myColorWipeRight(0, 0, 0);
  }

  String val = String(rRedRight) + "," + String(rGreenRight) + "," + String(rBlueRight);
  ledNodeRight.setProperty( "color").send(val);
  if(LightStateRight) {
    lightSwitchRight.setProperty("status").send("on");
  } else {
    lightSwitchRight.setProperty("status").send("off");
  }
  brightnessNodeRight.setProperty("brightness").send(String(brightnessRight));

  FastLED.show();
}

void updateState() {
  updateStateRight();
  updateStateLeft();
}











/*
 * when we get sent a colour change message, this gets called
 * we should never really see "off" here though
 */
bool lightColorHandlerLeft(HomieRange range, String value, bool update = true)
{
  // TODO: we really should check that value is something like [0-255],[0-255],[0-255]
  rRedLeft = value.substring(0,value.indexOf(',')).toInt();
  rGreenLeft = value.substring(value.indexOf(',')+1,value.lastIndexOf(',')).toInt();
  rBlueLeft = value.substring(value.lastIndexOf(',')+1).toInt();
  //ledNodeLeft.setProperty( "color").send(value);
 
  if(update) updateState();
  
  return true;
}

bool lightColorHandlerRight(HomieRange range, String value, bool update = true)
{
  // TODO: we really should check that value is something like [0-255],[0-255],[0-255]
  rRedRight = value.substring(0,value.indexOf(',')).toInt();
  rGreenRight = value.substring(value.indexOf(',')+1,value.lastIndexOf(',')).toInt();
  rBlueRight = value.substring(value.lastIndexOf(',')+1).toInt();
  //ledNodeRight.setProperty( "color").send(value);
 
  if(update) updateState();
  
  return true;
}

bool lightColorHandlerLeftM(HomieRange range, String value)
{
  return lightColorHandlerLeft(range, value, true);

}

bool lightColorHandlerRightM(HomieRange range, String value)
{
  return lightColorHandlerRight(range, value, true);

}

bool lightColorHandler(HomieRange range, String value)
{
  // TODO: we really should check that value is something like [0-255],[0-255],[0-255]
  lightColorHandlerLeft(range, value, false);
  lightColorHandlerRight(range, value, false);
 
  updateState();
  
  return true;
}






/*
 * Handle the on/off signal
 */


bool switchLightLeft(HomieRange range, String value, bool update=true)
{

  // handle a variety of "on" messaages (on/ON/true/TRUE/1)
  if(value == "on" || value == "ON" || value == "true" || value == "TRUE" || value == "1") {
    // turn the light off
    if(brightnessLeft == 0) brightnessLeft = 128;
    LightStateLeft = true;
  } else {
    // turn the light on
    LightStateLeft = false;    
  }
  if(update) updateStateLeft();

  // tell the mqtt server about it
  lightSwitchLeft.setProperty("status").send(value);

  return true;
}

bool switchLightRight(HomieRange range, String value, bool update=true)
{

  // handle a variety of "on" messaages (on/ON/true/TRUE/1)
  if(value == "on" || value == "ON" || value == "true" || value == "TRUE" || value == "1") {
    // turn the light off
    if(brightnessRight == 0) brightnessRight = 128;
    LightStateRight = true;
  } else {
    // turn the light on
    LightStateRight = false;    
  }
  if(update) updateStateRight();

  // tell the mqtt server about it
  lightSwitchRight.setProperty("status").send(value);

  return true;
}

bool switchLightLeftM(HomieRange range, String value)
{
  return switchLightLeft(range, value, true);
}

bool switchLightRightM(HomieRange range, String value)
{
  return switchLightRight(range, value, true);
}


bool switchLight(HomieRange range, String value)
{
  switchLightLeft(range, value, false); 
  switchLightRight(range, value, false); 

  return true;
}







/*
 * handle the brightness factor
 */
 
bool changeBrightnessLeft(HomieRange range, String value, bool update=true)
{
  brightnessLeft = value.toInt();
  
  // bounds check
  if(brightnessLeft > 255) brightnessLeft = 255;
  if(brightnessLeft < 0) brightnessLeft = 0;
  
  if(update) updateStateLeft();

  // tell mqtt about it all
  brightnessNodeLeft.setProperty("brightness").send(value);
  
  return true;
}

// right
bool changeBrightnessRight(HomieRange range, String value, bool update=true)
{
  brightnessRight = value.toInt();
  
  // bounds check
  if(brightnessRight > 255) brightnessRight = 255;
  if(brightnessRight < 0) brightnessRight = 0;
  
  if(update) updateStateRight();

  // tell mqtt about it all
  brightnessNodeRight.setProperty("brightness").send(value);
  
  return true;
}

bool changeBrightnessRightM(HomieRange range, String value) {
  return changeBrightnessRight(range, value, true);
}

bool changeBrightnessLeftM(HomieRange range, String value) {
  return changeBrightnessLeft(range, value, true);
}

bool changeBrightness(HomieRange range, String value)
{
  changeBrightnessLeft(range, value, false);
  changeBrightnessRight(range, value, false);

  updateState();

  return true;
}






/*
 * The initial setup code
 */
void setup()
{

  // init the serial port - home seems to mess with this at some point
  // in a way that i cant stop
  Serial.begin(115200);
  Serial.println(FW_NAME FW_VERSION);

  // start the ws2812 code
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  Homie_setFirmware(FW_NAME, FW_VERSION);

  // register our light settings to mqtt
  ledNode.advertise("color").settable(lightColorHandler);
  lightSwitch.advertise("switch").settable(switchLight);
  brightnessNode.advertise("brightness").settable(changeBrightness);

  ledNodeLeft.advertise("color").settable(lightColorHandlerLeftM);
  lightSwitchLeft.advertise("switch").settable(switchLightLeftM);
  brightnessNodeLeft.advertise("brightness").settable(changeBrightnessLeftM);
  
  ledNodeRight.advertise("color").settable(lightColorHandlerRightM);
  lightSwitchRight.advertise("switch").settable(switchLightRightM);
  brightnessNodeRight.advertise("brightness").settable(changeBrightnessRightM);

  // get homie moving
  Homie.setup();

}

/*
 * The loop codes
 */
void loop() {
  Homie.loop();
}
