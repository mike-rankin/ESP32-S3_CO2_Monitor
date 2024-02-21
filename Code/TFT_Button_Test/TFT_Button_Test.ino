/*
  Rev5 TFT and button test code
*/

#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

const int buttonPin1 = 39;
const int buttonPin2 = 40;

int buttonState1 = 0;
int buttonState2 = 0;

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

void setup(void)
 {
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor (30, 100);
  tft.print("Button & LCD Test"); 
  delay(2000);
  tft.fillScreen(TFT_BLACK);
}

void loop() 
{
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
 
  if (buttonState1 == HIGH) 
  {
   tft.setTextColor(TFT_RED, TFT_BLACK);
   tft.setTextSize(2);
   tft.setCursor (10, 15);
   tft.print("Button1"); 
   delay(500);
  } 

  if (buttonState2 == HIGH) 
  {
   tft.setTextColor(TFT_RED, TFT_BLACK);
   tft.setTextSize(2);
   tft.setCursor (160, 15);
   tft.print("Button2"); 
   delay(500);
  } 
  
  else 
  {
   tft.fillScreen(TFT_BLACK); 
   tft.setTextColor(TFT_GREEN, TFT_BLACK);
   tft.setTextSize(2);
   tft.setCursor (80, 100);
   tft.print("Waiting..."); 
   delay(250);
  }

}
