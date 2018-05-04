#include "FastLED.h"

#define NUM_LEDS 9*16
#define DATA_PIN 6
#define BRIGHTNESS 20
#define NUM_ROWS 36
#define MAX_PER_ROW 5
#define NUM_IN_KORVS 54
#define NUM_SPARKLES 10

CRGB leds[NUM_LEDS];
CHSV pixelColors[NUM_LEDS];
int korv[NUM_IN_KORVS] = {
  -1, -1, -1, -1, -1, -1, -1, -1,
  17, 16,
  -1, -1, -1, -1, -1, -1, -1, -1,
  32, 33, 47, 46, 45, 44, 43, 42, 41,
  -1, -1, -1, -1, -1, -1, -1, -1,
  25, 24,
  -1, -1, -1, -1, -1, -1, -1, -1,
  9,  8,  7,  6,  5,  4,  3,  2,  1
};
const int mx[NUM_ROWS][MAX_PER_ROW] = {
  {47,  32,  33,  -1,  -1},
  {46,  34,  -1,  -1,  -1},
  {45,  35,  -1,  -1,  -1},
  {44,  36,  -1,  -1,  -1},
  {31,  16,  17,  43,  37},
  {30,  18,  42,  38,  -1},
  {29,  19,  41,  40,  39},
  {15,  0,   1,   28,  20},
  {14,  2,   27,  21,  -1},
  {13,  3,   26,  22,  -1},
  {12,  4,   25,  24,  23},
  {11,  5,   95,  80,  81},
  {10,  6,   94,  82,  -1},
  {9,   8,   7,   93,  83},
  {92,  84,  -1,  -1,  -1},
  {79,  64,  65,  91,  85},
  {78,  66,  90,  86,  -1},
  {77,  67,  89,  88,  87},
  {63,  48,  49,  76,  68},
  {62,  50,  75,  69,  -1},
  {61,  51,  74,  70,  -1},
  {60,  52,  73,  72,  71},
  {59,  53,  143, 128, 129},
  {58,  54,  142, 130, -1},
  {57,  56,  55,  141, 131},
  {140, 132, -1,  -1,  -1},
  {127, 112, 113, 139, 133},
  {126, 114, 138, 134, -1},
  {125, 115, 137, 136, 135},
  {111, 96,  97,  124, 116},
  {110, 98,  123, 117, -1},
  {109, 99,  122, 118, -1},
  {108, 100, 121, 120, 119},
  {107, 101, -1,  -1,  -1},
  {106, 102, -1,  -1,  -1},
  {105, 104, 103, -1,  -1},
};
int current = 0;
int c = 0;

struct sparkle {
  int pos;
  int state;
  int offset;
};

const struct sparkle NEW_SPARKLE = {0, -1};
sparkle sparkles[NUM_SPARKLES];

void spark() {
  int ms = millis();
  for(int i = 0; i < NUM_SPARKLES; i++) {
    sparkle s = sparkles[i];
    if(s.state < 0) {
      s.pos = random(0, NUM_IN_KORVS);
      s.state = 255000;
    }

    /* s.state--; */
    if(korv[s.pos] > -1) {
      for(int j = 0; j < 3; j++) {
        pixelColors[korv[s.pos] + j * 3 * 16].saturation = cubicwave8((ms + s.offset) % 255);
      }
    }
  }
}

void setup() {
  for(int i = 0; i < NUM_SPARKLES; i++) {
    sparkles[i] = NEW_SPARKLE;
    sparkles[i].offset = random(0, 256);
  }
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  fill_solid(pixelColors, NUM_LEDS, CHSV(255, 255, 255));
  FastLED.show();
}

void loop() {
  unsigned long ms = millis() / 20;
  for(int i = 0; i < NUM_ROWS; i++) {
    for(int j = 0; j < MAX_PER_ROW; j++) {
      if(mx[i][j] != -1) {
        pixelColors[mx[i][j]].hue = (i + ms / 4) % 255;
        pixelColors[mx[i][j]].saturation = 255;
      }
    }
  }

  spark();
  hsv2rgb_rainbow(pixelColors,leds,NUM_LEDS);
  FastLED.show();
  FastLED.delay(10);
}
