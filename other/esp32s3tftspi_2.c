#define TFT_CS   10
#define TFT_DC   8
#define TFT_RST  9
#define TFT_MOSI 13
#define TFT_SCLK 12

#define BIT(n) (1UL << (n))

#define GPIO_OUT_W1TS_REG  (*(volatile uint32_t *)0x60004008)
#define GPIO_OUT_W1TC_REG  (*(volatile uint32_t *)0x6000400C)
#define GPIO_ENABLE_REG    (*(volatile uint32_t *)0x60004020)

static inline void gpio_fast_set(uint8_t pin)  { GPIO_OUT_W1TS_REG = BIT(pin); }
static inline void gpio_fast_clr(uint8_t pin)  { GPIO_OUT_W1TC_REG = BIT(pin); }
static inline void gpio_fast_output(uint8_t p) { GPIO_ENABLE_REG |= BIT(p); }

static inline void sendByte_fast(uint8_t b) {
  uint8_t m = 0x80;
  do {
    if (b & m) gpio_fast_set(TFT_MOSI);
    else       gpio_fast_clr(TFT_MOSI);

    gpio_fast_clr(TFT_SCLK);
    gpio_fast_set(TFT_SCLK);

    m >>= 1;
  } while (m);
}

void writeCmd(uint8_t cmd) {
  gpio_fast_clr(TFT_DC);
  gpio_fast_clr(TFT_CS);
  sendByte_fast(cmd);
  gpio_fast_set(TFT_CS);
}

void writeData(uint8_t data) {
  gpio_fast_set(TFT_DC);
  gpio_fast_clr(TFT_CS);
  sendByte_fast(data);
  gpio_fast_set(TFT_CS);
}

void setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
  writeCmd(0x2A);
  writeData(x0 >> 8); writeData(x0 & 0xFF);
  writeData(x1 >> 8); writeData(x1 & 0xFF);

  writeCmd(0x2B);
  writeData(y0 >> 8); writeData(y0 & 0xFF);
  writeData(y1 >> 8); writeData(y1 & 0xFF);

  writeCmd(0x2C);
}

void tft_clear(uint16_t color) {
  setWindow(0, 0, 239, 319);
  gpio_fast_set(TFT_DC);
  gpio_fast_clr(TFT_CS);

  uint8_t ch = color >> 8;
  uint8_t cl = color & 0xFF;
  uint32_t total = 240UL * 320UL;

  while (total--) {
    sendByte_fast(ch);
    sendByte_fast(cl);
  }

  gpio_fast_set(TFT_CS);
}

void setup() {
  gpio_fast_output(TFT_CS);
  gpio_fast_output(TFT_DC);
  gpio_fast_output(TFT_RST);
  gpio_fast_output(TFT_MOSI);
  gpio_fast_output(TFT_SCLK);

  gpio_fast_set(TFT_RST);
  delay(10);
  gpio_fast_clr(TFT_RST);
  delay(10);
  gpio_fast_set(TFT_RST);
  delay(120);

  writeCmd(0x01); delay(120);
  writeCmd(0x11); delay(120);
  writeCmd(0x3A); writeData(0x55);
  writeCmd(0x36); writeData(0x48);
  writeCmd(0x29); delay(20);
}

void loop() {
  tft_clear(0x0000); // 黑
  delay(100);

  tft_clear(0xFFFF); // 白
  delay(100);

  tft_clear(0xF800); // 红
  delay(100);

  tft_clear(0x07E0); // 绿
  delay(100);

  tft_clear(0x001F); // 蓝
  delay(100);
}
