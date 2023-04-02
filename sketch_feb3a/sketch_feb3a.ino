#include <dummy.h>

#include <Adafruit_NeoPixel.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PIN 2
 
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(10, PIN, NEO_GRB + NEO_KHZ800);
 
void setup()
{
pixels.begin(); // This initializes the NeoPixel library.
srand(5);
}
 
void loop()
{
 
// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
int i,j,k;
pixels.setPixelColor(0, pixels.Color(i%256,j%256, k%256) ); // Moderately bright green color. 
pixels.setPixelColor(1, pixels.Color(i%256,j%256, k%256)); // Moderately bright green color.
pixels.setPixelColor(2, pixels.Color(i%256,j%256, k%256)); // Moderately bright green color. 
pixels.setPixelColor(3, pixels.Color(i%256,j%256, k%256)); // Moderately bright green color.
pixels.setPixelColor(4, pixels.Color(i%256,j%256, k%256)); // Moderately bright green color. 
pixels.setPixelColor(5, pixels.Color(i%256,j%256, k%256)); // Moderately bright green color.
pixels.setPixelColor(6, pixels.Color(i%256,j%256, k%256)); // Moderately bright green color. 
pixels.setPixelColor(7, pixels.Color(i%256,j%256, k%256)); // Moderately bright green color.
pixels.setPixelColor(8, pixels.Color(i%256,j%256, k%256)); // Moderately bright green color. 
pixels.setPixelColor(9, pixels.Color(i%256,j%256, k%256)); // Moderately bright green color.

pixels.show(); // This sends the updated pixel color to the hardware.
delay(200); // Delay for a period of time (in milliseconds).

}