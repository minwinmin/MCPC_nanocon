#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
//#include <SoftwareSerial.h>//BLEにつかってるっぽい
#include <Adafruit_NeoPixel.h>
#include <math.h>

#define LED_COUNT 30
#define DIGITAL_PIN A1

Adafruit_NeoPixel led = Adafruit_NeoPixel( LED_COUNT,DIGITAL_PIN , NEO_GRB + NEO_KHZ800);

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void setup(void) {
  Serial.begin(115200);
  if (! lis.begin(0x19)) {  Serial.println("Couldnt start");
    while (1);
  }
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");

  led.begin();
  led.show();
  
}

void loop() {
  lis.read(); 
  sensors_event_t event; 
  lis.getEvent(&event);
  Serial.print(event.acceleration.x); Serial.print(",");
  Serial.print(event.acceleration.y); Serial.print(",");
  Serial.println(event.acceleration.z); 

    //なんかif文2つ目がちゃんと動作しないのだけどなんで？？？？？？？
    //本来は機械学習でモデリングするべき？やり方はよくわからん
    //加速度判定ならなんとかなるけど、精度は低い
    //なんでだろう？？？？
    //単純に3軸の平均で判断したい
  double total = (event.acceleration.x)*(event.acceleration.x)+(event.acceleration.y)*(event.acceleration.y)+(event.acceleration.z)*(event.acceleration.z); 
  double amount = sqrt(total);
  /*  if( event.acceleration.x >= 30 ||  event.acceleration.x <= -30 
        || event.acceleration.y >= 30 ||  event.acceleration.y <= -30
        || event.acceleration.z >= 30 ||  event.acceleration.z <= -30){
            led.setPixelColor( 0, led.Color( 0,255,255));
            led.setPixelColor( 1, led.Color( 0,255,255));
            led.setPixelColor( 2, led.Color( 0,255,255));
            led.show();
       Serial.println("***");
    }else if(30 > event.acceleration.x >= 12 || -30 < event.acceleration.x <= -12 
             || 30 > event.acceleration.y >= 12 || -30 < event.acceleration.y <= -12
             || 30 > event.acceleration.z >= 12 || -30 < event.acceleration.z <= -12){
            led.setPixelColor( 0, led.Color(255,255, 0));
            led.setPixelColor( 1, led.Color(255,255, 0));
            led.setPixelColor( 2, led.Color(255,255, 0));
            led.show();
       Serial.println("**");
    }else if(12 > event.acceleration.x >= 0 || -12 < event.acceleration.x <= 0 
             || 12 > event.acceleration.y >= 0 || -12 < event.acceleration.y <= 0
             || 12 > event.acceleration.z >= 0 || -12 < event.acceleration.z <= 0){
            //red
            led.setPixelColor( 0, led.Color(255, 0, 0));
            led.setPixelColor( 1, led.Color(255, 0, 0));
            led.setPixelColor( 2, led.Color(255, 0, 0));
            led.show();
       Serial.println("*");
    }
    */

      if( amount >= 20){
            //led.setPixelColor( 0, led.Color( 0,255,255));
            led.setPixelColor( 1, led.Color( 0,255,255));
            //led.setPixelColor( 2, led.Color( 0,255,255));
            led.show();
       Serial.println(amount);
       Serial.println("***");
        //delay(1000);
    }else if(20 > amount >= 10 ){
            //led.setPixelColor( 0, led.Color(255,255, 0));
            led.setPixelColor( 1, led.Color(255,255, 0));
            //led.setPixelColor( 2, led.Color(255,255, 0));
            led.show();
       Serial.println(amount);
       Serial.println("**");
       //delay(1000);
    }else if(10 > amount >= 0){
            //red
            //led.setPixelColor( 0, led.Color(255, 0, 0));
            led.setPixelColor( 1, led.Color(255, 0, 0));
            //led.setPixelColor( 2, led.Color(255, 0, 0));
            led.show();
       Serial.println(amount);
       Serial.println("*");
        //delay(1000);
    }
   delay(300);
     

}

