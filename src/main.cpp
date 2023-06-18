#include <Arduino.h>
#include <FastLED.h>

#define DI_PIN_ONE 8
#define DI_PIN_TWO 9
#define DI_PIN_THREE 7
#define NUM_LEDS 12
#define NUM_LEDS_STRIP 7
#define BRIGHTNESS 255
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

CRGB leds_one[NUM_LEDS];
CRGB leds_two[NUM_LEDS];
CRGB leds_three[NUM_LEDS_STRIP];

#define UPDATES_PER_SECOND 100

void setup()
{
  FastLED.addLeds<LED_TYPE, DI_PIN_ONE, COLOR_ORDER>(leds_one, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, DI_PIN_TWO, COLOR_ORDER>(leds_two, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, DI_PIN_THREE, COLOR_ORDER>(leds_three, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void knight_rider()
{
  // Fill the entire strip with purple
  uint8_t sinBeat = beatsin8(30, 0, NUM_LEDS - 1, 0, 0);
  leds_one[sinBeat] = CRGB::Navy;

  EVERY_N_MILLISECONDS(1000 / 30)
  {
    Serial.print(">sinBeat:");
    Serial.println(sinBeat);
  }

  // Reduce brightness for whole strip every time it is called
  fadeToBlackBy(leds_one, NUM_LEDS, 2);

  FastLED.show();
}

void rainbow()
{
  fill_rainbow(leds_one, NUM_LEDS, 0, 255 / NUM_LEDS);
  FastLED.show();
}

uint8_t hue = 0;

void hsv()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    // H - Color
    // S - Saturation (Saturated or Pale)
    // V - Value (Brightness)
    leds_one[i] = CHSV(hue + (i * 15), 255, 127);
  }

  EVERY_N_MILLISECONDS(10)
  {
    hue++;
  }

  FastLED.show();
}

void pallette_intro() {}

uint8_t pallette_index = 0;

// Define a palette
DEFINE_GRADIENT_PALETTE(heatmap_gp){
    0, 0, 0, 0,        // black
    128, 255, 0, 0,    // red
    224, 255, 255, 0,  // bright yellow
    255, 255, 255, 255 // full white
};

CRGBPalette16 predefinedPallette = CRGBPalette16(
    CRGB::Red,
    CRGB::Blue,
    CRGB::Green,
    CRGB::Yellow);

// Actually load the palette into a CRGB array
CRGBPalette16 my_pal = heatmap_gp;

void pallette()
{
  fill_palette(leds_one, NUM_LEDS, pallette_index, 255 / NUM_LEDS, my_pal, 255, LINEARBLEND);

  EVERY_N_MILLISECONDS(10)
  {
    pallette_index++;
  }

  FastLED.show();
}

void palletteSecondary()
{
  EVERY_N_MILLISECONDS(200)
  {
    leds_one[random8(0, NUM_LEDS - 1)] = ColorFromPalette(my_pal, random8(), 255, LINEARBLEND);
  }

  EVERY_N_MILLISECONDS(25)
  {
    fadeToBlackBy(leds_one, NUM_LEDS, 1);
  }

  FastLED.show();
}

void palettBlend() {}

void first_sin()
{
  uint8_t beatSin = beatsin8(30, 0, NUM_LEDS - 1, 0, 0);
  uint8_t othrBeatSin = beatsin8(30, 0, NUM_LEDS - 1, 0, 124);

  leds_one[beatSin] = CRGB::Navy;
  leds_one[othrBeatSin] = CRGB::Red;

  fadeToBlackBy(leds_one, NUM_LEDS, 1);
  FastLED.show();
}

void progress()
{
  uint8_t beat = map(beat8(55), 0, 255, 0, NUM_LEDS - 1);
  uint8_t beat_two = map(beat8(55), 0, 255, 0, NUM_LEDS - 1);
  uint8_t beat_three = map(beat8(55), 0, 255, 0, NUM_LEDS_STRIP - 1);

  leds_one[beat] = CRGB::Red;
  leds_two[NUM_LEDS - 1 - beat_two] = CRGB::Red;
  leds_three[beat_three] = CRGB::Black;

  EVERY_N_MILLISECONDS(25)
  {
    fadeToBlackBy(leds_one, NUM_LEDS, 10);
    fadeToBlackBy(leds_two, NUM_LEDS, 10);
  }

  EVERY_N_MILLISECONDS(10)
  {
    fadeToBlackBy(leds_three, NUM_LEDS_STRIP, 10);
  }

  FastLED.show();
}

void loop()
{
  progress();
}