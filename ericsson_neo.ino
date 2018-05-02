
//Fade LED

#include "FastLED.h"

#define NUM_LEDS 9*16
#define DATA_PIN 6
#define BRIGHTNESS 64

CRGB leds[NUM_LEDS];
int korv[] = {
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  17, 16,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  32, 33, 47, 46, 45, 44, 43, 42, 41,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  25, 24,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  9,  8,  7,  6,  5,  4,  3,  2,  1
};
int numkorv = 54;
int current = 0;
int c = 0;

void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void loop() {
  unsigned long ts = millis();
    int second = (ts / 1000) % 60;
    c = (ts / 25) % 255;
  current = (current + 1) % numkorv;
  for (int y = 0; y < 3; y++) {
    for (int i = 0; i < numkorv; i++) {
      if (korv[i] != NULL && i == current) {
        leds[korv[i] + y * 3 * 16] = ColorFromPalette(RainbowColors_p, (c + y * 64) % 255);
      } else if (korv[i] != NULL) {
        leds[korv[i] + y * 3 * 16].fadeToBlackBy(40);
      }
    }
  }
  FastLED.show();
  delay(4);
}
