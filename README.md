//Parts List://

DFRobot SEN0601 Soil Moisture, Temperature, and Electrical Conductivity Sensor: https://www.dfrobot.com/product-2817.html?srsltid=AfmBOopVAFm2FJkAC2ND2kJ8A9Ufb6X18eEhR8P3MBJBMhrqkQRtu3Hd
Arduino Nano or similar: https://www.amazon.ca/dp/B0816SGKHH?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_2
Real Time Clock Module: https://www.amazon.ca/dp/B07V68443F?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_1
MicroSD Card Module: https://www.amazon.ca/dp/B07V78MD81?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_3
MAX485 Module: https://www.amazon.ca/dp/B01N8WLEV0?ref=ppx_yo2ov_dt_b_fed_asin_title


// WIRING //

Arduino 5V   →  VCC on RTC, SD card module, RS485 module
Arduino GND  →  GND on RTC, SD card module, RS485 module, and sensor

// RTC MODULE //
RTC SDA  →  Arduino A4
RTC SCL  →  Arduino A5
RTC VCC  →  Arduino 5V
RTC GND  →  Arduino GND

// SD Card Module //
SD CS     →  Arduino D4 (or D10 if not using other SPI devices)
SD MOSI   →  Arduino D11
SD MISO   →  Arduino D12
SD SCK    →  Arduino D13
SD VCC    →  Arduino 5V
SD GND    →  Arduino GND

// RS485 Module //
RS485 RO  (Receiver Out)    →  Arduino D8 (SoftwareSerial RX)
RS485 DI  (Driver In)       →  Arduino D9 (SoftwareSerial TX)
RS485 DE  (Driver Enable)   →  Arduino D2
RS485 RE  (Receiver Enable) →  Arduino D3
RS485 VCC                   →  Arduino 5V
RS485 GND                   →  Arduino GND

//DFROBOT SEN0601 Sensor: docs https://wiki.dfrobot.com/RS485_Soil_Sensor_Temperature_Humidity_EC_SKU_SEN0601 //
Sensor A  →  RS485 A
Sensor B  →  RS485 B
Sensor VCC  →  5V (DFROBOT SEN0601 needs between 5V and 24V)
Sensor GND  →  GND
