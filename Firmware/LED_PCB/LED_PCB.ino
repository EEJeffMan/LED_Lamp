/*
 * Name: LED_LAMP
 * Author: EEJeffMan
 * Date: 3/9/19
 * 
 * Replace bulb in desk lamp with LEDs.
 *    
 * Hardware options for white or RGB LEDs
 *   White LEDs: 8 high power Cree LEDs, needs an external constant current regulator. Load is ~24V, target current is ~400mA max.
 *   RGB LEDs: 12 RGB LEDs, WS2812 or similar. Data lines connected in parallel. High side switch controlled by MCU to disable connection. Max input is ~5V.
 *      
 * Inputs:
 *   DIN (0): Data input to control operation.
 *   VIN_ADC (4,A2): input voltage
 *    
 * Outputs:
 *   DOUT (1): serial data for RGB LED's
 *   RGB_EN (2): Control of high side switch for power to RGB LEDs
 *   WHITE_EN (3): Control of low side switch for power to white LEDs
 * 
 * Description:
 *        
 *    Initially: both RGB_EN and WHITE_EN output low (outputs off).
 *    
 *    Read ADC input: 
 *      If input less than 5.5V: RGB LED mode.
 *      If input greater than 18V and less than 30V: White LED mode.
 *      Keep WHITE_EN on at all times unless voltage is > 30V. This is ok because
 *      the white LEDs will not draw any current unless input is greater than ~18V.
 *      RGB's must turn off when greater than ~5.5V to prevent damage.
 *    
 *    Use softwareserial to read input commands via DIN.
 *    
 *    RGB's use "FastLED" library, credit to tutorial in link below:
 *    https://howtomechatronics.com/tutorials/arduino/how-to-control-ws2812b-individually-addressable-leds-using-arduino/
 *    
 *    Commands:
 *    
 *      LED_MODE_OFF      both off
 *      LED_MODE_WHITE    RGB off, white on
 *      LED_MODE_RGB      RGB on, set PWM via FastLED
 */

#include <FastLED.h>
#include <SoftwareSerial.h>

#define NUM_LEDS      12
#define LED_PIN       1
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

// led mode defines
#define LED_MODE_OFF          0x10
#define LED_MODE_WHITE        0x20
#define LED_MODE_RGB_WHITE    0x30
#define LED_MODE_RGB_PURPLE   0x31
#define LED_MODE_RGB_BLUE     0x32
#define LED_MODE_RGB_RED      0x33
#define LED_MODE_RGB_ORANGE   0x34
#define LED_MODE_RGB_GREEN    0x35
#define LED_MODE_RGB_Yellow   0x36

// pin definitions
#define WHITE_EN_PIN    3
#define RGB_EN_PIN      2
#define DIN_PIN         0
#define DOUT_PIN        1
#define VIN_ADC_PIN     A2  //A2, aruidno pin & port pin 4

// marcros for led output control functions
#define white_leds_on()     digitalWrite(WHITE_EN_PIN, HIGH);
#define white_leds_off()    digitalWrite(WHITE_EN_PIN, LOW);
#define rgb_leds_on()       digitalWrite(RGB_EN_PIN, HIGH);
#define rgb_leds_off()      digitalWrite(RGB_EN_PIN, LOW);

// function prototypes
void set_led_mode (unsigned int mode);

// global variables
unsigned int led_mode = LED_MODE_OFF;

CRGB leds[NUM_LEDS];

void setup() {

  pinMode(DIN_PIN, INPUT);
  pinMode(DOUT_PIN, OUTPUT);
  pinMode(WHITE_EN_PIN, OUTPUT);
  pinMode(RGB_EN_PIN, OUTPUT);
  pinMode(VIN_ADC_PIN, INPUT);

  //initially, both outputs off
  led_mode = LED_MODE_OFF;
  set_led_mode(led_mode);

  SoftwareSerial tinySerial(DOUT_PIN, DIN_PIN);   // DOUT is not actually UART, it is  taken over with the FastLED library below.
  tinySerial.begin(9600);
  //Serial.begin(9600);
  
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

   unsigned int vin;

    // first, read vin and set output mode (off, white LEDs, or RGB LEDs):

   vin = analogRead(VIN_ADC_PIN);

   if (vin > ADC_WHITE_MAX)
   {
      led_mode = LED_MODE_OFF;
   }
   else if (vin > ADC_RGB_MAX)    // less than white ma but greater than RGB max
   {
      led_mode = LED_MODE_WHITE;
   }
   else                           // low enough to safely run RGB LEDs.
   {
      led_mode = LED_MODE_RGB;
   }

   set_led_mode(led_mode);

    // second, set RGB color, if in RGB mode

    delay(10);    // 10 ms
}

void set_led_mode(unsigned int mode)
{
    switch(mode)
    {
        case LED_MODE_OFF:
          white_leds_off();
          rgb_leds_off();
        break;

        case LED_MODE_WHITE:
          white_leds_on();
          rgb_leds_off();
        break;

        case LED_MODE_RGB:
           white_leds_on();   //voltage will be too low for LEDs to draw current, so ok to leave this on.
           rgb_leds_on();
        break;

        default:
            white_leds_off();
            rgb_leds_off();
            // set error code or send diagnostic message?
        break;
    }
}
