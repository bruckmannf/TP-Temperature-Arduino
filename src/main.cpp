#include <M5CoreInk.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 26
#define DHTTYPE DHT22

DHT_Unified dht(DHTPIN, DHTTYPE);

Ink_Sprite InkPageSprite(&M5.M5Ink);
sensors_event_t event;
String oui = "%";

//Initialisation
void setup() {
    M5.begin();
    M5.M5Ink.clear();
    if( !M5.M5Ink.isInit()){
        Serial.printf("Ink Init faild");
        while (1) delay(100);
    }
    if( InkPageSprite.creatSprite(0,0,200,200,true) != 0 ){
        Serial.printf("Ink Sprite creat faild");
    }
    //digitalWrite(LED_EXT_PIN,LOW);
    InkPageSprite.drawString(35,50,"BIENVENUE");
    InkPageSprite.pushSprite();
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    dht.humidity().getSensor(&sensor);
    delay(3000);
}

void loop() {
    dht.begin();
    M5.M5Ink.clear();
    dht.temperature().getEvent(&event);
    InkPageSprite.creatSprite(0,0,200,200,true);
    // Get temperature event and print its value.
  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    InkPageSprite.drawString(15,50,"Error reading temperature!");
  }
  else {
    char bufferTemp[35];
    snprintf(bufferTemp, 35, "Temperature: %.2fC", event.temperature);
    InkPageSprite.drawString(15,50,bufferTemp);
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    InkPageSprite.drawString(15,100,"Error reading humidity!");
  }
  else {
    char bufferHum[35];
    snprintf(bufferHum, 35, "Humidity: %.2f", event.temperature);
    InkPageSprite.drawString(15,100,bufferHum);
  }
  InkPageSprite.pushSprite();
  delay(5000);
}