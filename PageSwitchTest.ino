#include <U8g2lib.h>

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* CS=*/ 10, /* reset=*/ 8);

// Button pin definitions
const int pageButtonPin = 2;
const int counterButtonPin = 4;
int currentPage = 0;  // Variable to track the current page
int counter = 0;      // Counter variable

void setup() {
  pinMode(pageButtonPin, INPUT_PULLUP);   // Set page button pin as input with pull-up resistor
  pinMode(counterButtonPin, INPUT_PULLUP); // Set counter button pin as input with pull-up resistor
  u8g2.begin();  // Initialize the display
}

void loop() {
  // Read the state of the buttons
  int pageButtonState = digitalRead(pageButtonPin);
  int counterButtonState = digitalRead(counterButtonPin);

  // Handle page button (short press) to switch pages
  if (pageButtonState == LOW) { // Page button pressed
    delay(100); // Simple debounce delay
    if (pageButtonState == LOW) { // Check if still pressed
      currentPage = (currentPage + 1) % 5;  // Switch to the next page
      while (digitalRead(pageButtonPin) == LOW); // Wait for button release
      Serial.println("Button is still pressed");
    }
  }

  // Handle counter button (short press) to increment the counter
  if (counterButtonState == LOW && currentPage == 3) { // Counter button pressed and on Page 4
    delay(100); // Simple debounce delay
    if (digitalRead(counterButtonPin) == LOW) { // Check if still pressed
      counter++; // Increment the counter
      while (digitalRead(counterButtonPin) == LOW); // Wait for button release
    }
  }

  // Draw the current page
  u8g2.firstPage();
  do {
    switch (currentPage) {
      case 0:
        drawPage1();
        break;
      case 1:
        drawPage2();
        break;
      case 2:
        drawPage3();
        break;
      case 3:
        drawPage4();
        break;
      case 4:
        drawPage5();
        break;
    }
  } while (u8g2.nextPage());
}

void drawPage1() {
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(10, 20, "This is Page 1");
}

void drawPage2() {
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(10, 20, "This is Page 2");
}

void drawPage3() {
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(10, 20, "This is Page 3");
}

void drawPage4() {
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(10, 20, "Counter Page");
  
  // Display the counter value
  u8g2.setCursor(10, 40);
  u8g2.print("Counter: ");
  u8g2.print(counter);
}

void drawPage5() {
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(10, 20, "This is Page 5");
}
