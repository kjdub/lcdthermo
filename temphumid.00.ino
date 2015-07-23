#include <dht.h>
#include <LiquidCrystal.h>

// define pin and object for DHT11
#define dht_pin 2 
dht DHT;

// initialize display
LiquidCrystal LCD(7,8,9,10,11,12);

// define degree symbol
const char deg = (char)223;

// pointless loading function
void pLoad(LiquidCrystal &obj) {
  obj.setCursor(0,0);
  for(int i=0;i<16;i++)
  {
    obj.print(".");
    delay(150);
  }
  obj.clear();
}

void setup() {
  delay(1000);
  Serial.begin(9600);
  LCD.begin(16, 2);
  pLoad(LCD);
  delay(1000);
}

void loop() {
  // get data from sensor
  DHT.read11(dht_pin); 

  // make int to drop decimals
  int T = (int)DHT.temperature;
  int H = (int)DHT.humidity;
  float f = (DHT.temperature*1.8)+32; // do calc as float to retain accuracy then convert
  int F = (int)f;
  
  // print to serial
  Serial.print(T);
  Serial.print("*C, ");
  Serial.print(H);
  Serial.println("%");

  // print to LCD
  LCD.setCursor(0,0);
  LCD.print(T);
  LCD.print(deg); 
  LCD.print("C (");
  LCD.print(F);
  LCD.print(deg); 
  LCD.print("F)");
  // endl
  LCD.setCursor(0,2);
  LCD.print(H);
  LCD.print("% Humidity");

  // recommended MIN 2000ms delay before refresh.
  delay(7000); 
}
