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
//float a = 0;

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
    InkPageSprite.drawString(0,50,"Error reading temperature");
  }
  else {
    //if(M5.BtnUP.wasPressed()){
      //a = (event.temperature * (9/5) + 32);
    //}else if (M5.BtnDOWN.wasPressed()){
      //a = event.temperature;
    //}
    char bufferTemp[35];
    snprintf(bufferTemp, 35, "Temperature: %.2f C", event.temperature);
    InkPageSprite.drawString(20,50,bufferTemp);
    if(event.temperature < 15){
      char bufferTemp[35];
      snprintf(bufferTemp, 35, "Pas assez chaud");
      InkPageSprite.drawString(20,65,bufferTemp);
    }else if(event.temperature > 35){
      char bufferTemp[35];
      snprintf(bufferTemp, 35, "Trop chaud");
      InkPageSprite.drawString(20,65,bufferTemp);
    }
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    InkPageSprite.drawString(5,110,"Error reading humidity");
  }
  else {
    char bufferHum[35];
    snprintf(bufferHum, 35, "Humidity: %.2f %%", event.temperature);
    InkPageSprite.drawString(30,110,bufferHum);
    if(event.temperature < 30){
      char bufferTemp[35];
      snprintf(bufferTemp, 35, "Pas assez humide");
      InkPageSprite.drawString(30,125,bufferTemp);
    }else if(event.temperature > 75){
      char bufferTemp[35];
      snprintf(bufferTemp, 35, "Trop humide");
      InkPageSprite.drawString(30,125,bufferTemp);
    }
  }
  InkPageSprite.pushSprite();
  delay(5000);
}