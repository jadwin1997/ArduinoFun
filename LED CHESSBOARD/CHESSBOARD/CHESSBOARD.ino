#include <FastLED.h>

#define NUM_LEDS 64

#define DATA_PIN 3
//#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];

void setup() { 
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
}

void loop() { 
  for(int x=0; x < NUM_LEDS;x++){
    if(x%2 == 0){
      leds[x] = CRGB(0,0,255);
    }
    else{
      leds[x] = CRGB(255,0,0);
    }
    }
  FastLED.show();
}


void setColumn(int column, CRGB color){
  for(int x = column; x < NUM_LEDS; x=x + 15 - 2*x){
    leds[x] = color;
  }
}

void setRow(int row, CRGB color){
  for(int x = row*8; x < row*8+8;x++){
    leds[x] = color;
  }
  
}
void setRowColumn(int row, int column, CRGB color) {
  int index;

  if (row % 2 == 0) {
    // Even rows
    index = row * 8 + column;
  } else {
    // Odd rows
    index = (row + 1) * 8 - column - 1;
  }

  leds[index] = color;
}
// CHAT GPT EFFECTS NOT TESTED
void effect3D(CRGB color1, CRGB color2) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if ((i + j) % 2 == 0) {
        setRowColumn(i, j, color1);
      } else {
        setRowColumn(i, j, color2);
      }
    }
  }
}

void effectRotatingCube(CRGB color) {
  const int cubeSize = 4;
  const int cubeOffset = 2;
  const int cubeCenter = 3;

  int cube[cubeSize][cubeSize][cubeSize];

  // Initialize cube
  for (int x = 0; x < cubeSize; x++) {
    for (int y = 0; y < cubeSize; y++) {
      for (int z = 0; z < cubeSize; z++) {
        if ((x == cubeCenter || y == cubeCenter || z == cubeCenter) &&
            (x != cubeCenter || y != cubeCenter || z != cubeCenter)) {
          cube[x][y][z] = 1;
        } else {
          cube[x][y][z] = 0;
        }
      }
    }
  }

  // Rotate cube
  for (int angle = 0; angle < 360; angle += 5) {
    // Clear LEDs
    FastLED.clear();

    // Rotate cube
    for (int x = 0; x < cubeSize; x++) {
      for (int y = 0; y < cubeSize; y++) {
        for (int z = 0; z < cubeSize; z++) {
          int newX = round((x - cubeCenter) * cos(radians(angle)) -
                           (z - cubeCenter) * sin(radians(angle))) +
                      cubeCenter;
          int newY = round((x - cubeCenter) * sin(radians(angle)) +
                           (z - cubeCenter) * cos(radians(angle))) +
                      cubeCenter;
          int newZ = y;

          if (cube[x][y][z] == 1) {
            setRowColumn(newX + cubeOffset, newY + cubeOffset, color);
            // Uncomment the line below to enable depth effect
            // setRowColumn(newX + cubeOffset, newY + cubeOffset, CRGB(color.r / (newZ + 1), color.g / (newZ + 1), color.b / (newZ + 1)));
          }
        }
      }
    }

    // Show the cube
    FastLED.show();
    delay(100);
  }
}
