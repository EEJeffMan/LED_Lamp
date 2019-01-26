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
 *    11 total LEDs, start with all white:
 *     
 */

#include <FastLED.h>

#define NUM_LEDS      11
#define LED_PIN       2
#define COLOR_ORDER   GRB

// color table

/*
 * (R, G, B)
 * White (255, 255, 255)
 * Red (255, 0, 0)
 * Green (0, 255, 0)
 * Blue (0, 0, 255)
 * Yellow (255, 255, 0)
 * Cyan (0, 255, 255)
 * Magenta (255, 0, 255)
 * Silver (192, 192, 192)
 * Gray (128, 128, 128)
 * Maroon (128, 0, 0)
 */

 #define WHITE_R  255
 #define WHITE_G  255
 #define WHITE_B  255

 #define RED_R  255
 #define RED_G  0
 #define RED_B  0

 #define GREEN_R  0
 #define GREEN_G  255
 #define GREEN_B  0

 #define BLUE_R 0
 #define BLUE_G 0 
 #define BLUE_B 255

 #define YELLOW_R 255
 #define YELLOW_G 255
 #define YELLOW_B 0

 #define CYAN_R 0
 #define CYAN_G 255
 #define CYAN_B 255

 #define MAGENTA_R  255
 #define MAGENTA_G  0
 #define MAGENTA_B  255

 #define SILVER_R 192
 #define SILVER_G 192
 #define SILVER_B 192

 #define GRAY_R 128
 #define GRAY_G 128
 #define GRAY_B 128

 #define MAROON_R 128
 #define MAROON_G 0
 #define MAROON_B 0  

CRGB leds[NUM_LEDS];

void setup() {

  Serial.begin(9600);
  
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);

  for (int i=0; i<NUM_LEDS; i++)
  {
    leds[i] = CRGB(WHITE_R, WHITE_G, WHITE_B);
  }
  FastLED.show();
}

void loop() {
  // put your main code here, to run repeatedly:
   
}
