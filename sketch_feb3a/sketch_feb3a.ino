#include <Adafruit_NeoPixel.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <WiFi.h>

#define PIN 2
 
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
 
void setup()
{
pixels.begin(); // This initializes the NeoPixel library.
srand(5);
WiFi.mode(WIFI_STA);
  WiFi.begin("K-Lab", "allhailklab");
}
 
void loop()
{
 
// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255

     while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
pixels.setPixelColor(0, pixels.Color(rand()%256,rand()%256, rand()%256)); // Moderately bright green color.
pixels.show(); // This sends the updated pixel color to the hardware.
delay(200); // Delay for a period of time (in milliseconds).

}