#include <Homie.h>
#include <Adafruit_NeoPixel.h>

#define FW_NAME "led-control"
#define FW_VERSION "1.0.0"

#define PIN            2
#define LED_COUNT      60

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 500; 
int showType = 0;
int SoffitR;
int SoffitG;
int SoffitB;
int numPixels = LED_COUNT;

HomieNode ledNode("led", "led");

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

bool lightOnHandler(HomieRange range, String value) {
  if (value == "off") {
    colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
    ledNode.setProperty( "color").send("0,0,0,0");
  } else if (value == "red") {
    colorWipe(strip.Color(255, 0, 0), 50);  // Red
    ledNode.setProperty( "color").send("0,255,0,0");
  } else if (value == "green") {
    colorWipe(strip.Color(0, 255, 0), 50);  // Green
    ledNode.setProperty( "color").send("0,0,255,0");
  } else if (value == "blue") {
    colorWipe(strip.Color(0, 0, 255), 50);  // Blue
    ledNode.setProperty( "color").send("0,0,255,0");
  } else {
      //value.trim();
      Serial.print (value);
      //Serial.flush();
      // split string at every "," and store in proper variable
      // convert final result to integer
      SoffitR = value.substring(0,value.indexOf(',')).toInt();
      SoffitG = value.substring(value.indexOf(',')+1,value.lastIndexOf(',')).toInt();
      SoffitB = value.substring(value.lastIndexOf(',')+1).toInt();
      colorWipe(strip.Color(SoffitR, SoffitG, SoffitB), 50);
      ledNode.setProperty( "color").send(value);
  }
  return true;
}


void setup() {
  Serial.begin(115200);
  Serial.println(FW_NAME FW_VERSION);
  
  strip.begin();

  Homie_setFirmware(FW_NAME, FW_VERSION);
  ledNode.advertise("color").settable(lightOnHandler);

  Homie.setup();

}

void loop() {
  Homie.loop();
}
