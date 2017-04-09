/*
 * To use this code, you must have the following libraries:
 * - Homie for ESP8266 - https://github.com/marvinroger/homie-esp8266.git
 * - IR Remote library for ESP8266 - https://github.com/markszabo/IRremoteESP8266.git
 * - 
 * 
 * - Also assumes your using my board, but not necessary, feel free to use any!
 * 
 * License GPL, by takigama (me@pjr.cc), 2017.
 */

#define FW_NAME "esp8266-IR-send-recv-temp-light";
#define FW_VERSION "0.0.1a"

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Homie.h>
#include <IRremoteESP8266.h>



// pins that stuff hangs off
int IR_RECV_PIN = 4; //an IR detector/demodulator is connected to GPIO pin 2
int TEMP_PIN = 12;
int IR_SEND_PIN = 5;
bool ignoreloop = false;

OneWire onewire(TEMP_PIN);
DallasTemperature dTemp(&onewire);


// int LIGHT_PIN = adc;

// this var holds the last sent temperature
float cTemp = 0.0;
float fTemp = 0.0;
unsigned long cMillis=0,mMillis=0;
unsigned long lastTempMillis=0;

// ir results
decode_results results;


// temp check interval
unsigned long tc_interval = 60000ul;


// define out homie components
HomieNode Temp("temperature", "temperature");
HomieNode IR("ir", "ir");
HomieNode AmbLight("ambientlight", "ambientlight");

// setup our ir send and recv
IRrecv irrecv(IR_RECV_PIN);
IRsend irsend(IR_SEND_PIN);





void doTemp()
{
  if((cMillis-lastTempMillis) > tc_interval) {
    // update temp.... um.. i forgot how.

    // get a temp in both C and F
    dTemp.requestTemperatures(); 
    cTemp = dTemp.getTempCByIndex(0);
    fTemp = dTemp.getTempFByIndex(0);
    Serial.println("would send temps");
    Serial.println(String(cTemp));
    Serial.println(String(fTemp));

    // dont bother sending a temp if it doesnt make sense
    if(cTemp > -100.0 && cTemp < 100) {
      Temp.setProperty("temperaturec").send(String(cTemp));
      Temp.setProperty("temperaturef").send(String(fTemp));
    }

    lastTempMillis = cMillis;
  }
}





