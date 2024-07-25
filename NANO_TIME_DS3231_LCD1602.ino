#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

// 定义LCD的I²C地址
#define LCD_ADDR 0x27

// 创建LCD对象
LiquidCrystal_I2C lcd(LCD_ADDR, 16, 2);

// 创建RTC对象
RTC_DS3231 rtc;

void setup() {
  // 初始化串口用于调试输出
  Serial.begin(9600);
  
  // 初始化LCD
  lcd.init();
  
  // 开启背光
  lcd.backlight();
  
  // 清屏
  lcd.clear();
  
  // 初始化RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
  // 设置RTC的时间和日期，格式为：year, month, day, weekday, hour, minute, second
  rtc.adjust(DateTime(2024, 7, 25, 21, 55, 34)); // 示例时间
  
  // 显示初始化信息
  lcd.setCursor(0, 0);
  lcd.print("RTC Time Display");
  
  delay(2000);
  
  // 清屏
  lcd.clear();
}

void loop() {
  // 读取RTC的时间
  DateTime now = rtc.now();
  
  // 读取温度
  float temperature = rtc.getTemperature();
  
  // 显示时间
  lcd.setCursor(4, 0);
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute());
  lcd.print(":");
  lcd.print(now.second());
  
  // 显示日期
  lcd.setCursor(0, 1);
  lcd.print(now.year());
  lcd.print("/");
  lcd.print(now.month());
  lcd.print("/");
  lcd.print(now.day());

  // 显示温度
  lcd.setCursor(10, 1); // 假设LCD是16x2的，从第11个位置开始显示温度
  lcd.print(" ");
  lcd.print(temperature, 1); // 显示温度，保留一位小数
  lcd.print("C");
  
  // 等待一段时间再刷新显示
  delay(1000);
}