#include <Adafruit_NeoPixel.h>

#define PIN 7
//#define NPIX 120
//#define TIME 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NPIX, PIN, NEO_GRB + NEO_KHZ800);

//int led_per_min = NPIX/TIME;
//int time_per_led = 60000/led_per_min;

unsigned long start_time;
unsigned long stop_time;

void setup() {
  Serial.begin(9600); 
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
  start_time = millis();
  timer();
  stop_time = millis();
  Serial.print("verstreken tijd: ");
  Serial.print((stop_time - start_time)/1000);
  Serial.println(" seconden"); 
}

void loop() {
  rainbow(20);
}

void timer() {
  for (int i=0; i<=NPIX; i++) {
    for (int j=0; j<=250; j++) {
      // delay calculated as follows: 
      // time per LED is: 60 seconds devided the Amount of LEDs (120) multiplied by 10 minutes (the amount of time the timer has to last)
      // time per led = 60/120*10 = 5 seconds.
      // delay is then 5000 ms / 250 (from 0 to full brightness) to turn on fade on a led in 5 seconds
      // delay = 5000/250 = 20ms
      delay(20); 
      strip.setPixelColor(i, strip.Color(j, j, j));
      strip.show();
    } 
  if ((i+1) % led_per_min == 0){
    for (int k=0; k<=i; k++) {
      strip.setPixelColor(k-1, strip.Color(0, 0, 255));
    }
    strip.show();
  }
 }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

