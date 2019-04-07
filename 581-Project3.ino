#include "FastLED.h"  //Library with necessary information


#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    3
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    64
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120
int inLeftPin = 3;   // left button input pin
int inRightPin = 5;  // right button input pin
int LeftVal = 0;     // variable for reading left pin status
int RightVal = 0;    // variable for reading right pin status

void setup() {
  delay(3000);
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  
  Serial.begin(9600);
  pinMode(inLeftPin, INPUT);   // declare left button as input
  pinMode(inRightPin, INPUT);  // declare right button as input
  FastLED.addLeds<NEOPIXEL, 1>(leds, 60); //Declare the LEDS
}

void loop() {
  // put your main code here, to run repeatedly:
  LeftVal = digitalRead(inLeftPin);
  Serial.println(LeftVal);
  RightVal = digitalRead(inRightPin);
  Serial.println(RightVal);

  uint8_t gHue = 0; // rotating "base color" used by many of the patterns

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND);
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow 


//  if (LeftVal == 0 && RightVal == 0){
//    leds[0] = CRGB::Purple; FastLED.show(); delay(30); 
//  }
//
//  if (LeftVal == 1 && RightVal == 0){
//    leds[0] = CRGB::Red; FastLED.show(); delay(30);
//  }
//  if (LeftVal == 0 && RightVal == 1){
//    leds[0] = CRGB::Yellow; FastLED.show(); delay(30);
//  }
//  if (LeftVal == 1 && RightVal == 1){
//    leds[0] = CRGB::Green; FastLED.show(); delay(30);
//  }

  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
 
}
