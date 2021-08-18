/***********************************************************************

   Voting system for HzF
   anable to store (microSD) and show (LCD) numer of votes for each button
   control adresable led strip for indication and visual effects

   system designed and programmed by František Langr 2021

 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // library for LCD
#include <SD.h>                 // library for SD card module
#include <FastLED.h>            // library for Neopixel adressable RGB strip WS2812
#define LED_PIN     7           // pin where NEOPIXEL data line is connected
#define NUM_LEDS    18          // number of LEDs on LED strip
CRGB leds[NUM_LEDS];
uint8_t const columns = 11;     //number of columns of colors 2D array
// 2D array storing logo animation colors (flickering if nuber lower than maximum(255) is used)
// first 10 columns for logo circle, last one for center LED
uint8_t colors[3][columns] = {
  {   0,   0,   0,   0,   0, 255, 255, 255, 255, 255, 255},
  {   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 255},
  { 255, 255, 255, 255, 255,   0,   0,   0,   0,   0, 255}
};

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

const int chipSelect = 4;   // pin where SD card module CS pin is connected

const int ADCpin = A7;      // input pin for button - resistor ladder
int ADCvalue = 0;           // variable to store the value coming from button - resistor ladder
bool btn_pressed = 0;       // variable storing if button was pressed

const int logo_sw_pin = 2;  // input pin for LOGO switch
bool logo_sw_value = 0;     // variable to store LOGO switch state

// variable to store band votes
int first_band_votes = 0;
int second_band_votes = 0;
int third_band_votes = 0;
int fourth_band_votes = 0;
int fifth_band_votes = 0;
int sixth_band_votes = 0;

/************************************************************************************************/
void setup() {
  // SD module settings
  SD.begin(chipSelect);         // SD module initialization

  // LCD settings
  lcd.begin(16, 2);             // LCD initialization
  lcd.clear();
  // default display view
  lcd.setCursor(0, 0);          // lcd.setCursor(postion, line); indexing from 0
  lcd.print("    ^^    ^^    ");
  lcd.setCursor(0, 1);
  lcd.print("    ^^    ^^    ");

  pinMode(logo_sw_pin, INPUT);  // set LOGO switch pin as input pin

  // Neopixel settings
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  delay(50);                  //needed

  // Interrupt settings - Timer2
  cli();                        // stop interrupts for till we make the settings
  TCCR2A = 0;                   // Reset entire TCCR2A to 0
  TCCR2B = 0;                   // Reset entire TCCR2B to 0
  TCCR2B |= B00000111;          // prescaler 1024 -> 16ms
  TIMSK2 |= (1 << TOIE2);       // overflow interrupt on Timer2 enable
  sei();                        // Enable interrupts

}
/************************************************************************************************/
void loop() {



}
/* Interrupt service routines ----------------------------------------*/
ISR(TIMER2_OVF_vect)
{
  TCNT2  = 0;   //First, set the timer back to 0 so it resets for next interrupt

  static uint8_t number_of_overflows = 0;
  number_of_overflows++;

  // if LOGO switch is on, every two ISR make logo animation change
  if (number_of_overflows % 2 == 0) logo();
  // search if any band button is pressed
  if (number_of_overflows == 1) button_search();      
  // sets how often will ADC tries to recognize pressed button
  else if (number_of_overflows == 2 && btn_pressed == 0) number_of_overflows = 0;
  // sets how long will ADC stop looking for button pressed after one is pressed
  else if (number_of_overflows == 100 && btn_pressed == 1)
  {
    number_of_overflows = 0;    // start counting number of overflows again
    btn_pressed = 0;            // ==0 until band button is pressed
  }
}
/* Custom functions --------------------------------------------------*/
// update number of votes on display (called by button_search();)
void display_update() {
  /*
        lcd.setCursor(0, 0);
        lcd.print("1111^^2222^^3333");
        lcd.setCursor(0, 1);
        lcd.print("4444^^5555^^6666");
  */

  lcd.setCursor(0, 0);
  lcd.print(first_band_votes);
  lcd.setCursor(6, 0);
  lcd.print(second_band_votes);
  lcd.setCursor(12, 0);
  lcd.print(third_band_votes);
  lcd.setCursor(0, 1);
  lcd.print(fourth_band_votes);
  lcd.setCursor(6, 1);
  lcd.print(fifth_band_votes);
  lcd.setCursor(12, 1);
  lcd.print(sixth_band_votes);

  sd_update();  // store new number of votes on microSD card
}
// store new number of votes on microSD card (called by display_update();)
void sd_update() {
  // if microSD card available open hlasy.txt (file created if not there)
  File soubor = SD.open("hlasy.txt", FILE_WRITE); //_ can not be in file name
  // if file opened successfully write number of actual votes in format 1111:2222:3333:4444:5555:6666
  if (soubor)
  {
    soubor.print(first_band_votes);
    soubor.print(":");
    soubor.print(second_band_votes);
    soubor.print(":");
    soubor.print(third_band_votes);
    soubor.print(":");
    soubor.print(fourth_band_votes);
    soubor.print(":");
    soubor.print(fifth_band_votes);
    soubor.print(":");
    soubor.println(sixth_band_votes);
    soubor.close();

  } 
  //if microSD is't available print SDerror on display and button LEDs lights red
  else 
  {
    lcd.setCursor(0, 0);
    lcd.print("SDerror");

    for ( int i = 0; i <= 5; i++)
    {
      leds[i] = CRGB ( 255, 0, 0);
      FastLED.show();
    }
  }

}
/* read and store ADCvalue(one wire connection to buttons/resistors ladder) 
 * define if/which button is pressed, count votes and calls display_update() 
 * (called by ISR(TIMER2_OVF_vect);)
 */
