/*

ESP32 Sensores for The Things Network

Copyright (C) 2022 Marcos Rocha https://github.com/dev-marcos

This code requires LMIC library by Matthijs Kooijman
https://github.com/mcci-catena/arduino-lmic

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

*/

#pragma once

#include <Arduino.h>
//#include <lmic.h>
//void ttn_register(void (*callback)(uint8_t message));

// -----------------------------------------------------------------------------
// Version
// -----------------------------------------------------------------------------

#define APP_NAME                "ESP Sensors"
#define APP_VERSION             "1.0.0"

// -----------------------------------------------------------------------------
// Configuration
// -----------------------------------------------------------------------------


// Replace with your network credentials
//const char* ssid     = "";
//const char* password = "";

// Select the payload format. Change on TTN as well. Only uncomment one.
//#define PAYLOAD_USE_FULL
// #define PAYLOAD_USE_CAYENNE

// If using a single-channel gateway, uncomment this next option and set to your gateway's channel
//#define SINGLE_CHANNEL_GATEWAY  0



#define DEBUG_PORT              Serial          // Serial debug port
#define SERIAL_BAUD             115200          // Serial debug baud rate
#define SLEEP_BETWEEN_MESSAGES  false           // Do sleep between messages
#define SEND_INTERVAL           (20 * 1000)     // Sleep for these many millis
#define MESSAGE_TO_SLEEP_DELAY  5000            // Time after message before going to sleep
#define LOG_RATE                (5 * 60 * 1000)     // Interval for reading the sensors in millis
#define TIME_ZONE               -10800          // Brasilia time zone in seconds


/*
//#define USE_LORAWAN             false           // Enable LoraWAN
#define LOGO_DELAY              5000            // Time to show logo on first boot
#define LORAWAN_PORT            10              // Port the messages will be sent to
#define LORAWAN_CONFIRMED_EVERY 0               // Send confirmed message every these many messages (0 means never)
#define LORAWAN_SF              DR_SF7          // Spreading factor (recommended DR_SF7 for ttn network map purposes, DR_SF10 works for slow moving trackers)
#define LORAWAN_ADR             0               // Enable ADR
#define REQUIRE_RADIO           true            // If true, we will fail to start if the radio is not found
*/




// -----------------------------------------------------------------------------
// PINS
// -----------------------------------------------------------------------------
#define AN1 32
#define AN2 35
#define AN3 34

//RO 16 RX2
//RE 4
//DE 15
//DI 17 TX2


// -----------------------------------------------------------------------------
// BARRAMENTO I2C
// -----------------------------------------------------------------------------
#define I2C_SDA 21
#define I2C_SCL 22

// -----------------------------------------------------------------------------
// Cartao SD pinout
// -----------------------------------------------------------------------------
#define  SD_CS      5
#define  SD_MOSI    23
#define  SD_MISO    19
#define  SD_CLK     18


// -----------------------------------------------------------------------------
// SENSORS 
// -----------------------------------------------------------------------------
#define PH_DEF            1 // 1 = ph_grav  / 2 = DFRobot
#define ORP_DEF           1 // 1 = orp_grav / 2 = DFRobot
#define DO_DEF            1 // 1 = do_grav  / 2 = DFRobot
//#define CONDUCTIVITY_DEF  0
//#define TURBIDITY_DEF     0
//#define TEMPERATURE_DEF   0
//#define FLOW_DEF          0


// -----------------------------------------------------------------------------
// SENSORS PINS
// -----------------------------------------------------------------------------
#ifdef PH_DEF
#define PH_PIN            AN1
#endif

#ifdef ORP_DEF
#define ORP_PIN           AN2 
#endif

#ifdef DO_DEF
#define DO_PIN            AN3 
#endif


// -----------------------------------------------------------------------------
// DEBUG
// -----------------------------------------------------------------------------

#ifdef DEBUG_PORT
#define DEBUG_MSG(...) DEBUG_PORT.printf( __VA_ARGS__ )
#else
#define DEBUG_MSG(...)
#endif



/*
// -----------------------------------------------------------------------------
// Custom messages
// -----------------------------------------------------------------------------

#define EV_QUEUED       100
#define EV_PENDING      101
#define EV_ACK          102
#define EV_RESPONSE     103

// -----------------------------------------------------------------------------
// LoRa SPI
// -----------------------------------------------------------------------------

#define SCK_GPIO        5
#define MISO_GPIO       19
#define MOSI_GPIO       27
#define NSS_GPIO        18
#define RESET_GPIO      14

#define DIO0_GPIO       26
#define DIO1_GPIO       33 // Note: not really used on this board
#define DIO2_GPIO       32 // Note: not really used on this board
*/
