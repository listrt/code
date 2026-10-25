#include <WiFi.h>

// ===== TFT 引脚 =====
#define TFT_CS   10
#define TFT_DC   8
#define TFT_RST  9
#define TFT_MOSI 13
#define TFT_SCLK 12

// ===== Wi-Fi 配置 =====
const char* ssid     = "507";
const char* password = "LTT168@269";

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
  gpio_fast_clr(TFT_DC); gpio_fast_clr(TFT_CS);
  sendByte_fast(cmd);
  gpio_fast_set(TFT_CS);
}

void writeData(uint8_t data) {
  gpio_fast_set(TFT_DC); gpio_fast_clr(TFT_CS);
  sendByte_fast(data);
  gpio_fast_set(TFT_CS);
}

void setWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
  writeCmd(0x2A); writeData(x0 >> 8); writeData(x0 & 0xFF); writeData(x1 >> 8); writeData(x1 & 0xFF);
  writeCmd(0x2B); writeData(y0 >> 8); writeData(y0 & 0xFF); writeData(y1 >> 8); writeData(y1 & 0xFF);
  writeCmd(0x2C);
}

void tft_fillRect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {
  setWindow(x0, y0, x1, y1);
  gpio_fast_set(TFT_DC); gpio_fast_clr(TFT_CS);
  uint8_t ch = color >> 8, cl = color & 0xFF;
  uint32_t total = (uint32_t)(x1 - x0 + 1) * (y1 - y0 + 1);
  while (total--) {
    sendByte_fast(ch); sendByte_fast(cl);
  }
  gpio_fast_set(TFT_CS);
}

void tft_init() {
  gpio_fast_output(TFT_CS); gpio_fast_output(TFT_DC); gpio_fast_output(TFT_RST);
  gpio_fast_output(TFT_MOSI); gpio_fast_output(TFT_SCLK);

  gpio_fast_set(TFT_RST); delay(10);
  gpio_fast_clr(TFT_RST); delay(10);
  gpio_fast_set(TFT_RST); delay(120);

  writeCmd(0x01); delay(120);
  writeCmd(0x11); delay(120);
  writeCmd(0x3A); writeData(0x55);
  writeCmd(0x36); writeData(0x00); // 沿用刚刚测试成功的方向
  writeCmd(0x29); delay(20);
}

void setup() {
  Serial.begin(115200);
  delay(1500);
  Serial.println("\n=== SYSTEM BOOT ===");

  // 1. 初始化屏幕
  tft_init();
  // 先把全屏刷成黑色（稍微耗点电，但只刷一次），作为背景
  tft_fillRect(0, 0, 239, 319, 0x0000); 
  // 画一个蓝色的状态方块在左上角
  tft_fillRect(0, 0, 19, 19, 0x001F); 
  Serial.println("Screen Init Done. Status Box: BLUE");

  // 2. 延时，让供电稳住
  delay(2000);

  // 3. 温柔地启动 Wi-Fi
  Serial.printf("Connecting to WiFi: %s\n", ssid);
  WiFi.mode(WIFI_STA);
  WiFi.setTxPower(WIFI_POWER_8_5dBm); // 降低发射功率，保供电
  WiFi.setSleep(false);               // 关闭休眠，保连接稳定
  WiFi.begin(ssid, password);
}

void loop() {
  static int lastState = -1;
  static unsigned long lastCheck = 0;

  if (millis() - lastCheck > 1000) {
    lastCheck = millis();
    bool connected = (WiFi.status() == WL_CONNECTED);
    int state = connected ? 1 : 0;

    if (state != lastState) {
      lastState = state;
      if (connected) {
        Serial.println("\nWiFi Connected!");
        Serial.print("IP: "); Serial.println(WiFi.localIP());
        tft_fillRect(0, 0, 19, 19, 0xF800);  // 变红
      } else {
        Serial.println("\nWiFi Disconnected.");
        tft_fillRect(0, 0, 19, 19, 0x001F);  // 变蓝
      }
    }
  }

  // 如果断开，后台重连
  if (WiFi.status() != WL_CONNECTED) {
    static unsigned long lastTry = 0;
    if (millis() - lastTry > 5000) {
      lastTry = millis();
      WiFi.disconnect();
      WiFi.begin(ssid, password);
    }
  }
}
