
/*
 * This code orginally borrowed from http://www.instructables.com/id/ESP8266-controlling-Neopixel-LEDs-using-Arduino-ID/
 * and has since been updated quite alot from its original codebase
 */

#include <Homie.h>
#include <FastLED.h>


// doing this is kinda annoying to be honest but i cant see an easier way around it
// as the fastled struct doesnt contain a brightness parameter and we need that
struct RGBB {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t br;
};


#define FW_NAME "lsc01-esp-home-mqtt-ws2812"
#define FW_VERSION "0.0.2"

#define NUM_LEDS 144
#define DATA_PIN 2

RGBB myleds[NUM_LEDS];

CRGB leds[NUM_LEDS];

void updateState();


// our led strip
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 500; 
int showType = 0;

// the "Requested" values for rgb
uint32_t rRed;
uint32_t rGreen;
uint32_t rBlue;

// the "brightness" value
uint32_t brightness = 255;

// current light state
bool LightState = true;

// number of ws2812's connected
int numPixels = NUM_LEDS;

// homie nodes for our setables
HomieNode ledNode("led", "color");
HomieNode brightnessNode("led", "brightness");
HomieNode lightSwitch("led", "switch");






String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}








int myColorWipe(uint8_t s, uint8_t e, uint8_t r, uint8_t g, uint8_t b)
{
  for(int i=s; i<e; i++) {
    myleds[i].r = r;
    myleds[i].g = g;
    myleds[i].b = b;
  }
}

int myBrightWipe(uint8_t s, uint8_t e, uint8_t br)
{
  for(int i=s; i<e; i++) {
    myleds[i].br = br;
  }
}





/*
 * Update the light state (i.e. colorWipe it) based on the
 * settings i've been told
 */
void updateState()
{
  for(int i=0; i<NUM_LEDS; i++) {
    leds[i].r = myleds[i].r;
    leds[i].g = myleds[i].g;
    leds[i].b = myleds[i].b;
    if(myleds[i].br != 255) {
      leds[i].fadeLightBy(255-myleds[i].br);
    }
  }

  FastLED.show();
}












/*
 * when we get sent a colour change message, this gets called
 * we should never really see "off" here though
 * we now expect a format of x,y,r,g.b
 * where x is the start pixel (0) y is the end pixel (numpixels)
 */
bool lightColorHandler(HomieRange range, String value)
{
  // TODO: we really should check that value is something like [0-255],[0-255],[0-255]
  uint8_t sVal, eVal;
  
  sVal = getValue(value, ',', 0).toInt();
  eVal = getValue(value, ',', 1).toInt();
  rRed = getValue(value, ',', 2).toInt();
  rGreen = getValue(value, ',', 3).toInt();
  rBlue = getValue(value, ',', 4).toInt();
  //ledNode.setProperty( "color").send(value);

  myColorWipe(sVal, eVal, rRed, rGreen, rBlue);
 
  updateState();
  
  return true;
}





/*
 * Handle the on/off signal
 * now takes x,y,state
 */


bool switchLight(HomieRange range, String value)
{
  uint8_t sVal, eVal;
  
  sVal = getValue(value, ',', 0).toInt();
  eVal = getValue(value, ',', 1).toInt();
  String sState = getValue(value, ',', 2);


  // handle a variety of "on" messaages (on/ON/true/TRUE/1)
  if(sState == "on" || value == "ON" || value == "true" || value == "TRUE" || value == "1") {
    // turn the light off
    myColorWipe(sVal, eVal, 0, 0, 0);
    myBrightWipe(sVal, eVal, 255);
  } else {
    // turn the light on - we use the last spec'd color
    myColorWipe(sVal, eVal, rRed, rGreen, rBlue);
    myBrightWipe(sVal, eVal, brightness);
  }
  
  updateState();

  // tell the mqtt server about it
  lightSwitch.setProperty("status").send(sState);

  return true;
}








/*
 * handle the brightness factor
 */
 
bool changeBrightness(HomieRange range, String value)
{

  uint8_t sVal, eVal;
  
  sVal = getValue(value, ',', 0).toInt();
  eVal = getValue(value, ',', 1).toInt();

  brightness = getValue(value, ',', 2).toInt();
  
  // bounds check
  if(brightness > 255) brightness = 255;
  if(brightness < 0) brightness = 0;

  myBrightWipe(sVal, eVal, brightness);
  
  updateState();

  // tell mqtt about it all
  brightnessNode.setProperty("brightness").send(String(brightness));
  
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

  // get homie moving
  Homie.setup();

}

/*
 * The loop codes
 */
void loop() {
  Homie.loop();
}
