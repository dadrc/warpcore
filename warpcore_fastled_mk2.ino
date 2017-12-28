#include "FastLED.h"
FASTLED_USING_NAMESPACE


#define DATA_PIN    5
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    140
#define CHAMBER 15
#define SIDE 35
#define FRAMES_PER_SECOND 120
CRGB leds[NUM_LEDS];

int toponly = SIDE - 2 * CHAMBER;
unsigned long last = 0;
int counter = 0;

void setup() {
  delay(1000); // 1 second delay for recovery
  Serial.begin(9600);
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(255);
  Serial.println(toponly);
}

void loop() {
  if (millis() > last + 60) {
    int i = counter;
    last = millis();
      for (int j = 0; j < 4; j++) {
        // even sides
        if (j % 2 == 0) {
          int bottom = j * SIDE;
          int top = bottom + SIDE;
  
          if (i > SIDE - CHAMBER - 2) {
            white(bottom + i - toponly);
            white(top - i);
            white(bottom + i - toponly + 1);
            white(top - i - 1);
          }
          else {
            if (i > toponly) {
              blue(bottom + i - toponly);
            }
            blue(top - i);
          }
        }
        // odd sides
        else {
          int top = j * SIDE - 1;
          int bottom = top + SIDE;
  
          if (i > SIDE - CHAMBER -2) {
            white(bottom - i + toponly);
            white(top + i);
            white(bottom - i + toponly - 1);
            white(top + i + 1);
          }
          else {
            if (i > toponly) {
              blue(bottom - i + toponly);
            }
            blue(top + i);
          }
        }
      }
      if (counter >= SIDE - CHAMBER) {
        counter = 0;
      }
      else {
        counter++;
      }
  }
  fadeToBlackBy(leds, NUM_LEDS, 30);
  FastLED.show();  
  FastLED.delay(1000/FRAMES_PER_SECOND); 
}

void blue(int pos) {
    leds[pos] = CRGB(0,0, 255);
}

void white(int pos) {
  leds[pos] = CRGB(255, 200, 200);
}


