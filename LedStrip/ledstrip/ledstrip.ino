/*
 * This code orginally borrowed from http://www.instructables.com/id/ESP8266-controlling-Neopixel-LEDs-using-Arduino-ID/
 * and has since been updated quite alot from its original codebase
 */

#include <Homie.h>
#include <Adafruit_NeoPixel.h>

#define FW_NAME "esp-home-mqtt-ws2812"
#define FW_VERSION "0.0.1"

#define PIN            2
#define LED_COUNT      20


void updateState();


// our led strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 500; 
int showType = 0;

// the "Requested" values for rgb
uint32_t rRed;
uint32_t rGreen;
uint32_t rBlue;

// the "brightness" value
uint32_t brightness = 255;

// the "total" value (i.e. RGB + brightness)
uint32_t tRed = 255;
uint32_t tGreen = 255;
uint32_t tBlue = 255;

// current light state
bool LightState = true;

// number of ws2812's connected
int numPixels = LED_COUNT;

// homie nodes for our setables
HomieNode ledNode("led", "led");
HomieNode brightnessNode("brightness", "brightness");
HomieNode lightSwitch("switch", "switch");











// a generic colorwipe function as per the
// adafruid examples
void colorWipe(uint32_t c, uint8_t wait)
{
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.setBrightness(brightness);
    strip.show();
    delay(wait);
  }
}











/*
 * when we get sent a colour change message, this gets called
 * we should never really see "off" here though
 */
bool lightOnHandler(HomieRange range, String value)
{
  if (value == "off") {
    // first make sure the brightness is above about 50, then turn it off
    // we do that so in case someone has turned the brightness to 0 somehow
    // and is trying to fix the light colour
    if(brightness < 50) brightness = 50;
    LightState = false;
    ledNode.setProperty( "color").send("0,0,0");
  } else if (value == "red") {
    rRed = 255;
    rGreen = 0;
    rBlue = 0;
    ledNode.setProperty( "color").send("255,0,0");
  } else if (value == "green") {
    rRed = 0;
    rGreen = 255;
    rBlue = 0;
    ledNode.setProperty( "color").send("0,255,0");
  } else if (value == "blue") {
    rRed = 0;
    rGreen = 0;
    rBlue = 255;
    ledNode.setProperty( "color").send("0,0,255");
  } else {
      //value.trim();
      Serial.print (value);
      //Serial.flush();
      // split string at every "," and store in proper variable
      // convert final result to integer
      rRed = value.substring(0,value.indexOf(',')).toInt();
      rGreen = value.substring(value.indexOf(',')+1,value.lastIndexOf(',')).toInt();
      rBlue = value.substring(value.lastIndexOf(',')+1).toInt();
      ledNode.setProperty( "color").send(value);
  }

  updateState();
  
  return true;
}







/*
 * Update the light state (i.e. colorWipe it) based on the
 * settings i've been told
 */
void updateState()
{


  if(LightState && brightness != 0) {
    // do colour calc - gunna be fun
    //tRed = (rRed * 255)/brightness;
    //tGreen = (rGreen * 255)/brightness;
    //tBlue = (rBlue * 255)/brightness;
    colorWipe(strip.Color(rRed, rGreen, rBlue), 50);
  } else {
    colorWipe(strip.Color(0, 0, 0), 50);
  }

  String val = String(tRed) + "," + String(tGreen) + "," + String(tBlue);
  ledNode.setProperty( "color").send(val);
  if(LightState) {
    lightSwitch.setProperty("status").send("on");
  } else {
    lightSwitch.setProperty("status").send("off");
  }
  brightnessNode.setProperty("brightness").send(String(brightness));

  

}








/*
 * Handle the on/off signal
 */
bool switchLight(HomieRange range, String value)
{

  // handle a variety of "on" messaages (on/ON/true/TRUE/1)
  if(value == "on" || value == "ON" || value == "true" || value == "TRUE" || value == "1") {
    // turn the light off
    if(brightness == 0) brightness = 128;
    LightState = true;
  } else {
    // turn the light on
    LightState = false;    
  }
  updateState();

  // tell the mqtt server about it
  lightSwitch.setProperty("status").send(value);

  return true;
}









/*
 * handle the brightness factor
 */
bool changeBrightness(HomieRange range, String value)
{
  brightness = value.toInt();
  
  // bounds check
  if(brightness > 255) brightness = 255;
  if(brightness < 0) brightness = 0;
  
  updateState();

  // tell mqtt about it all
  brightnessNode.setProperty("brightness").send(value);
  
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
  strip.begin();

  Homie_setFirmware(FW_NAME, FW_VERSION);

  // register our light settings to mqtt
  ledNode.advertise("color").settable(lightOnHandler);
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
