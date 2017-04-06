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
int IR_SEND_PING = 5;

OneWire onewire(TEMP_PIN);
DallasTemperature dTemp(&onewire);


// int LIGHT_PIN = adc;

// this var holds the last sent temperature
float cTemp = 0.0;
float fTemp = 0.0;
unsigned long cMillis=0;
unsigned long lastTempMillis=0;

// ir results
decode_results results;


// temp check interval
unsigned long tc_interval = 60000;


// define out homie components
HomieNode Temp("temperature", "temperature");
HomieNode IR("ir", "ir");
HomieNode AmbLight("ambientlight", "ambientlight");

// setup our ir send and recv
IRrecv irrecv(IR_RECV_PIN);
IRsend irsend(IR_SEND_PING);





void doTemp()
{
  if(cMillis < lastTempMillis || ((cMillis-lastTempMillis) > tc_interval)) {
    // update temp.... um.. i forgot how.

    // get a temp in both C and F
    dTemp.requestTemperatures(); 
    cTemp = dTemp.getTempCByIndex(0);
    fTemp = dTemp.getTempFByIndex(0);

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
  IR.setProperty("irreceived").send("read");
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
    case UNKNOWN:
      toSend = "UNKNOWN,"+String(r->bits) + "," +String(r->value,HEX);
    break;
  }

  IR.setProperty("irreceived").send(toSend);
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
  // decode "value" into something that makes sense.
  // should contain 3 comma sep'd values "encoding", "bits", "value";
  IR.setProperty("irsenddebug").send("about to send");

  String enc = getValue(value, ',', 0);
  String bits = getValue(value, ',', 1);
  String val = getValue(value, ',', 2);

  if(enc == "NEC") {
    // for now i only handle nec cause im lazy
    irsend.sendNEC(bits.toInt(), val.toInt());`
  }
    
}











void  setup()
{
  Serial.begin(9600);

  dTemp.begin();
  
  Homie_setFirmware(FW_NAME, FW_VERSION);
  
  irrecv.enableIRIn();

  Homie.setup();

  //Temp("temperature", "temperature");
  //HomieNode IR("ir", "ir");
  //HomieNode AmbLight("ambientlight", "ambientlight");
  Temp.advertise("ir").settable(irSendHandler);

}






void loop()
{
  cMillis = millis();

  if (irrecv.decode(&results)) {
    doIrRecv(&results);
    irrecv.resume();
  }
  
  doTemp();
  
  Homie.loop();
}

