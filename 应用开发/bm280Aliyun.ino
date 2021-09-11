
#include <WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <ArduinoJson.h>
#include <AliyunIoTSDK.h>
AliyunIoTSDK iot;
WiFiClient   espClient;
//以下信息需要自己修改
#define WIFI_SSID        "5a517517"		//替换自己的WIFI
#define WIFI_PASSWD      "5a517517"		//替换自己的WIFI
#define PRODUCT_KEY      "a10UcGK3Uje" 	//替换自己的PRODUCT_KEY
#define DEVICE_NAME      "03nP762VYPr3QMW2" 	//替换自己的DEVICE_NAME
#define DEVICE_SECRET    "5fab37d7b9371c23a1b82b52eaf94ce6"//替换自己的DEVICE_SECRET
#define REGION_ID "cn-shanghai"

Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

int LedPin1 = 13;
int LedFlag1 = 0;
int LedPin2 = 26;
int LedFlag2 = 0;
 
void wifiInit(const char *ssid, const char *passphrase)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, passphrase);
    WiFi.setAutoConnect (true);
    WiFi.setAutoReconnect (true);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("WiFi not Connect");
    }
    Serial.println("Connected to AP");
    Serial.println("Local IP: ");
    Serial.println(WiFi.localIP());
}
  
void setup() {
  Serial.begin(115200);
  Serial.println("Demo Start");

  pinMode(LedPin2, OUTPUT);
  pinMode(LedPin1, OUTPUT);
  digitalWrite(LedPin1, HIGH);
   digitalWrite(LedPin2, HIGH);
  if (!bmp.begin(0x76)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1) delay(10);
  }
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  wifiInit(WIFI_SSID, WIFI_PASSWD);
  AliyunIoTSDK::begin(espClient, PRODUCT_KEY, DEVICE_NAME, DEVICE_SECRET, REGION_ID);
  // 绑定属性回调
  AliyunIoTSDK::bindData("LEDSwitch1", LedOnCallback1);
  AliyunIoTSDK::bindData("LEDSwitch2", LedOnCallback2);
  //mqttClient.setCallback(mqtt_callback);
}

unsigned long lastMsMain = 0;
void loop()
{
    sensors_event_t temp_event, pressure_event;
    AliyunIoTSDK::loop();
    if (millis() - lastMsMain >= 5000)
    {
        lastMsMain = millis();
        // 发送模型属性到阿里云平台
        bmp_temp->getEvent(&temp_event);
        AliyunIoTSDK::send("temperature", temp_event.temperature);
        bmp_pressure->getEvent(&pressure_event);
        AliyunIoTSDK::send("Atmosphere", pressure_event.pressure);
        AliyunIoTSDK::send("LEDSwitch1", LedFlag1);
        AliyunIoTSDK::send("LEDSwitch2", LedFlag2);
        
    }
}

void LedOnCallback1(JsonVariant p)
{
    serializeJsonPretty(p, Serial);
    int LedFlag1 = p["LEDSwitch1"];
    if (LedFlag1 == 1)
    {
        //turn on the led
        digitalWrite(LedPin1, LOW);
    }
    else
    {
        //turn off the led
        digitalWrite(LedPin1, HIGH);
    }
}
    
void LedOnCallback2(JsonVariant p)
{
    serializeJsonPretty(p, Serial);
    int LedFlag2= p["LEDSwitch2"];
    if (LedFlag2 == 1)
    {
        //turn on the led
        digitalWrite(LedPin2, LOW);
    }
    else
    {
        //turn off the led
        digitalWrite(LedPin2, HIGH);
    }
}
