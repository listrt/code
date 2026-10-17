// ==========================================
// 引脚定义（必须核对无误）
// ==========================================
#define TFT_CS   10   
#define TFT_DC   8    
#define TFT_RST  9    
#define TFT_MOSI 13   
#define TFT_SCLK 12   

void setup() {
  // 1. 引脚初始化
  pinMode(TFT_CS, OUTPUT);
  pinMode(TFT_DC, OUTPUT);
  pinMode(TFT_RST, OUTPUT);
  pinMode(TFT_MOSI, OUTPUT);
  pinMode(TFT_SCLK, OUTPUT);

  // 2. 硬件复位
  digitalWrite(TFT_RST, HIGH); delay(10);
  digitalWrite(TFT_RST, LOW);  delay(10);
  digitalWrite(TFT_RST, HIGH); delay(120);

  // 辅助宏：手动发送一个字节
  // 别嫌乱，这样写绝对不会报错
  #define SEND_BYTE(b) do { \
    uint8_t _t = (b); \
    for (int _i = 0; _i < 8; _i++) { \
      if (_t & 0x80) digitalWrite(TFT_MOSI, HIGH); else digitalWrite(TFT_MOSI, LOW); \
      digitalWrite(TFT_SCLK, LOW); digitalWrite(TFT_SCLK, HIGH); \
      _t <<= 1; \
    } \
  } while(0)

  // 辅助宏：发送命令
  #define WRITE_CMD(c) do { \
    digitalWrite(TFT_DC, LOW); digitalWrite(TFT_CS, LOW); \
    SEND_BYTE(c); \
    digitalWrite(TFT_CS, HIGH); \
  } while(0)

  // 辅助宏：发送数据
  #define WRITE_DATA(d) do { \
    digitalWrite(TFT_DC, HIGH); digitalWrite(TFT_CS, LOW); \
    SEND_BYTE(d); \
    digitalWrite(TFT_CS, HIGH); \
  } while(0)

  // 3. ILI9341 标准初始化序列
  WRITE_CMD(0x01); delay(120); // 软复位
  WRITE_CMD(0x11); delay(120); // 退出睡眠
  
  // 电源控制
  WRITE_CMD(0xCF); WRITE_DATA(0x00); WRITE_DATA(0xC1); WRITE_DATA(0x30);
  WRITE_CMD(0xED); WRITE_DATA(0x64); WRITE_DATA(0x03); WRITE_DATA(0x12); WRITE_DATA(0x81);
  WRITE_CMD(0xE8); WRITE_DATA(0x85); WRITE_DATA(0x00); WRITE_DATA(0x78);
  WRITE_CMD(0xCB); WRITE_DATA(0x39); WRITE_DATA(0x2C); WRITE_DATA(0x00); WRITE_DATA(0x34); WRITE_DATA(0x02);
  WRITE_CMD(0xF7); WRITE_DATA(0x20);
  WRITE_CMD(0xEA); WRITE_DATA(0x00); WRITE_DATA(0x00);
  
  // 驱动时序
  WRITE_CMD(0xC0); WRITE_DATA(0x23); // Power control 1
  WRITE_CMD(0xC1); WRITE_DATA(0x10); // Power control 2
  WRITE_CMD(0xC5); WRITE_DATA(0x3e); WRITE_DATA(0x28); // VCOM Control
  WRITE_CMD(0xC7); WRITE_DATA(0x86); // VCOM Control 2
  
  // 内存访问控制 (这里设置为横屏)
  WRITE_CMD(0x36); WRITE_DATA(0x28); // 0x28 是横屏，竖屏是 0x48
  
  // 像素格式
  WRITE_CMD(0x3A); WRITE_DATA(0x55); // 16位 RGB565
  
  // 帧率控制
  WRITE_CMD(0xB1); WRITE_DATA(0x00); WRITE_DATA(0x18);
  
  // 显示功能控制
  WRITE_CMD(0xB6); WRITE_DATA(0x08); WRITE_DATA(0x82); WRITE_DATA(0x27);
  
  // Gamma 校正
  WRITE_CMD(0xF2); WRITE_DATA(0x00);
  WRITE_CMD(0x26); WRITE_DATA(0x01);
  WRITE_CMD(0xE0); 
  WRITE_DATA(0x0F); WRITE_DATA(0x31); WRITE_DATA(0x2B); WRITE_DATA(0x0C); 
  WRITE_DATA(0x0E); WRITE_DATA(0x08); WRITE_DATA(0x4E); WRITE_DATA(0xF1); 
  WRITE_DATA(0x37); WRITE_DATA(0x07); WRITE_DATA(0x10); WRITE_DATA(0x03); 
  WRITE_DATA(0x0E); WRITE_DATA(0x09); WRITE_DATA(0x00);
  
  WRITE_CMD(0xE1);
  WRITE_DATA(0x00); WRITE_DATA(0x0E); WRITE_DATA(0x14); WRITE_DATA(0x03); 
  WRITE_DATA(0x11); WRITE_DATA(0x07); WRITE_DATA(0x31); WRITE_DATA(0xC1); 
  WRITE_DATA(0x48); WRITE_DATA(0x08); WRITE_DATA(0x0F); WRITE_DATA(0x0C); 
  WRITE_DATA(0x31); WRITE_DATA(0x36); WRITE_DATA(0x0F);
  
  WRITE_CMD(0x11); delay(120); // 再次退出睡眠
  WRITE_CMD(0x29); delay(20);  // 开启显示

  // ==========================================
  // 4. 强行刷屏（刷成蓝色）
  // 设置列地址 (X): 0 到 239
  WRITE_CMD(0x2A); 
  WRITE_DATA(0x00); WRITE_DATA(0x00); // 起始 0
  WRITE_DATA(0x00); WRITE_DATA(0xEF); // 结束 239
  
  // 设置行地址 (Y): 0 到 319
  WRITE_CMD(0x2B); 
  WRITE_DATA(0x00); WRITE_DATA(0x00); // 起始 0
  WRITE_DATA(0x01); WRITE_DATA(0x3F); // 结束 319
  
  // 开始写入数据
  WRITE_CMD(0x2C);
  
  digitalWrite(TFT_CS, LOW);
  digitalWrite(TFT_DC, HIGH); // 数据模式
  
  // 循环写入 240 * 320 = 76800 个像素点
  for (uint32_t i = 0; i < 76800; i++) {
    uint8_t tempH = 0x00; // 蓝色高8位
    for(int b=0; b<8; b++) { if(tempH & 0x80) digitalWrite(TFT_MOSI, HIGH); else digitalWrite(TFT_MOSI, LOW); digitalWrite(TFT_SCLK, LOW); digitalWrite(TFT_SCLK, HIGH); tempH <<= 1; }
    uint8_t tempL = 0x1F; // 蓝色低8位
    for(int b=0; b<8; b++) { if(tempL & 0x80) digitalWrite(TFT_MOSI, HIGH); else digitalWrite(TFT_MOSI, LOW); digitalWrite(TFT_SCLK, LOW); digitalWrite(TFT_SCLK, HIGH); tempL <<= 1; }
  }
  digitalWrite(TFT_CS, HIGH);
}

void loop() {
  // 留空
}
