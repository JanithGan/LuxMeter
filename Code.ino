#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(-1);
double const MAXV = 716;
int const MAX = 1022;

int val1,val2,val3,vol,tot,lux;
double prec;

int ap1 = A2;
int ap2 = A1;
int ap3 = A0;
int ap4 = A3;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  display.setTextSize(2);       // Initialize Display
  display.setTextColor(WHITE);
  display.setCursor(25, 10);
  display.print("LUX 7");       // Display Initial Message
  display.display();

  delay(500);

  display.setTextSize(2);
  display.setCursor(0,0);
}

void loop() {
  val1 = analogRead(ap1);       // Take Voltage Readings
  val2 = analogRead(ap2);
  val3 = analogRead(ap3);  
  vol = analogRead(ap4);

  prec = (vol/MAXV)*100;        // Calculate Battery Precentage
  tot = val1 + val2 + val3;     // Sum of All Readings
  
  if(tot>MAX*2)                 // Calculate Lux Value Seperately
    lux = val3 + MAX*2;         // Auto Ranging
  else if(tot>MAX)
    lux = val2 + MAX;
  else
    lux = val1;
  
  display.clearDisplay();       // Display Lux Value
  display.print(lux);
  display.println(" LUX");
  display.print(prec);
  display.print(" %");
  display.display();

  delay(500);
}