void button_search() {

  ADCvalue = analogRead(ADCpin);              // store ADC value
  // needed some delay ind this line for cycle below works fine
  for ( int i = 0; i <= 5; i++) leds[i] = CRGB ( 0, 0, 0);
  FastLED.show();

  // no button pressed
  if (ADCvalue >= 900)
  {
    //lcd.setCursor(0, 1);      // set cursor on first position and second line
    //lcd.print("   no input");
  }
  //first button pressed
  else if (ADCvalue >= 0 && ADCvalue <= 30)
  {
    leds[5] = CRGB ( 0, 255, 0);
    FastLED.show();
    btn_pressed = 1;
    first_band_votes++;
    display_update();
  }
  //second button pressed
  else if (ADCvalue >= 70 && ADCvalue <= 120)
  {
    leds[4] = CRGB ( 0, 255, 0);
    FastLED.show();
    btn_pressed = 1;
    second_band_votes++;
    display_update();
  }
  //third button pressed
  else if (ADCvalue >= 200 && ADCvalue <= 270)
  {
    leds[3] = CRGB ( 0, 255, 0);
    FastLED.show();
    btn_pressed = 1;
    third_band_votes++;
    display_update();
  }
  //fourth button pressed
  else if (ADCvalue >= 420 && ADCvalue <= 470)
  {
    leds[2] = CRGB ( 0, 255, 0);
    FastLED.show();
    btn_pressed = 1;
    fourth_band_votes++;
    display_update();
  }
  //fifth button pressed
  else if (ADCvalue >= 580 && ADCvalue <= 630)
  {
    leds[1] = CRGB ( 0, 255, 0);
    FastLED.show();
    btn_pressed = 1;
    fifth_band_votes++;
    display_update();
  }
  //sixth button pressed
  else if (ADCvalue >= 690 && ADCvalue <= 750)
  {
    leds[0] = CRGB ( 0, 255, 0);
    FastLED.show();
    btn_pressed = 1;
    sixth_band_votes++;
    display_update();
  }
  // can't recognize which button was pressed
  else
  {
    for ( int i = 0; i <= 5; i++) leds[i] = CRGB ( 255, 0, 0);
    FastLED.show();
    btn_pressed = 1;
  }
}
// make animation change - by one position shift color of all circle LEDs (called by ISR(TIMER2_OVF_vect);)
void logo()
{
  static uint8_t led_num = 6;   // variable for adress of writed LED 
  static uint8_t slow_down = 0; // counting how many times was functon called
  // slow down animation by ignoring odd cycles
  if (slow_down % 2 == 0)
  {
    logo_sw_value = digitalRead(logo_sw_pin);   // store LOGO switch value
    if (logo_sw_value == 0)  // if logo switch is on
    {
      for (int i = 0; i <= 9; i++) // cycle only 10 times, led num remember 16 for next run and that makes LED movement
      {
        leds[led_num] = CRGB ( colors[0][i], colors[1][i], colors[2][i]);
        if (led_num < 16) led_num++;  // increase led position
        else if (led_num == 16) led_num = 6;
      }

      leds[17] = CRGB ( colors[0][columns-1], colors[1][columns-1], colors[2][columns-1]); //center LED color (last in array)
      FastLED.show();
    }
    else  // turn of all logo LEDs
    {
      for (int i = 6; i <= 17; i++) leds[i] = CRGB ( 0, 0, 0);
      FastLED.show();
    }
  }
  slow_down++;
}
