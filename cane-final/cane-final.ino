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
int buzzer_pin = 13;
int speaker_pin = 9;
int sos_pin = 11; // was 7

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

 

void loop() {

  int buttonState = digitalRead(sos_pin);
  int pitches[]={440, 350};

  if (buttonState == HIGH) {

    Serial.println("On");

    for (int i=0; i<2; i++){

    tone(speaker_pin, pitches[i], 300);

    delay(300);

    noTone(3);

    };

  } else {

    Serial.println("Off");

  };

  int switchState = digitalRead(power_switch_pin);

  if (switchState == previousState) {
    Serial.println(switchState);
    delay(100);

    return;

  }
  Serial.println("New switch state!");

  if (switchState == 0) { // on

    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

      pixels.setPixelColor(i, pixels.Color(i % 3 == 0 ? 255 : 0, i % 3 == 1 ? 255 : 0, i % 3 == 2 ? 255 : 0));

      pixels.show(); // Send the updated pixel colors to the hardware.

    }

    digitalWrite(buzzer_pin, HIGH);

    delay(1000);

    digitalWrite(buzzer_pin, LOW);

  } else {

    pixels.clear();

    pixels.show();

  }

  previousState = switchState;

  delay(DELAYVAL); // Pause before next pass through loop
}
