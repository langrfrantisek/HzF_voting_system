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
int i = 0;                  // testing variable

const int ADCpin = A7;      // input pin for button - resistor ladder
int ADCvalue = 0;           // variable to store the value coming from button - resistor ladder

const int logo_sw_pin = 2;  // input pin for LOGO switch
bool logo_sw_value = 0;     // variable to store LOGO switch state


/************************************************************************************************/
void setup() {
  // SD module settings
  SD.begin(chipSelect);         // SD module initialization

  // LCD settings
  lcd.begin(16, 2);             // LCD initialization
  lcd.clear();

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
    /*logo_sw_value = digitalRead(logo_sw_pin);   // store LOGO switch value
      lcd.setCursor(0, 0);                        // set cursor on first position and first line
      if (logo_sw_value == 0) lcd.print("on ");
      else lcd.print("off");*/

    ADCvalue = analogRead(ADCpin);              // store ADC value
    delay(100);

    leds[0] = CRGB ( 0, 255, 0);
    FastLED.show();

    if (ADCvalue >= 900)
    {
      lcd.setCursor(0, 1);                        // set cursor on first position and second line
      lcd.print("no input");
    }
    else if (ADCvalue >= 0 && ADCvalue <= 30)
    {
      lcd.setCursor(0, 1);                        // set cursor on first position and second line
      lcd.print("BTN: 1  ");
    }
    else if (ADCvalue >= 70 && ADCvalue <= 120)
    {
      lcd.setCursor(0, 1);                        // set cursor on first position and second line
      lcd.print("BTN: 2  ");
    }
    else if (ADCvalue >= 200 && ADCvalue <= 270)
    {
      lcd.setCursor(0, 1);                        // set cursor on first position and second line
      lcd.print("BTN: 3  ");
    }
    else if (ADCvalue >= 420 && ADCvalue <= 470)
    {
      lcd.setCursor(0, 1);                        // set cursor on first position and second line
      lcd.print("BTN: 4  ");
    }
    else if (ADCvalue >= 580 && ADCvalue <= 630)
    {
      lcd.setCursor(0, 1);                        // set cursor on first position and second line
      lcd.print("BTN: 5  ");
    }
    else if (ADCvalue >= 690 && ADCvalue <= 750)
    {
      lcd.setCursor(0, 1);                        // set cursor on first position and second line
      lcd.print("BTN: 6  ");
    }
    else
    {
      lcd.setCursor(0, 1);                        // set cursor on first position and second line
      lcd.print("ERROR   ");
    }
  } else if (number_of_overflows == 10) number_of_overflows = 0;

  //  if (number_of_overflows == 5)
  //  {
  //    leds[0] = CRGB ( 0, 255, 0);
  //    FastLED.show();
  //
  //    File soubor = SD.open("testXY.txt", FILE_WRITE);
  //    if (soubor)
  //    {
  //      Serial.println(i);
  //      soubor.println(i);
  //      soubor.close();
  //
  //      lcd.setCursor(0, 0);
  //      lcd.print("SD:");
  //      lcd.setCursor(4, 0);
  //      lcd.print(i);
  //
  //      delay(100);
  //
  //    } else {
  //      lcd.setCursor(4, 0);
  //      lcd.print("SDerror");
  //    }
  //    i++;
  //
  //  }

}
