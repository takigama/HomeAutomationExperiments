#include <Adafruit_NeoPixel.h>
#include <NewPing.h>


#define DEBUG 0
// for ping
#define TRIGGER_PIN  5  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// for ws2812's
#define PIN            3
#define LED_COUNT      7
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);



// number of seconds to make the led go when state changes
int resTime = 10;
bool carParked = false;
bool stateChange = false;
int distance = 0;

// time for no state change
int nst_t = 0;

// 300cm's seems fair
int maxDist = 350;

// current dist, last current dist
int cDist = 0;
int lcDist = 0;

// "parked" distance
int minDist = 35;

// current state
int cState = 0;
int lcState = 0;
// cState = 0 empty if dist > 250 or 0
// cState = 1 parking if dist < 250 > 1 and delay < 1000
// cState = 2 parked if dist < 250 > 1 and dely == 1000

// at this dist we start going from green to red
//int cChangeDist = 200;

// at 45cm's we start changing the led colours to reflect where the person parking is
int startMin = 180;

int maxZeroTime = 1000;
int szt = 0;
int nrest = resTime * 10;
int cDelay;

int cRed = 0;
int cGreen = 0;
int cBlue = 0;
int cOn = 0;
int cBias = 0;
bool changeColour = false;
int cFlash = 0;

// a generic colorwipe function as per the
// adafruid examples
void colorWipe(uint32_t c, uint8_t wait)
{
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}



void setup()
{
  Serial.begin(115200);

  // start the ws2812 code
  strip.begin();
}

void loop()
{
  int cDiff;
  int cDiff_a;

  cDist = 0;


  // avoid a 0 type - but only for so long
  while((cDist == 0 || cDist > 200) && szt < maxZeroTime) {
    cDist = sonar.ping_cm();
    szt++;
  }

  if(cDist == 0) cDist = 1000;
  // zero szt just in case
  szt = 0;
  
  cDiff_a = lcDist - cDist;
  cDiff = abs(cDiff_a);

#if DEBUG
  Serial.print("cDist: ");
  Serial.print(cDist, DEC);
  Serial.print(", lcDist: ");
  Serial.print(lcDist, DEC);
  Serial.print(", cDiff: ");
  Serial.print(cDiff, DEC);
  Serial.print(", cDelay: ");
  Serial.print(cDelay, DEC);
  Serial.print(", nrest: ");
  Serial.print(nrest, DEC);
  Serial.print(", nst_t: ");
  Serial.print(nst_t, DEC);
  Serial.print(", cBias: ");
  Serial.print(cBias, DEC);
  if(stateChange) {
    Serial.print(" - state");
  } else {
    Serial.print(" - no state");
  }
  Serial.println("");
#endif

    
  if(cDiff < 3) {
    // no state change, increment rest timer
    if(cDelay < 2000) nst_t++;
    stateChange = false;
  } else {
    lcDist = cDist;
    nst_t = 0; 
    stateChange = true;
  }



  if(nst_t < nrest) {
    cDelay = 200;
    lcState = 1;

    // calc a colour value
    if(cDist > startMin) {
      changeColour = true;
      cRed = 0;
      cGreen = 255;
      cBlue = 0;
      cOn = 1;
      cFlash = 0;
    } else if(cDist < minDist) {
      changeColour = true;
      cRed = 255;
      cGreen = 0;
      cBlue = 0;
      if(cFlash < 16) {
        if(cOn == 1) {
          cOn = 0;      
        } else {
          cOn = 1;
        }
        cFlash++;
      } else {
        cOn = 1;
      }
    } else {
      // we calculate a colour bias value as we approach red
      cBias = ((cDist - minDist)*255)/(startMin - minDist);
      cRed = 255 - cBias;
      cGreen = 255 - cRed;
      cBlue = 0;
      cOn = 1;
      changeColour = true;
      cFlash = 0;
    }
  } else {
    
    if(cDist >= 250 || cDist == 0) {
      lcState = 0;
    } else if(cDist < 250) {
      lcState = 2;
    }
    cFlash = 0;
    cDelay = 1000;
    if(cOn != 0) changeColour = true;
    cOn = 0;
  }

  if(nst_t == 100) 
  {
    changeColour = true;
    cOn = 0;
  }

  if(lcState != cState) {
    switch(lcState) {
      case 0:
        Serial.println("empty");
      break;
      case 1:
        Serial.println("parking");
      break;
      case 2:
        Serial.println("parked");
      break;
    }
    cState = lcState;
  }

  //if(cDiff_a < 0) {
    //changeColour = true;
    //cOn = 0;
  //}

  if(changeColour) {
      if(cOn == 0) {
        colorWipe(strip.Color(0, 0, 0), 0);
      } else {
        colorWipe(strip.Color(cRed, cGreen, cBlue), 0);
      }
  }

  

  delay(cDelay);
}
