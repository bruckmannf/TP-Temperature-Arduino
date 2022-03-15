#include <M5CoreInk.h>

Ink_Sprite InkPageSprite(&M5.M5Ink);

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
    InkPageSprite.drawString(35,50,"Hello World!"); //draw string. 绘制字符串
    InkPageSprite.pushSprite();
}

void loop() {
    int a=1;
}