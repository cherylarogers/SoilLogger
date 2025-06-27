
// WIRING //

// Arduino 5V   →  VCC on RTC, SD card module, RS485 module
// Arduino GND  →  GND on RTC, SD card module, RS485 module, and sensor

// RTC MODULE //
// RTC SDA  →  Arduino A4
// RTC SCL  →  Arduino A5
// RTC VCC  →  Arduino 5V
// RTC GND  →  Arduino GND

// SD Card Module //
// SD CS     →  Arduino D4 (or D10 if not using other SPI devices)
// SD MOSI   →  Arduino D11
// SD MISO   →  Arduino D12
// SD SCK    →  Arduino D13
// SD VCC    →  Arduino 5V
// SD GND    →  Arduino GND

// RS485 Module //
// RS485 RO  (Receiver Out)    →  Arduino D8 (SoftwareSerial RX)
// RS485 DI  (Driver In)       →  Arduino D9 (SoftwareSerial TX)
// RS485 DE  (Driver Enable)   →  Arduino D2
// RS485 RE  (Receiver Enable) →  Arduino D3
// RS485 VCC                   →  Arduino 5V
// RS485 GND                   →  Arduino GND

//DFROBOT SEN0601 Sensor: docs https://wiki.dfrobot.com/RS485_Soil_Sensor_Temperature_Humidity_EC_SKU_SEN0601 //
// Sensor A  →  RS485 A
// Sensor B  →  RS485 B
// Sensor VCC  →  5V (DFROBOT SEN0601 needs between 5V and 24V)
// Sensor GND  →  GND


// Required libraries //
#include <SoftwareSerial.h>
#include <RTClib.h>
#include <SD.h>

// RS485 control pins
#define DE_PIN 2
#define RE_PIN 3
#define SD_CS 4

// Command to read: Temp, Moisture, EC
uint8_t Com[8] = { 0x01, 0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB };

// Initialize global variables
float temperatureValue[3]; //This holds Temp, Humidity, and EC in real units
byte temperatureBuffer[11]; //This holds the unprocessed output from the sensor

SoftwareSerial RS485Serial(8, 9); // RX, TX
RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  RS485Serial.begin(9600);

  pinMode(DE_PIN, OUTPUT);
  pinMode(RE_PIN, OUTPUT);
  digitalWrite(DE_PIN, LOW);
  digitalWrite(RE_PIN, LOW);

  // Init RTC
  if (!rtc.begin()) {
    Serial.println("RTC not found!");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power. Setting time to compile time.");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Init SD card
  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("SD card failed or not present.");
    while (1);
  }
  Serial.println("Card initialized.");
  // Write to SD card
    File logFile = SD.open("logdata.txt", FILE_WRITE);
    if (logFile) {
      logFile.println(String("Date, Time, Temperature (C), Soil Moisture (%), Electrical Conductivity (μS/cm)"));
      logFile.close();
      Serial.println("Header string logged.\n");
    } else {
      Serial.println("Failed to open log file.");
    }
  }


void loop() {
  if (getTemperature()) {
    DateTime now = rtc.now();
    
    // Print to Serial
    for (uint8_t j = 0; j < 11; j++) {Serial.print(temperatureBuffer[j],HEX); Serial.print(" ");};
    Serial.println();
    Serial.print("Soil T: "); Serial.print(temperatureValue[0] / 10.0); Serial.println(" °C");
    Serial.print("Soil M: "); Serial.print(temperatureValue[1] / 10.0); Serial.println(" %RH");
    Serial.print("Soil EC: "); Serial.print(temperatureValue[2]); Serial.println(" μS/cm");

    // Format time
    String init;
    char timestamp[25];
    sprintf(timestamp, "%04d/%02d/%02d,%02d:%02d:%02d",
        now.year(), now.month(), now.day(),
        now.hour(), now.minute(), now.second());
    Serial.println(timestamp);

    // Format data
    String dataString = init + timestamp + ", " +
                        String(temperatureValue[0] / 10.0) + ", " +
                        String(temperatureValue[1] / 10.0) + " , " +
                        String(temperatureValue[2]);

    // Write to SD card
    File logFile = SD.open("logdata.txt", FILE_WRITE);
    if (logFile) {
      logFile.println(dataString);
      logFile.close();
      Serial.println("Data logged.\n");
    } else {
      Serial.println("Failed to open log file.");
    }
  }

  delay(2000);
}

// Returns true if CRC check passed and values were stored
bool getTemperature() {
  while (RS485Serial.available()) RS485Serial.read();

  digitalWrite(DE_PIN, HIGH);
  digitalWrite(RE_PIN, HIGH);
  delay(10);
  RS485Serial.write(Com, 8);
  digitalWrite(DE_PIN, LOW);
  digitalWrite(RE_PIN, LOW);
  delay(10);

  byte i = 0;
  unsigned long start = millis();
  while (i < 11 && millis() - start < 1000) {
    if (RS485Serial.available()) {
      temperatureBuffer[i++] = RS485Serial.read();
    }
  }

  if (i < 11) {
    Serial.println("Incomplete response.");
    return false;
  }

  // CRC check
  uint16_t crcCalc = calculateCRC(temperatureBuffer, 9);
  uint16_t crcRecv = (temperatureBuffer[10] << 8) | temperatureBuffer[9];
  if (crcCalc != crcRecv) {
    Serial.println("CRC check failed!");
    return false;
  }

  // Parse values
  int16_t temp = (temperatureBuffer[5] << 8) | temperatureBuffer[6];
  uint16_t hum = (temperatureBuffer[3] << 8) | temperatureBuffer[4];
  uint16_t ec = (temperatureBuffer[7] << 8) | temperatureBuffer[8];

  temperatureValue[0] = temp;
  temperatureValue[1] = hum;
  temperatureValue[2] = ec;
  Serial.println("CRC check passed.");
  return true;
}

uint16_t calculateCRC(uint8_t *data, uint8_t length) {
  uint16_t crc = 0xFFFF;
  for (uint8_t i = 0; i < length; i++) {
    crc ^= data[i];
    for (uint8_t j = 0; j < 8; j++) {
      if (crc & 0x0001) {
        crc >>= 1;
        crc ^= 0xA001;
      } else {
        crc >>= 1;
      }
    }
  }
  return crc;
}
