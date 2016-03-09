#include "application.h"
#include "dotstar.h"

// enable background for system functions
SYSTEM_THREAD(ENABLED);

#define NUM_LEDS 240

/*
  TODO (this includes nonsettings)
  Hardware and connection dependent settings
 */

int lightMode = 6; // one less than we want bc interrupt runs at beginning apparently

#include "strip_functions.h"
uint16_t _num_led = NUM_LEDS; // Number of pixels in strand
uint8_t _pin_led = 6; // NeoPixel LED strand is connected to this pin
uint8_t _pin_pot = 9; // using 1K potentiometer
extern boolean checkButton();

#include "sound_reactive.h"
uint8_t _pin_mic = D4; // Microphone is attached to this analog pin
extern int vol;


/* Initialize variables */


#define DATA_PIN D6
#define CLOCK_PIN D7

Adafruit_DotStar
  strip = Adafruit_DotStar(NUM_LEDS, DATA_PIN, CLOCK_PIN);

boolean pushed = false;
/**
 * Instead doing work directly within interrupt, we'll just toggle a
 * variable that we'll check for later. This prevents any weirdness due to
 * variable volatility.
 */
void buttonInterrupt() {
  pushed = true;
}

//int lightMode = 0; // how many times the button has been pressed

void setup() {

  Serial.begin(9600);
  /* Interrupt setup */

    /*
      "FLORA supports external interrupts on D0 (INT2), D1(INT3), D2(INT1), and
      D3(INT0). You would attach your button between, say, D0 and GND."
      FLORA's D0 is labeled "RX" (https://learn.adafruit.com/assets/2845)
      and corresponds to Arduino interrupt 2.
      * https://www.arduino.cc/en/Reference/PinMode
      * https://www.arduino.cc/en/Reference/attachInterrupt
      * https://forums.adafruit.com/viewtopic.php?f=25&t=57650:
     */
    pinMode(0, INPUT_PULLUP); // configure pin to behave as input
    // when button is pushed, run buttonPushed()
    attachInterrupt(2, buttonInterrupt, FALLING); // listen for high to low

    // from Amplitie code, not sure if needed or what it does
    //pinMode(_pin_led, OUTPUT);

  /* sound_reactive */

    memset((void*) vol, 0, sizeof(vol));

    /*
      This is only needed on 5V Arduinos (Uno, Leonardo, etc.). Connect 3.3V to
      mic AND TO AREF ON ARDUINO and enable this line.  Audio samples are
      'cleaner' at 3.3V. COMMENT OUT THIS LINE FOR 3.3V ARDUINOS (FLORA, ETC.):
     */
    // analogReference(EXTERNAL);

  strip.begin();
  colorWipe(strip.Color(0,0,0),0);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  //Serial.print("audio:");
  //Serial.println(analogRead(D4));
  /*volMeter(20,60);*/


  /*rainbow(10);*/
  pulse(strip.Color(127, 0, 255), 0);
  //checkButton();

  /*switch (lightMode) {
    default:
      // we exceeded defined modes, reset and fall through
      lightMode = 0;
    case 0:
      colorWipe(strip.Color(0, 0, 0), 0);
      delay(20);
      break;
    case 1: rainbowSingle(3); break;
    case 2: rainbowCycle(1); break;
    case 3: rainbow(1); break;
    case 4:
      pulse(strip.Color(127, 0, 255), 0);
      break;
    case 5: volMeter(120,220); break;
    case 6: volMeter(220,250); break;
    case 7: volMeter( 20, 60); break;
    case 8: volMeter(  1,255); break;
  }*/

}
