#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "myGif.h"
#include "cat398.h"
#include "cat412.h"
#include "giphy.h"
#include "vegeta.h"
#include "vegeta_inverse.h"
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Hàm tổng quát để hiển thị GIF
void playGIF(const AnimatedGIF* gif, uint16_t loopCount = 1) {
  for (uint16_t loop = 0; loop < loopCount; loop++) {
    for (uint8_t frame = 0; frame < gif->frame_count; frame++) {
        display.clearDisplay();
        
        // Hiển thị khung hình hiện tại
        for (uint16_t y = 0; y < gif->height; y++) {
            for (uint16_t x = 0; x < gif->width; x++) {
                uint16_t byteIndex = y * (((gif->width + 7) / 8)) + (x / 8);
                uint8_t bitIndex = 7 - (x % 8);
                if (gif->frames[frame][byteIndex] & (1 << bitIndex)) {
                    display.drawPixel(x, y, WHITE);
                }
            }
        }
        
        display.display();
        delay(gif->delays[frame]);
    }
  }
}

void playGIFWithText(const AnimatedGIF* gif, const char* text, int textX, int textY) {
  for (uint8_t frame = 0; frame < gif->frame_count; frame++) {
      // Chỉ xóa vùng GIF, không xóa toàn bộ màn hình
      for (uint16_t y = 0; y < gif->height; y++) {
          for (uint16_t x = 0; x < gif->width; x++) {
              display.drawPixel(x, y, BLACK); // Xóa pixel trong vùng GIF
          }
      }
      
      // Hiển thị khung hình hiện tại
      for (uint16_t y = 0; y < gif->height; y++) {
          for (uint16_t x = 0; x < gif->width; x++) {
              uint16_t byteIndex = y * (((gif->width + 7) / 8)) + (x / 8);
              uint8_t bitIndex = 7 - (x % 8);
              if (gif->frames[frame][byteIndex] & (1 << bitIndex)) {
                  display.drawPixel(x, y, WHITE);
              }
          }
      }
      
      // Hiển thị text cố định
      display.setTextColor(WHITE);
      display.setCursor(textX, textY);
      display.print(text);
      
      // Cập nhật màn hình
      display.display();
      delay(gif->delays[frame]);
  }
}

void display_text(const char* text){
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(10, 20);
  display.print(text);
  display.display();
}

void display_image() {
    display.clearDisplay();
    
    playGIF(&myGif_gif);
    
    display.display();
}

void setup() {
    Wire.begin(21, 22);
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("SSD1306 init failed!");
        while(1);
    }
    
    // Hiển thị hình ảnh thay vì test_display()
    display_image();
}

void loop() {
  display_text("This is a gif with text");
  delay(1000);
  playGIFWithText(&cat398_gif, "Hello anh em", 10, 10);
  delay(50); // Thời gian nghỉ giữa các lần phát lại
  playGIFWithText(&cat412_gif, "Chao anh em nha", 10, 40);
  delay(50); // Thời gian nghỉ giữa các lần phát lại
  playGIF(&giphy_gif);
  delay(50); // Thời gian nghỉ giữa các lần phát lại
  playGIF(&giphy_gif);
  delay(50); // Thời gian nghỉ giữa các lần phát lại
  playGIF(&giphy_gif);
  display_text("This is vegeta");
  delay(1000);
  playGIF(&vegeta_gif);
  display_text("..and inverse color");
  delay(1000);
  playGIF(&vegeta_inverse_gif);
}
