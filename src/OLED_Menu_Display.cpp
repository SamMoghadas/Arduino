#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int currentMenu = 0;
const int totalMenus = 3;

void drawMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  
  switch (currentMenu) {
    case 0:
      display.print("Menu 1: Info");
      display.setCursor(0, 10);
      display.print("Press to navigate");
      break;
    case 1:
      display.print("Menu 2: Settings");
      display.setCursor(0, 10);
      display.print("Press to navigate");
      break;
    case 2:
      display.print("Menu 3: About");
      display.setCursor(0, 10);
      display.print("Press to navigate");
      break;
  }
  display.display();
}

void setup() {
  if (!display.begin(SSD1306_I2C_ADDRESS, OLED_RESET)) {
    for (;;);
  }
  drawMenu();
}

void loop() {
  if (digitalRead(2) == HIGH) { // Assuming button is connected to pin 2
    currentMenu = (currentMenu + 1) % totalMenus;
    drawMenu();
    delay(200); // Debouncing delay
  }
}
