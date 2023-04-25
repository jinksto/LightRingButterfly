//C++ code for Arduino UNO REV3 [A000066]
//Adafruit 24 RGB LED Neopixel Ring
//Code by Jinksto


#include <Adafruit_NeoPixel.h>

#define PIN 9         // this is the pin on the minicomputer that controls the light ring
#define NUMPIXELS 24  // this is the total number of pixels in the light right used to create the object.

// default delay value.  Because of the way that the Arduinio runs delays less than 300ms can cause issues.
int delayval = 300;

// The 24 pixel neo pixel has brightness levels between 0 and 255.  10 is bright enough, 255 is too bright for most things.
int defaultBright = 10;

//Create light ring object
Adafruit_NeoPixel lightRing24 = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

//define a subset of colors and name them
uint32_t red = lightRing24.Color(255, 0, 0, 0);     //red
uint32_t orange = lightRing24.Color(255, 100, 10);  //orange
uint32_t yellow = lightRing24.Color(255, 255, 0);   //yellow
uint32_t green = lightRing24.Color(0, 255, 0);      //green
uint32_t dkgreen = lightRing24.Color(0, 115, 0);    //dark green
uint32_t cyan = lightRing24.Color(0, 255, 255);     //cyan
uint32_t blue = lightRing24.Color(0, 0, 255);       //blue
uint32_t magenta = lightRing24.Color(255, 0, 255);  //magenta
uint32_t purple = lightRing24.Color(50, 0, 50);     //purple
uint32_t white = lightRing24.Color(0, 0, 0, 255);   //white

// array of defined colors so that we can easily roatate through them if needed.  Not used in Rainbow()
uint32_t colors[10] = { red, orange, yellow, green, dkgreen, cyan, blue, magenta, purple, white };

// array of pixel numbers to be lighted so that we can only light LED's that are behind wings.
int pixels[14] = { 0, 1, 2, 3, 5, 6, 7, 13, 14, 15, 17, 18, 19, 20 };


void setup() {
  lightRing24.begin();                       // This initializes the NeoPixel library.
  lightRing24.setBrightness(defaultBright);  // Set brightness
  lightRing24.show();                        // Initialize all pixels
}

//This void loop is default for the Arduino device.  It just, well, loops forever which is the primary function of this minicomputer
void loop() {

  //rainbow() is a built in function in class Adafruit_NeoPixel.  It doesn't really do what we want but...whatev kev.
  lightRing24.rainbow(1000);
  lightRing24.show();
  delay(2000);

  // start at max brightness and fade to black
  fade();
  delay(2000);

  // show all defined colors.  There are only 9
  showAllColors();
  delay(2000);
  offAll();

  /*
  // TEST: bink the index number for each pixel
  blinkIndex();
  offAll();
  delay (2000);

  // TEST: light all of the pixels as white to test the device
  lightAll();
  delay(2000);
  */
}

void offAll() {
  //use clear() to remove all pixel colors which has the net effect of turning them all off.
  lightRing24.clear();
  lightRing24.show();
}

void showAllColors() {
  // Set the colors for all pixels using the 10 colors we've defined.  This would work better as a nested for loop.
  lightRing24.setPixelColor(0, red);
  lightRing24.setPixelColor(1, orange);
  lightRing24.setPixelColor(2, yellow);
  lightRing24.setPixelColor(3, green);
  lightRing24.setPixelColor(4, dkgreen);
  lightRing24.setPixelColor(5, cyan);
  lightRing24.setPixelColor(6, blue);
  lightRing24.setPixelColor(7, magenta);
  lightRing24.setPixelColor(8, purple);
  lightRing24.setPixelColor(9, white);
  lightRing24.setPixelColor(10, red);
  lightRing24.setPixelColor(11, orange);
  lightRing24.setPixelColor(12, yellow);
  lightRing24.setPixelColor(13, green);
  lightRing24.setPixelColor(14, dkgreen);
  lightRing24.setPixelColor(15, cyan);
  lightRing24.setPixelColor(16, blue);
  lightRing24.setPixelColor(17, magenta);
  lightRing24.setPixelColor(18, purple);
  lightRing24.setPixelColor(19, white);
  lightRing24.setPixelColor(20, red);
  lightRing24.setPixelColor(21, orange);
  lightRing24.setPixelColor(22, yellow);
  lightRing24.setPixelColor(23, green);

  // show them all at once.
  lightRing24.show();
}


void lightAll() {
  lightRing24.setBrightness(defaultBright);
  for (int i = 0; i < NUMPIXELS; i++) {
    lightRing24.setPixelColor(i, white);
    lightRing24.show();
  }
}

void blinkIndex() {
  for (int x : pixels) {
    // Blink each pixel off, on, a number of times equal to its index number ... probably.
    // Clearly this is a problem for index 0 so just set 0 to green first.
    lightRing24.setPixelColor(0, green);
    for (int y = 0; y <= x; y++) {
      //If index zero, there's no need to blink red.
      if (x == 0) {
        lightRing24.setPixelColor(x, green);
        continue;
      }
      lightRing24.setPixelColor(x, 0, 0, 0, 0);
      lightRing24.show();
      delay(300);
      lightRing24.setPixelColor(x, red);
      lightRing24.show();
      delay(300);
      lightRing24.setPixelColor(x, 0, 0, 0, 0);
      lightRing24.show();
      delay(300);
      lightRing24.setPixelColor(x, green);
      lightRing24.show();
    }
  }
}

void fade() {
  for (int i = 255; i > -1; i = i - 5) {
    lightRing24.setBrightness(i);
    lightRing24.show();
    delay(400);
  }
  //call offAll() to set the color for the entire strip to black (e.g. off)
  offAll();
  // reset the strip to the default brightness now that there are no colors set.
  lightRing24.setBrightness(defaultBright);
}
