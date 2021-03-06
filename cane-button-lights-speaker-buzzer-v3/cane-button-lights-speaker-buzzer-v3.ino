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

#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels

int power_switch_pin = 6;
int buzzer_pin = 9;
// 6 is buzzer -> 4
// 7 is speaker

void setup() {
  
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  pinMode(power_switch_pin, INPUT_PULLUP);
  pinMode(buzzer_pin, OUTPUT);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

int previousState = -1;
int bootingUp = 1;

void loop() {

  if (bootingUp == 1) {
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
        pixels.setPixelColor(i, pixels.Color(i % 3 == 0 ? 255 : 0, i % 3 == 1 ? 255 : 0, i % 3 == 2 ? 255 : 0));
        pixels.show(); // Send the updated pixel colors to the hardware.
        delay(5);
    }
  
      pixels.clear();
      pixels.show(); // Send the updated pixel colors to the hardware.
      delay(5);
  }

  bootingUp = 0;
  int switchState = digitalRead(power_switch_pin);
  if (switchState == previousState) {
    Serial.println("Same state");
    delay(10);
    return;
  }
  
  if (switchState == 0) { // on
    Serial.println("ON");
    
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
      if (i > 100) {
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      } else {
        pixels.setPixelColor(i, pixels.Color(255, 255, 255));
      }
      
    }
    pixels.show(); // Send the updated pixel colors to the hardware.
  } else {
    Serial.println("OFF");
    pixels.clear();
    pixels.show();
//    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
//      
//      pixels.setPixelColor(i, pixels.Color(0,0,0));
//      pixels.show(); // Send the updated pixel colors to the hardware.
//    }
  }
  previousState = switchState;
  // delay(DELAYVAL); // Pause before next pass through loop
}
