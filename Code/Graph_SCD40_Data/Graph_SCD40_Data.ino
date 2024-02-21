#include <SensirionI2CScd4x.h>
#include "Arduino.h"
#include "TFT_eSPI.h"
#include <Wire.h>
#include "DotFont.h"          //larger LED Dot-Matrix
#include "Smaller_DotFont.h"  //smaller LED Dot-Matrix

SensirionI2CScd4x scd4x;
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

int values[24]={0};
int values2[24]={0};
char timeHour[3]="00";
char timeMin[3]="00";
char timeSec[3];

char m[12];
char y[5];
char d[3];
char dw[12];

int gw=204;  //204
int gh=102;  //102
int gx=50;   //position of graph across
int gy=144;  //144
int curent=0;
#define gray 0x6B6D
#define darkgrey  0x4208 
#define blue 0x0967
#define orange 0xC260
#define purple 0x604D
#define green 0x1AE9

int deb=0;
int Mode=0;

void setup(void)
{
  uint16_t error;
  char errorMessage[256];

  Serial.begin(115200);
  Wire.begin(18,17);
  scd4x.begin(Wire);
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setRotation(3);
    
  sprite.createSprite(280, 240); 
  sprite.setTextDatum(3);
  sprite.setSwapBytes(true);
  values[23]=gh/2;
  analogReadResolution(10);

  // stop potentially previously started measurement
  error = scd4x.stopPeriodicMeasurement();
  if (error) 
  {
   Serial.print("Error trying to execute stopPeriodicMeasurement(): ");
  }

  // Start Measurement
  error = scd4x.startPeriodicMeasurement();
  if (error) 
  {
   Serial.print("Error trying to execute startPeriodicMeasurement(): ");
   errorToString(error, errorMessage, 256);
   Serial.println(errorMessage);
  }
}

int counter=0;
int Min=gh/2;
int Max=gh/2;
int average=0;
String minT="";
String maxT="";

uint16_t co2;
uint16_t co2_min = 5000;  //too high a value
uint16_t co2_max = 10;    //too low a value

String co2_min_text;
String co2_max_text;

String co2_text;
String temp_text;
String humid_text;
float temperature = 0.0f;
float humidity = 0.0f;

void loop()
{
 uint16_t error;
 char errorMessage[256];
 delay(100);

 bool isDataReady = false;
 error = scd4x.getDataReadyFlag(isDataReady);

 sprite.fillSprite(TFT_BLACK);

 for(int i=1;i<12;i++)
 {
  sprite.drawLine(gx+(i*17),gy,gx+(i*17),gy-gh,darkgrey);
  if(i*17%34==0)
  if(i*2<10)
  sprite.drawString("0"+String((i*2)+1),gx+(i*17)-3,gy+8);  //Bottom 04,08,12,16,20
  else
  sprite.drawString(String(i*2),gx+(i*17)-4,gy+8);  //Bottom,4,8
 }
  
 for(int i=1;i<6;i++)
 {
  sprite.drawLine(gx,gy-(i*17),gx+gw,gy-(i*17),darkgrey);
  sprite.drawString(String(i*400-300),gx-30,gy-(i*17)); //Left side numbers, 
 }

  sprite.drawLine(gx,gy,gx+gw,gy,darkgrey);  //Bottom line
  sprite.drawLine(gx,gy,gx,gy-gh,darkgrey);  //Left side line

 if (error) 
 {
  Serial.print("Error trying to execute getDataReadyFlag(): ");
  errorToString(error, errorMessage, 256);
  Serial.println(errorMessage);
  return;
 }

 if (!isDataReady) 
 {
  return;
 }

 error = scd4x.readMeasurement(co2, temperature, humidity);

 if (error) 
 {
  Serial.print("Error trying to execute readMeasurement(): ");
  errorToString(error, errorMessage, 256);
  Serial.println(errorMessage);
  } 

  else if (co2 == 0) 
  {
   Serial.println("Invalid sample detected, skipping.");
  } 
  else
  {
  
   for(int i=0;i<21;i++)  
   {
    co2_text=co2;
    temp_text=temperature;
    humid_text=humidity;
    scd4x.readMeasurement(co2, temperature, humidity);
    if (co2 > 1700)
    {
     co2=1700;
    }
    else
    {
    }

    sprite.fillCircle(gx+(i*10), gy-(co2/17), 2, TFT_RED); 
    //Serial.println(co2/100);
    sprite.loadFont(DotFont);
    sprite.fillRect(10, 165, 250, 70, TFT_BLACK); //Black out old CO2 value, (10, 175, 250, 70
    sprite.setTextColor(TFT_WHITE, TFT_BLACK); 
    sprite.drawString(co2_text,25,215);
    sprite.unloadFont();
    sprite.loadFont(Smaller_DotFont);
    sprite.drawString(temp_text,175,190);
    sprite.drawString(humid_text,175,220);
    sprite.unloadFont();
  
    sprite.drawString("SCD40 Sensor Data",100,20);
    sprite.drawString(" C",240,200);
    sprite.drawString(" %H",240,225);
    sprite.drawString("ppm",140,225);
    sprite.drawString("min:",15,185);
    sprite.drawString("max:",90,185);

    //calculate co2 min and max
    if (co2<co2_min)
    co2_min = co2;
    Serial.print("Min:");
    Serial.println(co2_min);

    if (co2>co2_max)
    co2_max = co2;
    Serial.print("Max:");
    Serial.println(co2_max);

    co2_max_text=co2_max;
    co2_min_text=co2_min;
    sprite.loadFont(Smaller_DotFont);
    sprite.drawString(co2_max_text,115,180);
    sprite.drawString(co2_min_text,40,180);
    sprite.unloadFont();   
    sprite.pushSprite(0,0);
    delay(10000);
   }

   sprite.pushSprite(0,0);
  }

}

 