# GIF2CPP

Convert GIF animations into C/C++ arrays for display on monochrome OLED/LCD screens.

![Version](https://img.shields.io/badge/version-1.0.0-blue?style=flat)&nbsp;![License](https://img.shields.io/badge/license-MIT-green?style=flat)

## Table of Contents

• [Overview](#overview)
• [Key Features](#key-features)
• [Prerequisites](#prerequisites)
• [Installation](#installation)
• [Usage](#usage)
  1. [Upload GIF](#1-upload-gif)
  2. [Configure Output](#2-configure-output)
  3. [Adjust Image](#3-adjust-image)
  4. [Convert & Copy Code](#4-convert--copy-code)
  5. [Download Header File](#5-download-header-file)
• [Supported Output Formats](#supported-output-formats)
• [Integration Example](#integration-example)
• [Directory Structure](#directory-structure)
• [Contributing](#contributing)
• [License](#license)
• [Author](#author)

---

## Overview

**GIF2CPP** is a web-based tool that processes multi-frame GIF files and generates C/C++ arrays ready for embedding into microcontroller projects (ESP32, Arduino, etc.) to animate on monochrome displays.

This project leverages [image2cpp](https://github.com/javl/image2cpp) and [libgif-js](https://github.com/buzzfeed/libgif-js) under the hood, extending support to full GIF animations.

---

## Key Features

• Live preview of GIF frames in your browser
• Threshold, scaling, inversion, flip, and rotation controls
• Three drawing modes: `horizontal`, `vertical`, and `horizontal_bytes`
• Export code in Arduino, plain C/C++, or ESP8266/ESP32 formats
• One-click copy to clipboard or download as a `.h` header file

--

## Usage

### 1. Upload GIF

• Click **Choose File** and select your `.gif` file.
• The variable name auto-populates from the file name.

### 2. Configure Output

• **Canvas Size**: Enter width and height matching your display.
• **Draw Mode**: Select `Horizontal`, `Vertical`, or `Horizontal Bytes`.

### 3. Adjust Image

• **Threshold**: Set the luminance cutoff for black-and-white conversion.
• **Scale**: Options: `fit`, `fit_width`, `fit_height`, or `custom`.
• **Invert Colors**: Toggle for negative effect.
• **Flip / Rotate**: Flip horizontally/vertically or rotate 0°/90°/180°/270°.

### 4. Convert & Copy Code

• Click **Convert GIF** to generate code.
• View code in the output pane.
• Click **Copy** to copy all code to clipboard.

### 5. Copy output or Download Header File
• You can simply copy output code to use anywhere, there is a function comment out at the bottom of the code or:
• Click **Save as .h** to download a header file containing
• Then use this code to display gif which design to display many gif with one function:
```cpp
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

```
---

## Supported Output Formats

| Format       | Description                                        |
| ------------ | -------------------------------------------------- |
| Arduino      | `PROGMEM const uint8_t` arrays                     |
| Plain C/C++  | `const uint8_t` arrays                             |
| ESP32/ESP8266| `ICACHE_RODATA_ATTR` for flash-resident data       |

---

## Integration Example

Please check "src/main.cpp"


---

## Contributing

Contributions are welcome! Please open issues or pull requests on [GitHub](https://github.com/<your-username>/gif2cpp).

---

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

---

## Author

**Huykhong** • [GitHub](https://github.com/huykhoong) • hello@huykhong.com