void doIrRecv(decode_results *r)
{
  IR.setProperty("irreceived").send("recd");
  String toSend;

  switch(r->decode_type) {
    case NEC:
      toSend = "NEC,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case SONY:
      toSend = "SONY,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case RC5:
      toSend = "RC5,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case RC6:
      toSend = "RC6,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case PANASONIC:
      toSend = "PANASONIC,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case SAMSUNG:
      toSend = "SAMSUNG,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case SANYO:
      toSend = "SANYO,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case MITSUBISHI:
      toSend = "MITSUBISHI,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case DISH:
      toSend = "DISH,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case LG:
      toSend = "LG,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case JVC:
      toSend = "JVC,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case AIWA_RC_T501:
      toSend = "AIWA_RC_T501,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case WHYNTER:
      toSend = "WHYNTER,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case SHARP:
      toSend = "SHARP,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case COOLIX:
      toSend = "COOLIX,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case DAIKIN:
      toSend = "DAIKIN,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case DENON:
      toSend = "DENON,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case KELVINATOR:
      toSend = "KELVINATOR,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case SHERWOOD:
      toSend = "SHERWOOD,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case MITSUBISHI_AC:
      toSend = "MITSUBISHI_AC ,"+String(r->bits) + "," +String(r->value,HEX);
    break;
    case UNKNOWN:
      toSend = "UNKNOWN,"+String(r->bits) + "," +String(r->value,HEX);
    break;
  }

  Serial.println(toSend);
  IR.setProperty("irreceived").send(toSend);
  Serial.print("unsigned int  ");          // variable type
  Serial.print("rawData[");                // array name
  Serial.print(r->rawlen - 1, DEC);  // array size
  Serial.print("] = {");                   // Start declaration

  // Dump data
  for (int i = 1;  i < r->rawlen;  i++) {
    Serial.print(r->rawbuf[i] * USECPERTICK, DEC);
    if ( i < r->rawlen-1 ) Serial.print(","); // ',' not needed on last one
    if (!(i & 1))  Serial.print(" ");
  }

  // End declaration
  Serial.println("};");  // 
  if(r->overflow) {
    Serial.println("overflow true");
  }
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







bool irSendHandler(HomieRange range, String value)
{
  ignoreloop = true;
  // decode "value" into something that makes sense.
  // should contain 3 comma sep'd values "encoding", "bits", "value";
  //IR.setProperty("irsenddebug").send("about to send");
  char val_c[128];

  irrecv.disableIRIn();


  Serial.println("about to send IR");
  Serial.println(value);
  String enc = getValue(value, ',', 0);
  String bits = getValue(value, ',', 1);
  String val = getValue(value, ',', 2);
  val.toCharArray(val_c, 128);
  unsigned long rval = strtoul(val_c, NULL, 16);

  if(enc == "NEC") {
    // for now i only handle nec cause im lazy
//    Serial.println("now sending NEC");
//    Serial.println(rval);
//    Serial.println(bits.toInt());
    irsend.sendNEC(rval,bits.toInt());
//    Serial.println("after irsend");
  }

//   testng for one device i just cant make work - a pioneer vsx-522 - GC says: sendir,1:1,1,40000,1,1,360,180,22,67,22,22,22,67,....
//   but i cant make it work for love nor money
//  unsigned int  rawData[67] = {8500,4250, 600,1600, 550,500, 600,1600, 550,500, 600,500, 600,1600, 550,500, 600,1600, 550,500, 600,1600, 550,500, 600,1600, 550,1600, 550,500, 600,1600, 550,500, 600,500, 600,500, 600,1600, 550,1600, 550,1600, 550,500, 550,500, 600,500, 600,1600, 550,1600, 550,500, 600,500, 600,500, 600,1600, 550,1600, 550,1600, 550};
//  irsend.sendRaw(rawData, sizeof(rawData) / sizeof(rawData[0]), 40);
//  irsend.enableIROut(40);
//  unsigned int Samsung_power_toggle[71] = {40000,1,1,360,180,22,67,22,22,22,67,22,22,22,22,22,67,22,22,22,67,22,22,22,67,22,22,22,67,22,67,22,22,22,67,22,22,22,22,22,22,22,67,22,67,22,67,22,22,22,22,22,22,22,67,22,67,22,22,22,22,22,22,22,67,22,67,22,67,22,989};
//  irsend.sendGC(Samsung_power_toggle, 71);

  irrecv.enableIRIn();
  ignoreloop = false;
  return true;
}





void setupHandler()
{
  irrecv.enableIRIn();
  irsend.begin();
//  dTemp.begin();
  
}



void loopHandler()
{
  if(ignoreloop) return;

  
  if (irrecv.decode(&results)) {
    doIrRecv(&results);
    irrecv.resume();
  }

  doTemp();

}



void  setup()
{
  Serial.begin(9600);


  // for some reason, whatever homie does on pin 16 kills the serial - not sure why
  // it should be pin 16 on a generic esp8266-12e board
  Homie.setLedPin(16, false);
  Homie_setFirmware(FW_NAME, FW_VERSION);
  Serial.println("and thus we begin");
  

  Homie.setSetupFunction(setupHandler).setLoopFunction(loopHandler);

  //HomieNode IR("ir", "ir");
  //HomieNode AmbLight("ambientlight", "ambientlight");
  Temp.advertise("temperaturef");
  Temp.advertise("temperaturec");
  IR.advertise("irsend").settable(irSendHandler);
  IR.advertise("irreceived");
  
  
  Homie.setup();
}






void loop()
{
  if(ignoreloop) return;
  cMillis = millis();


  
  Homie.loop();
}

