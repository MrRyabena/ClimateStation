#pragma once

// #define DEBUG
#include <shs_settings.h>

#define CLIMATE_STATION_ESP32_VERSION "1.0.6"

#define SHS_CS_DEFAULT_TBOT_TOKEN CS_TBOT_VVR_TOKEN
// CS_TBOT_KULIC_TOKEN 
// CS_TBOT_VVR_TOKEN

static constexpr auto LEDS_NUM = 9 * 5;
static constexpr auto LEDS_PIN = 16;

static constexpr auto SD_CS = 1;
static constexpr auto SD_MOSI = 23;
static constexpr auto SD_MISO = 34;
static constexpr auto SD_SCK = 18;

