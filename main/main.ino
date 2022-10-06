/*
  ESP32 Sensores for The Things Network
  
  Main module

  Copyright (C) 2022 Marcos Rocha https://github.com/dev-marcos

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  //https://files.atlas-scientific.com/atlas_gravity.zip

*/
// Libraries for SD card
#include "FS.h"
#include "SD.h"
#include <SPI.h>
#include <Wire.h>
#include "configuration.h"


#ifdef PH_DEF      
  #if PH_DEF == 1 
    #include "ph_grav.h" 
    Gravity_pH gravityPH = Gravity_pH(PH_PIN); 
  #endif
#endif

#ifdef ORP_DEF
  #if ORP_DEF == 1
    #include "orp_grav.h" 
    Gravity_ORP gravityORP = Gravity_ORP(ORP_PIN);
  #endif
#endif

#ifdef DO_DEF
  #if DO_DEF == 1
    #include "do_grav.h"
    Gravity_DO gravityDO = Gravity_DO(DO_PIN);
  #endif
#endif


#ifdef TEMPERATURE_DEF
  #if TEMPERATURE_DEF = 1
    #include "DallasTemperature.h"
  #endif
#endif





//#include "EEPROM.h"
//#include "RTClib.h" 
// Libraries to get time from NTP Server
//#include <WiFi.h>
//#include <NTPClient.h>
//#include <WiFiUdp.h>



//#include "rom/rtc.h"
//#include <TinyGPS++.h>
//



// Save reading number on RTC memory
//RTC_DATA_ATTR int readingID = 0;


// Define NTP Client to get time
//WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP);

// Variables to save date and time
//String formattedDate;
//String dayStamp;
//String timeStamp;

struct sensors 
{
  #ifdef PH_DEF 
    float ph; 
  #endif
  #ifdef ORP_DEF 
    float orp;  
  #endif
  #ifdef DO_DEF 
    float dissolvedOxygen;  
  #endif
  #ifdef CONDUCTIVITY_DEF 
    float conductivity;  
  #endif
  #ifdef TURBIDITY_DEF 
    float turbidity  
  #endif
  #ifdef TEMPERATURE_DEF 
    float temperature;  
  #endif
  #ifdef FLOW_DEF 
    float flow;  
  #endif 
};


unsigned long LAST_LOG = 0; 

uint8_t user_bytes_received = 0;
const uint8_t bufferlen = 32;
char user_data[bufferlen];



void setup()
{
    // Debug
    #ifdef DEBUG_PORT
        DEBUG_PORT.begin(SERIAL_BAUD);
    #endif
    
    DEBUG_MSG(APP_NAME " " APP_VERSION "\n");

    pinMode(SD_CS, OUTPUT);
    digitalWrite(SD_CS, HIGH);

    Wire.begin(I2C_SDA, I2C_SCL);

    //dallasTemperature.begin();

    //setupSensors();

    // Initialize SD card
    setupSD();

    setupSensors();
    
    // Buttons & LED
    //pinMode(BUTTON_PIN, INPUT_PULLUP);

    #ifdef LED_PIN
        pinMode(LED_PIN, OUTPUT);
    #endif

    // Hello
    

   



   


/*#ifdef USE_LORAWAN
    // TTN setup
    if (!ttn_setup()) {
        screen_print("[ERR] Radio module not found!\n");

        if (REQUIRE_RADIO) {
            delay(MESSAGE_TO_SLEEP_DELAY);
            screen_off();
            sleep_forever();
        }
    }
    else {
        ttn_register(callback);
        ttn_join();
        ttn_adr(LORAWAN_ADR);
    }
#endif*/

/*
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");

  // Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(TIME_ZONE);*/


}




void loop() {
   if (Serial.available() > 0) {
    user_bytes_received = Serial.readBytesUntil(13, user_data, sizeof(user_data));
  }

  if (user_bytes_received) {
    parse_cmd(user_data);
    user_bytes_received = 0;
    memset(user_data, 0, sizeof(user_data));
  }

  
  if (LAST_LOG <= millis()){

    updateSensors();

    LAST_LOG = millis() + (LOG_RATE);
  }

  
  delay(1000);
}
