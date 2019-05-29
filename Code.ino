#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(-1);
int ap1 = A0;
int ap2 = A1;
int ap3 = A2;
int ap4 = A3;

int val1 = 0;
int val2 = 0;
int val3 = 0;
int vol = 0;

int tot = 0;
int lux = 0;
double con = 716;
double prec = 0;

void setup() {
  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  Serial.begin(9600);

  // display a line of text
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(25, 10);
  display.print("LUX 7");
  display.display();
  delay(500);
}

void loop() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0);

  val1 = analogRead(ap3);
  val2 = analogRead(ap2);
  val3 = analogRead(ap1);  
  vol = analogRead(ap4);
  
  Serial.println(val1);
  Serial.println(val2);
  Serial.println(val3);
  Serial.println(vol);
  
  tot = val1 + val2 + val3;
  
  if(tot<940)
    lux = val1;
  else if(tot>=940 && tot<1880)
    lux = 940+val2;
  else if(tot>1880 && tot<3000)
    lux = 1880+val3;

  prec = (vol/con)*100;
  
  display.print(lux);
  display.println(" LUX");
  display.print(prec);
  display.print(" %");
  
  display.display();

  delay(500);
}
