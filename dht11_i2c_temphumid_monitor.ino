#include <DHT.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 2      
#define DHTTYPE DHT11
#define SCREEN_I2C_ADDR 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RST_PIN -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST_PIN);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize the display
  if (!display.begin(SCREEN_I2C_ADDR, 0x3C)) {
    for (;;); // Loop forever if initialization fails
  }
  display.clearDisplay();

  display.setTextWrap(false);
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.print("Temp & Humid Sensor");
  display.drawFastHLine(0, 10, 128, SSD1306_WHITE);
  display.display();

  display.setCursor(0, 15);
  display.print("Temp:");
  display.display();
  
  display.setCursor(60, 15);
  display.print("Humid:");
  display.display();

  Serial.begin(9600); 
  Serial.println("DHT11 test!");
  dht.begin();
}

void loop() {
  display.fillRect(0,25,128,15,SSD1306_BLACK);
  delay(1000);

  int humidity = dht.readHumidity();
  int temperature = dht.readTemperature();

  // TEMPERATURE DISPLAY
  display.setCursor(0, 25);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.print(temperature);
  display.write(0xF7);
  display.display();

  // HUMIDITY DISPLAY
  display.setCursor(60, 25);
  display.fillRect(60, 25, 10, 10, SSD1306_BLACK); 
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.print(humidity);
  display.write(0x25);
  display.display();

  // Check if any reading failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
}
