
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

enum specialState {
  nothing = 0,
  fire = 1,
  candle = 2,
  pointerforward = 3,
  pointerbackward = 4
};






// Special state variables
// first pointer mode
#define POINT_DELAY 40
int cPoint = 0;
int lastUp = 0;

// fire mode
CRGBPalette16 gPal;
specialState specState = nothing;
// TODO: make fire brightness come from generic brightness
#define BRIGHTNESS  200
#define FIRE_DELAY 15
#define COOLING  55
// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120





#define FW_NAME "lsc01-esp-home-mqtt-ws2812"
#define FW_VERSION "0.0.9"

#define NUM_LEDS 60
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
HomieNode ledNode("color", "color");
HomieNode brightnessNode("brightness", "brightness");
HomieNode lightSwitch("switch", "switch");





int countChar(String data, char chr)
{
  int nc = 0;
  int clen = data.length();
  for(int i=0; i<clen; i++) {
    if(data[i] == chr) nc++;
  }

  return nc;
}






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
//  ledNode.setProperty("ack").send("ack");
//  ledNode.setProperty("ack").send(value);

  // TODO: we really should check that value is something like [0-255],[0-255],[0-255]
  uint8_t sVal, eVal;
  uint8_t nlc = countChar(value, ',');
  
  if(nlc == 2) {
    sVal = 0;
    eVal = NUM_LEDS;
    rRed = getValue(value, ',', 0).toInt();
    rGreen = getValue(value, ',', 1).toInt();
    rBlue = getValue(value, ',', 2).toInt();
    //ledNode.setProperty( "color").send(value);
  } else if(nlc == 4) {
    sVal = getValue(value, ',', 0).toInt();
    eVal = getValue(value, ',', 1).toInt();
    rRed = getValue(value, ',', 2).toInt();
    rGreen = getValue(value, ',', 3).toInt();
    rBlue = getValue(value, ',', 4).toInt();    
  } else return true;

  myColorWipe(sVal, eVal, rRed, rGreen, rBlue);
 
  updateState();


//  ledNode.setProperty("ack").send("ack2");
//  ledNode.setProperty("ack").send(String(nlc));
//  ledNode.setProperty("ack").send(String(sVal));
//  ledNode.setProperty("ack").send(String(eVal));
//  ledNode.setProperty("ack").send(String(rRed));
//  ledNode.setProperty("ack").send(String(rGreen));
//  ledNode.setProperty("ack").send(String(rBlue));
//  ledNode.setProperty("ack").send("ackend");
  ledNode.setProperty("ack").send(value);
  
  return true;
}





/*
 * Handle the on/off signal
 * now takes x,y,state
 */


bool switchLight(HomieRange range, String value)
{
//  ledNode.setProperty("ack").send("ack");
//  ledNode.setProperty("ack").send(value);

  uint8_t sVal, eVal;
  uint8_t nlc = countChar(value, ',');
  String sState;

  if(nlc == 2) {
    sVal = getValue(value, ',', 0).toInt();
    eVal = getValue(value, ',', 1).toInt();
    sState = getValue(value, ',', 2);
  } else {
    sVal = 0;
    eVal = NUM_LEDS;
    sState = value;
  }

  specState = nothing;

  // handle a variety of "on" messaages (on/ON/true/TRUE/1)
  if(sState == "on" || value == "ON" || value == "true" || value == "TRUE" || value == "1") {
    // turn the light off
    myColorWipe(sVal, eVal, rRed, rGreen, rBlue);
    myBrightWipe(sVal, eVal, 255);
  } else if(sState == "fire") {
    gPal = HeatColors_p;
    specState = fire;
    myBrightWipe(0, NUM_LEDS, 255);
    myColorWipe(0, NUM_LEDS, 255, 64, 64);
  } else if(sState == "candle") {
  } else if(sState == "pointforward") {
    specState = pointerforward;
    myBrightWipe(0, NUM_LEDS, 255);
    myColorWipe(0, NUM_LEDS, 255, 255, 255);
  } else if(sState == "pointbackward") {
    specState = pointerbackward;
    myBrightWipe(0, NUM_LEDS, 255);
    myColorWipe(0, NUM_LEDS, 255, 255, 255);
  } else {
    // turn the light off - we use the last spec'd color
    myBrightWipe(sVal, eVal, brightness);
    myColorWipe(sVal, eVal, 0, 0, 0);
  }
  
  updateState();

  // tell the mqtt server about it
//  ledNode.setProperty("ack").send("ack2");
//  ledNode.setProperty("ack").send(value);

  lightSwitch.setProperty("status").send(value);

  return true;
}








/*
 * handle the brightness factor
 */
 
bool changeBrightness(HomieRange range, String value)
{
//  ledNode.setProperty("ack").send("ack");
//  ledNode.setProperty("ack").send(value);


  uint8_t sVal, eVal;
  uint8_t nlc = countChar(value, ',');


  if(nlc == 2) {
    sVal = getValue(value, ',', 0).toInt();
    eVal = getValue(value, ',', 1).toInt();
  
    brightness = getValue(value, ',', 2).toInt();
  } else {
    sVal = 0;
    eVal = NUM_LEDS;
    brightness = value.toInt();
  }
  
  // bounds check
  if(brightness > 255) brightness = 255;
  if(brightness < 0) brightness = 0;

  myBrightWipe(sVal, eVal, brightness);
  
  updateState();

  // tell mqtt about it all
//  ledNode.setProperty("ack").send("ack2");
//  ledNode.setProperty("ack").send(value);

  brightnessNode.setProperty("brightness").send(value);
  
  return true;
}






// the code below comes from FASTled - pretty much unedited


void Fire2012WithPalette()
{
// Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      byte colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
      myleds[j].r = color.r;
      myleds[j].g = color.g;
      myleds[j].b = color.b;
      myleds[j].br = 255;
    }
}



void makeState()
{
  switch(specState) {
    case fire:
      if((millis() - lastUp) > FIRE_DELAY) {
        Fire2012WithPalette();
        lastUp = millis();
      }
      break;
    case pointerforward:
      if((millis() - lastUp) > POINT_DELAY) {
        myleds[cPoint].br = 255;
        cPoint++;
        if(cPoint > (NUM_LEDS-1)) cPoint = 0;
        myleds[cPoint].br = 2;
        lastUp = millis();
      }
      break;
    case pointerbackward:
      if((millis() - lastUp) > POINT_DELAY) {
        myleds[cPoint].br = 255;
        cPoint--;
        if(cPoint < 0) cPoint = NUM_LEDS-1;
        myleds[cPoint].br = 2;
        lastUp = millis();
      }
      break;
  }

  updateState();
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

  myColorWipe(0, 60, 255, 255, 255);
  myBrightWipe(0, 60, 255);
  specState = fire;
  gPal = HeatColors_p;
  updateState();

}

/*
 * The loop codes
 */
void loop() {
  Homie.loop();

  if(specState != nothing) {
    makeState();
  }
}
