#include <Adafruit_NeoPixel.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PIN 2
 
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
 
void setup()
{
pixels.begin(); // This initializes the NeoPixel library.
srand(5);
}
 
void loop()
{
 
// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255

 
pixels.setPixelColor(0, pixels.Color(rand()%256,rand()%256, rand()%256)); // Moderately bright green color.
pixels.show(); // This sends the updated pixel color to the hardware.
delay(200); // Delay for a period of time (in milliseconds).

}