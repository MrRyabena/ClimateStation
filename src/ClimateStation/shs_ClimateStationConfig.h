#pragma once


#include <shs_types.h>
#include <shs_CRC.h>
#include <shs_version.h>

namespace shs
{
    struct ClimateStationConfig;
};


struct shs::ClimateStationConfig
{
    // ----------------------------------INFO-----------------------------------
    shs::version::Version config_version = "v1.0.0";

    // ---------------------------------SENSORS---------------------------------

    // MHZ19
    shs::t::shs_pin_t MHZ19_TX_PIN = 17;
    shs::t::shs_pin_t MHZ19_RX_PIN = 35;

    // DHT
    shs::t::shs_pin_t DHT_PIN = 1;

    // flags
    /*
       See enum class shs::ClimateStation::SensorsNumbers
       MHZ19_b = 0b1, BME280_b = 0b10, DHT_b = 0b100,
       DS3231_b = 0b1000, NTP_b = 0b10000, UPDATING_TIMEOUT_b = 0b100000,
    */
    uint8_t sensors_flags = 0b11111;

    // -------------------------------INDICATION--------------------------------

    // TFT
    shs::t::shs_pin_t TFT_LED_PIN = 19;

    uint32_t SLEEP_TIMEOUT = 120'000;      // 2 minutes

    uint32_t SAVE_TIMEOUT = 300'000;           // every 5 minutes

    // Backlight (LED)
    uint16_t MIN_CO2 = 400u;
    uint16_t MAX_CO2 = 2200u;
    uint8_t  MIN_COLOR_H = 0;              // red
    uint8_t  MAX_COLOR_H = 90;             // green

};
