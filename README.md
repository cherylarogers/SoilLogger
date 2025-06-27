Parts List: </br>
DFRobot SEN0601 Soil Moisture, Temperature, and Electrical Conductivity Sensor: https://www.dfrobot.com/product-2817.html?srsltid=AfmBOopVAFm2FJkAC2ND2kJ8A9Ufb6X18eEhR8P3MBJBMhrqkQRtu3Hd</br>
Arduino Nano or similar: https://www.amazon.ca/dp/B0816SGKHH?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_2</br>
Real Time Clock Module: https://www.amazon.ca/dp/B07V68443F?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_1</br>
MicroSD Card Module: https://www.amazon.ca/dp/B07V78MD81?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_3</br>
MAX485 Module: https://www.amazon.ca/dp/B01N8WLEV0?ref=ppx_yo2ov_dt_b_fed_asin_title</br>
</br>
</br>
WIRING</br>
Arduino 5V   →  VCC on RTC, SD card module, RS485 module</br>
Arduino GND  →  GND on RTC, SD card module, RS485 module, and sensor</br>
</br>
</br>
RTC MODULE</br>
RTC SDA  →  Arduino A4</br>
RTC SCL  →  Arduino A5</br>
RTC VCC  →  Arduino 5V</br>
RTC GND  →  Arduino GND</br>
</br>
</br>
SD Card Module</br>
SD CS     →  Arduino D4</br>
SD MOSI   →  Arduino D11</br>
SD MISO   →  Arduino D12</br>
SD SCK    →  Arduino D13</br>
SD VCC    →  Arduino 5V</br>
SD GND    →  Arduino GND</br>
</br>
</br>
RS485 Module</br>
RS485 RO  (Receiver Out)    →  Arduino D8 (SoftwareSerial RX)</br>
RS485 DI  (Driver In)       →  Arduino D9 (SoftwareSerial TX)</br>
RS485 DE  (Driver Enable)   →  Arduino D2</br>
RS485 RE  (Receiver Enable) →  Arduino D3</br>
RS485 VCC                   →  Arduino 5V</br>
RS485 GND                   →  Arduino GND</br>
</br>
</br>
DFROBOT SEN0601 Sensor: docs https://wiki.dfrobot.com/RS485_Soil_Sensor_Temperature_Humidity_EC_SKU_SEN0601</br>
Sensor A  →  RS485 A</br>
Sensor B  →  RS485 B</br>
Sensor VCC  →  5V (DFROBOT SEN0601 needs between 5V and 24V)</br>
Sensor GND  →  GND</br>
