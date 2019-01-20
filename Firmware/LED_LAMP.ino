/*
 * Name: LED_LAMP
 * Author: EEJeffMan
 * Date: 1/20/19
 * 
 * Description:
 *    Replace bulb in desk lamp with LEDs.
 *    
 *    Currently using WS2812 RGB LEDs.
 *    
 *    RGB's use "FastLED" library, credit to tutorial in link below:
 *    https://howtomechatronics.com/tutorials/arduino/how-to-control-ws2812b-individually-addressable-leds-using-arduino/
 *    
 *    
 */

#include <FastLED.h>

#define NUM_LEDS      1
#define LED_PIN       1
#define COLOR_ORDER   GRB

CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);

  leds[0] = CRGB(255, 0, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
   
}
