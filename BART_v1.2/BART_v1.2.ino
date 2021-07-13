#include <FastLED.h>
FASTLED_USING_NAMESPACE

/* *********** FFT ***************** */
#include "arduinoFFT.h"

#define SAMPLES 64             //Must be a power of 2
#define SAMPLING_FREQUENCY 8000 //Hz, must be less than 10000 due to ADC
#define LED_BASS 4
#define LED_TREB 2
#define THRESH_BASS 600
#define THRESH_TREB 800

arduinoFFT FFT = arduinoFFT();

 
unsigned int sampling_period_us;
unsigned long microseconds;
 
double vReal[SAMPLES];
double vImag[SAMPLES];


/*****************  FAST LED  ******************/
// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define BUTTON_PIN      2
#define TOP_DATA_PIN    3
#define BOTTOM_DATA_PIN 4

//enum {CHILLING, DANCE_PARTY}; 
//int currentState = CHILLING;
//#define CLK_PIN   4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS_BOTTOM   47
#define NUM_LEDS_TOP 39
CRGB topLeds[NUM_LEDS_TOP];
CRGB bottomLeds[NUM_LEDS_BOTTOM];
//CRGBArray <NUM_LEDS_TOP>topLeds;
//CRGBArray <NUM_LEDS_BOTTOM> bottomLeds;

CLEDController *topLEDController;
CLEDController *bottomLEDController;

int fadeAmount = 1;
int count = 1;
//#define BASEBRIGHNESS          0
#define FRAMES_PER_SECOND  120
      
void setup() {
  delay(1000); // 1.5 second delay for recovery
  pinMode(BUTTON_PIN, INPUT);
  sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
  Serial.begin(57600);
  
  // tell FastLED about the LED strip configuration
  topLEDController = &FastLED.addLeds<LED_TYPE,TOP_DATA_PIN,COLOR_ORDER>(topLeds, NUM_LEDS_TOP).setCorrection(TypicalLEDStrip);
  bottomLEDController = &FastLED.addLeds<LED_TYPE,BOTTOM_DATA_PIN,COLOR_ORDER>(bottomLeds, NUM_LEDS_BOTTOM).setCorrection(TypicalLEDStrip);
   //FastLED.addLeds<LED_TYPE,BOTTOM_DATA_PIN,COLOR_ORDER>(bottomLeds, NUM_LEDS_BOTTOM).setCorrection(TypicalLEDStrip);
   //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(0);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
//SimplePatternList gPatterns = {Fire2012};
SimplePatternList gPatterns = {wahoo, wahoo_party, rainbow,  off};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
uint8_t baseBrightness = 0; 
uint8_t gBrightness = 0;
uint8_t topBrightness = 0;
uint8_t bottomBrightness = 0;

  
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();
  //Fire2012();
  //FastLED.show();
 
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  if(ButtonClick()) nextPattern();
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void myFFT() {
  long signalAvg = 0, signalMax = 0, signalMin = 1024, signalRange = 0;
   
    /*SAMPLING*/
    for(int i=0; i<SAMPLES; i++)
    {
        
        microseconds = micros();    //Overflows after around 70 minutes!
        
        vReal[i] = analogRead(0);
        //Serial.println(vReal[i]);
        vImag[i] = 0;
        
        signalMin = min(signalMin, vReal[i]);
        signalMax = max(signalMax, vReal[i]);
        signalAvg += vReal[i];
     
        while(micros() < (microseconds + sampling_period_us)){
        }
    }
     signalAvg /=  SAMPLES;
     signalRange = signalMax - signalMin;
    
 
    /*FFT*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
 
    /*PRINT RESULTS*/
//    Serial.print("Peak: ");
//    Serial.println(peak);     //Print out what frequency is the most dominant.
//    Serial.print("Level: ");
//    Serial.println(signalRange);     //Print loudness
    int thresh = 20;
    if (signalRange > thresh)
      gBrightness = map(signalRange, thresh, 200, 0, 255);
    else {
//      gBrightness = 0;
//      if (gBrightness > 15)
//        gBrightness *= 0.5;
//      else
//        gBrightness = 0;
//      
    }
      


   if(peak > THRESH_TREB && signalRange > thresh) {
      topBrightness = gBrightness;
    }
    else {
      topBrightness = 0;
    }
    
    if(peak < THRESH_BASS && signalRange > thresh) {
      bottomBrightness = gBrightness;
    }
    else {
      bottomBrightness = 0;
    }

}

//////////////////////////////////////////
//                                      //
//              PATTERNS                //
//                                      //
//////////////////////////////////////////

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( topLeds, NUM_LEDS_TOP, gHue, 7);
  fill_rainbow( bottomLeds, NUM_LEDS_BOTTOM, gHue, 7);
  addGlitter(30);
  FastLED.setBrightness(100);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    topLeds[ random16(NUM_LEDS_TOP) ] += CRGB::White;
    bottomLeds[ random16(NUM_LEDS_BOTTOM) ] += CRGB::White;
  }
}

void wahoo() {
  baseBrightness = 0;
  fill_solid(topLeds, NUM_LEDS_TOP, CRGB::Blue);
  fill_solid(bottomLeds, NUM_LEDS_BOTTOM, CRGB::OrangeRed);
  FastLED.setBrightness(100);
  FastLED.show();
}

void wahoo_party() {
  baseBrightness = 0;
  
  fill_solid(topLeds, NUM_LEDS_TOP, CRGB::Blue);
  fill_solid(bottomLeds, NUM_LEDS_BOTTOM, CRGB::OrangeRed);
  
  myFFT();
 
  topLEDController->showLeds(topBrightness);
  bottomLEDController->showLeds(bottomBrightness);
}


void sinelon()
{
  baseBrightness = 15;
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( topLeds, NUM_LEDS_TOP, 20);
  fadeToBlackBy( bottomLeds, NUM_LEDS_BOTTOM, 20);
  //uint8_t  bpm = map(gBrightness, 0, 255, 4, 16);
  int pos_top = beatsin16( 8, 0, NUM_LEDS_TOP-1 );
  int pos_bot = beatsin16( 8, 0, NUM_LEDS_BOTTOM-1 );
  
  topLeds[pos_top] += CHSV( gHue, 255, baseBrightness + topBrightness);
  bottomLeds[pos_bot] += CHSV( gHue, 255, baseBrightness + bottomBrightness);
}

// Fire2012 by Mark Kriegsman, July 2012
bool gReverseDirection = false;
// There are two main parameters you can play with to control the look and
// feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// in step 3 above).
//
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 50, suggested range 20-100 
#define COOLING  55

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 120

void Fire2012()
{
// Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS_BOTTOM];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS_BOTTOM; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS_BOTTOM) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS_BOTTOM - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS_BOTTOM; j++) {
      CRGB color = HeatColor( heat[j]);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS_BOTTOM-1) - j;
      } else {
        pixelnumber = j;
      }
      bottomLeds[pixelnumber] = color;
    }

}


void off() 
{
  FastLED.setBrightness(0);
  FastLED.show();
  FastLED.clear();
}

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  off();
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

int prevButtonState = LOW; //button up => pin reads HIGH

bool ButtonClick(void)
{
  bool retVal = false;
  
  int currButtonState = digitalRead(BUTTON_PIN);
  if(prevButtonState != currButtonState)
  {
    delay(10); //this is a cheat for debouncing
    if(currButtonState == LOW) retVal = true;  //button is down => pin reads LOW
  }
  prevButtonState = currButtonState;

  return retVal;
}

void HandleButtonClick() {
  
}
