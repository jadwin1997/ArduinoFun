
#define DECODE_NEC          // Includes Apple and Onkyo


#include <Arduino.h>
#include <FastLED.h>
#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc.
#include <IRremote.hpp>
#define NUM_LEDS 60

#define DATA_PIN 3
#define CLOCK_PIN 13
CRGB leds[NUM_LEDS];
void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
 
    Serial.begin(115200);
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);
    Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
}
void rainbow() {
  for(int i=0; i<NUM_LEDS; i++) {
    leds[i] = CHSV(i*255/NUM_LEDS, 255, 255);
     delay(20);
     FastLED.show();
  }
    for(int i=NUM_LEDS; i>0; i--) {
    leds[i] = CHSV(255, i*255/NUM_LEDS, 255);
         delay(20);
     FastLED.show();
  }
  for(int i=0; i<NUM_LEDS; i++) {
    leds[i] = CHSV(255, 255, i*255/NUM_LEDS);
     delay(20);
     FastLED.show();
  }

      for(int i=NUM_LEDS; i>0; i--) {
    leds[i] = CHSV(i*255/NUM_LEDS, i*255/NUM_LEDS, i*255/NUM_LEDS);
         delay(20);
     FastLED.show();
  }
 
}
void fire() {
  for(int i=0; i<NUM_LEDS; i++) {
    int flicker = random(50, 200);
    leds[i] = ColorFromPalette(HeatColors_p, flicker);
  }
  FastLED.show();
  delay(100);
}

void theaterChase(CRGB color, int wait) {
  for(int j=0; j<10; j++) {
    for(int q=0; q<3; q++) {
      for(int i=0; i<NUM_LEDS; i=i+3) {
        leds[i+q] = color;
      }
      FastLED.show();
      delay(wait);
      for(int i=0; i<NUM_LEDS; i=i+3) {
        leds[i+q] = CRGB::Black;
      }
    }
  }
}

void colorWaves() {
  uint8_t maxChanges = 24;
  for(int j=0; j<maxChanges; j++) {
    for(int i=0; i<NUM_LEDS; i++) {
      uint8_t hue = j + (i * 2);
      leds[i] = CHSV(hue, 255, 255);
    }
    FastLED.show();
    delay(50);
  }
}
void rainbowChase(uint8_t wait) {
  for(int j=0; j<256; j++) {
    for(int i=0; i<NUM_LEDS; i++) {
      leds[i] = CHSV(j+i, 255, 255);
    }
    FastLED.show();
    delay(wait);
  }
}
void colorWipe(CRGB color, int wait) {
  for(int i=0; i<NUM_LEDS; i++) {
    leds[i] = color;
    FastLED.show();
    delay(wait);
  }
}
void loop() {
    /*
     * Check if received data is available and if yes, try to decode it.
     * Decoded result is in the IrReceiver.decodedIRData structure.
     *
     * E.g. command is in IrReceiver.decodedIRData.command
     * address is in command is in IrReceiver.decodedIRData.address
     * and up to 32 bit raw data in IrReceiver.decodedIRData.decodedRawData
     */
    if (IrReceiver.decode()) {

        /*
         * Print a short summary of received data
         */
        IrReceiver.printIRResultShort(&Serial);
        IrReceiver.printIRSendUsage(&Serial);
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
            // We have an unknown protocol here, print more info
            IrReceiver.printIRResultRawFormatted(&Serial, true);
        }
        Serial.println();
    }

        /*
         * !!!Important!!! Enable receiving of the next value,
         * since receiving has stopped after the end of the current received data packet.
         */
        IrReceiver.resume(); // Enable receiving of the next value

        /*
         * Finally, check the received data and perform actions according to the received command
         */
        if (IrReceiver.decodedIRData.command == 0x45) { // 1 KEY
          //rainbow();
          colorWipe(CRGB(255,0,0),20);
              
        } else if (IrReceiver.decodedIRData.command == 0x46) { // 2 KEY
          //theaterChase(CRGB(100,255,100),100);
          colorWipe(CRGB(0,255,0),20);
              }

         else if (IrReceiver.decodedIRData.command == 0x44) { // 4 KEY
          colorWipe(CRGB(0,255,255),20);  
              }
         else if (IrReceiver.decodedIRData.command == 0x40) { // 5 KEY
          colorWipe(CRGB(255,255,255),20);
              }
         else if (IrReceiver.decodedIRData.command == 0x43) { // 6 KEY
          colorWipe(CRGB(0,0,0),20);
              }
         else if (IrReceiver.decodedIRData.command == 0x7) { // 7 KEY
          colorWipe(CRGB(255,255,0),20);
              }
         else if (IrReceiver.decodedIRData.command == 0x15) { // 8 KEY
          colorWipe(CRGB(255,0,255),20);
              } 
         else if (IrReceiver.decodedIRData.command == 0x9) { // 9 KEY
          rainbow();
              }
         else if (IrReceiver.decodedIRData.command == 0x16) { // * KEY
          theaterChase(CRGB(255,255,255), 100);
              }
         else if (IrReceiver.decodedIRData.command == 0x19) {// 0 KEY
          
              }
         else if (IrReceiver.decodedIRData.command == 0xD) {//#
        
              }
         else if (IrReceiver.decodedIRData.command == 0x18) {//UP ARROW
        
              }
         else if (IrReceiver.decodedIRData.command == 0x8) {//LEFT ARROW
          
              }
         else if (IrReceiver.decodedIRData.command == 0x1C) {//OK
            colorWipe(CRGB(255,0,0),20);
            colorWipe(CRGB(0,255,0),20);
            colorWipe(CRGB(0,0,255),20);
              }
         else if (IrReceiver.decodedIRData.command == 0x5A) {//RIGHT ARROW
        fire();
              }
         else if (IrReceiver.decodedIRData.command == 0x52) {//DOWN ARROW
          
              }        
        else if(IrReceiver.decodedIRData.command == 0x47) {
          colorWipe(CRGB(0,0,255),30);
              }
        
        
    
}
