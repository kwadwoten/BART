// Use if you want to force the software SPI subsystem to be used for some reason (generally, you don't)
// #define FASTLED_FORCE_SOFTWARE_SPI
// Use if you want to force non-accelerated pin access (hint: you really don't, it breaks lots of things)
// #define FASTLED_FORCE_SOFTWARE_SPI
// #define FASTLED_FORCE_SOFTWARE_PINS
#include <FastLED.h>

///////////////////////////////////////////////////////////////////////////////////////////
//
// Move a white dot along the strip of leds.  This program simply shows how to configure the leds,
// and then how to turn a single pixel white and then off, moving down the line of pixels.
// 

// How many leds are in the strip?
#define NUM_LEDS    47
#define NUM_LEDS_TOP 39

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define TOP_DATA_PIN    3
#define BOTTOM_DATA_PIN 4
#define CLOCK_PIN 13
int fadeAmount = 5;
int brightness = 0;

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];
CRGB tleds[NUM_LEDS_TOP];

// This function sets up the ledsand tells the controller about them
void setup() {
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
   	delay(2000);


     FastLED.addLeds<WS2812B, TOP_DATA_PIN, RGB>(tleds, NUM_LEDS_TOP);  // GRB ordering is typical
     FastLED.addLeds<WS2812B, BOTTOM_DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical

}

// This function runs over and over, and is where you do the magic to light
// your leds.
//void loop() {
//   // Move a single white led 
//   for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
//      // Turn our current led on to white, then show the leds
//      leds[whiteLed] = CRGB::White;
//
//      // Show the leds (only one of which is set to white, from above)
//      FastLED.show();
//
//      // Wait a little bit
//      delay(100);
//
//      // Turn our current led back to black for the next loop around
//      leds[whiteLed] = CRGB::Black;
//   }
//}

//void loop(){
//  for( int cur = 0; cur < NUM_LEDS/3; cur = cur + 1){
//    leds[cur] = CRGB::Blue;
//  }
//
//  for(int cur = (NUM_LEDS/3); cur < ((NUM_LEDS/3)*2); cur = cur + 1){
//    leds[cur] = CRGB::White;
//  }
//
//  for( int cur = ((NUM_LEDS/3)*2); cur < NUM_LEDS; cur = cur + 1){
//    leds[cur] = CRGB::Red;
//  }
//}

  void loop(){

    for (int cur = 0; cur < NUM_LEDS_TOP; cur++){
  tleds[cur] = CRGB::White;
}

  for( int cur = 0; cur < NUM_LEDS/3; cur = cur + 1){
    leds[cur] = CRGB::Blue;
  }

  for(int cur = (NUM_LEDS/3); cur < ((NUM_LEDS/3)*2); cur = cur + 1){
    leds[cur] = CRGB::White;
  }

  for( int cur = ((NUM_LEDS/3)*2); cur < NUM_LEDS; cur = cur + 1){
    //leds[cur].setRGB(100,0,0);
    leds[cur] = CRGB::Green;
  }
    
    for(int i = 0; i < NUM_LEDS; i++){
      //leds[i] = CRGB::White;
      leds[i].fadeLightBy(brightness);
    }
    FastLED.show();
    brightness = brightness + fadeAmount;
    if(brightness == 0 || brightness == 255){
      fadeAmount= -fadeAmount;
    }
    delay(150);
  }
