#include <Adafruit_NeoPixel.h>

#define PIN 7
#define NPIX 120
#define TIME 10

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NPIX, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(200);
  strip.show(); // Initialize all pixels to 'off'

  timer();  // do the timer once
}

void loop() {
  alarm();
  delay(20);
}

void timer() {
  // delay calculated as follows: 
  // time per LED is: 60 seconds devided the Amount of LEDs (120) multiplied by 10 minutes (the amount of time the timer has to last)
  // time per led = 60/120*10 = 5 seconds (5000 ms).
//   int time_per_led = 600/NPIX*TIME;  // uncomment to test quickly
  int time_per_led = 60000/NPIX*TIME;
  int led_per_min = NPIX/TIME;
  
  for (int i=0; i<=NPIX; i++) {
    strip.setPixelColor(i, strip.Color(255, 255, 255));

    // after a minute has passed set all the pixels up to that point to blue/black.
    // except for the last minute
    if (i % led_per_min == 0 && i != NPIX){
      bool on = false;
      for (int k=0; k<=i; k++) {
        strip.setPixelColor(k-1, strip.Color(0, 0, 0));
        if (on == true){
          strip.setPixelColor(k-1, strip.Color(0, 0, 255));
        }
        if (k % led_per_min == 0){
          on = !on;
        }
      }
    }
    
    strip.show();
    delay(time_per_led); 
  }
}

void alarm() {
  // the alarm animation, which happens when the time runs out
  int time_per_led = 10; 
  int led_per_min = NPIX/TIME;
  bool on = true;
  for (int i=0; i<=NPIX; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    if (on == true){
      strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
    if (i % led_per_min == 0){
      on = !on;
    }  
    strip.show();
    delay(time_per_led); 
  }
  on = false;
  for (int i=0; i<=NPIX; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    if (on == true){
      strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
    if (i % led_per_min == 0){
      on = !on;
    }  
    strip.show();
    delay(time_per_led); 
  }
}
