// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        5 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 144 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

int power_switch_pin = 6;


void setup() {
  
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  pinMode(power_switch_pin, INPUT_PULLUP);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

int previousState = -1;

void loop() {
  int switchState = digitalRead(power_switch_pin);
  if (switchState == previousState) {
    // delay(10);
    return;
  }
  if (switchState == 0) { // on
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
      pixels.setPixelColor(i, pixels.Color(i % 3 == 0 ? 255 : 0, i % 3 == 1 ? 255 : 0, i % 3 == 2 ? 255 : 0));
      pixels.show(); // Send the updated pixel colors to the hardware.
    }
  } else {
    pixels.clear();
    pixels.show();
  }
  previousState = switchState;
  delay(DELAYVAL); // Pause before next pass through loop
}
