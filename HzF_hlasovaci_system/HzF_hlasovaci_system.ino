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
#define LED_PIN     7
#define NUM_LEDS    18
CRGB leds[NUM_LEDS];

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
  lcd.setCursor(0, 0);
  lcd.print("-    :    :    -");
  lcd.setCursor(0, 1);
  lcd.print("-    :    :    -");

  pinMode(logo_sw_pin, INPUT);  // set LOGO switch pin as input pin

  // Neopixel settings
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  delay(50);                  //needed

  // Interrupt settings
  cli();                        //stop interrupts for till we make the settings
  TCCR2A = 0;                   // Reset entire TCCR1A to 0
  TCCR2B = 0;                   // Reset entire TCCR1B to 0
  TCCR2B |= B00000111;          //  prescaler 1024 -> 16ms
  TIMSK2 |= (1 << TOIE2);       // overflow interrupt on Timer1 enable
  sei();                        // Enable interrupts

}
/************************************************************************************************/
void loop() {



}
/* Interrupt service routines ----------------------------------------*/
ISR(TIMER2_OVF_vect)
{
  TCNT2  = 0;                  //First, set the timer back to 0 so it resets for next interrupt

  static uint8_t number_of_overflows = 0;
  number_of_overflows++;

  if (number_of_overflows == 1)
  {
    logo_sw_value = digitalRead(logo_sw_pin);   // store LOGO switch value
    button_search();
    logo(logo_sw_value);
  }
  // sets how often will ADC tries to recognize pressed button
  else if (number_of_overflows == 2 && btn_pressed == 0) number_of_overflows = 0;
  // sets how long will ADC stop looking for button pressed after one is pressed
  else if (number_of_overflows == 100 && btn_pressed == 1)
  {
    number_of_overflows = 0;
    btn_pressed = 0;
  }
}
/* Custom functions --------------------------------------------------*/
void display_update() {
  /*
        //lcd.setCursor(postion, line);
        lcd.setCursor(0, 0);
        lcd.print("-1111:2222:3333-");
        lcd.setCursor(0, 1);
        lcd.print("-4444:5555:6666-");
  */

  lcd.setCursor(1, 0);
  lcd.print(first_band_votes);
  lcd.setCursor(6, 0);
  lcd.print(second_band_votes);
  lcd.setCursor(11, 0);
  lcd.print(third_band_votes);
  lcd.setCursor(1, 1);
  lcd.print(fourth_band_votes);
  lcd.setCursor(6, 1);
  lcd.print(fifth_band_votes);
  lcd.setCursor(11, 1);
  lcd.print(sixth_band_votes);

  sd_update();
}

void sd_update() {

  File soubor = SD.open("hlasy.txt", FILE_WRITE); //_ can not be in file name
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

  } else {
    lcd.setCursor(0, 0);
    lcd.print("SDerror");

    for ( int i = 0; i <= 5; i++)
    {
      leds[i] = CRGB ( 255, 0, 0);
      FastLED.show();
    }
  }

}

void button_search() {

  ADCvalue = analogRead(ADCpin);              // store ADC value
  // needed some delay ind this line for cycle below works fine
  for ( int i = 0; i <= 5; i++)
  {
    leds[i] = CRGB ( 0, 0, 0);
    FastLED.show();
  }

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
  // can't recognize with button was pressed
  else
  {
    for ( int i = 0; i <= 5; i++)
    {
      leds[i] = CRGB ( 255, 0, 0);
      FastLED.show();
    }
    btn_pressed = 1;
  }
}

void logo(bool sw)
{
  static bool change = 0;
  static uint8_t led_num = 6;

  if (sw == 0)  // if logo switch is on
  {
    if (led_num <= 17 && change == 0)
    {
      leds[led_num] = CRGB ( 0, 0, 255);
      FastLED.show();
    }
    else if (led_num <= 17 && change == 1)
    {
      leds[led_num] = CRGB ( 255, 0, 0);
      FastLED.show();
    }
  }

  if (led_num < 17) led_num++;
  else if (led_num == 17) 
  {
    change = !change;
    led_num++;
  }
  else led_num = 6;

}
