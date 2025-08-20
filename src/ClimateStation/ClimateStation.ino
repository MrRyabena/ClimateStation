#include "settings.h"

#include <shs_settings_private.h>

#include <shs_ProgramTimer.h>

#include <memory>

#include "shs_ClimateStation.h"
#include "shs_ClimateStationVisualizer.h"
#include "shs_ClimateStationStorage.h"
#include "shs_ClimateStationConfig.h"
#include "ClimateStationGUIcore.h"
#include "UpdateWindow.h"

#include <SPI.h>
#include <TFT_eSPI.h>       // https://github.com/Bodmer/TFT_eSPI


#include <shs_ControlWiFi.h>
#include <shs_ProgramTimer.h>
#include <shs_utils.h>
#include <GyverNTP.h>
#include <LittleFS.h>

std::shared_ptr<TFT_eSPI> tft_ptr;

std::shared_ptr<shs::ClimateStationStorage> storage;
std::shared_ptr<shs::ClimateStation> climate_station;
std::shared_ptr<shs::ClimateStationVisualizer> climate_station_visualizer;


CRGB leds[LEDS_NUM]{};

#include <AutoOTA.h>
void checkUpdate();

void setup()
{
    // dinit();
    // WiFi
    //shs::ControlWiFi::connectWiFi();
    shs::ControlWiFi::connectWiFiMulti();
    delay(500);


    pinMode(1, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(15, OUTPUT);
    pinMode(33, OUTPUT);

    digitalWrite(1, HIGH); 
    digitalWrite(15, HIGH);
    digitalWrite(33, HIGH);
        
    tft_ptr = std::make_shared<TFT_eSPI>();

    // Storage
    LittleFS.begin();

    //SDspi.begin(SD_SCK, SD_MISO, SD_MOSI);
    storage = std::make_shared<shs::ClimateStationStorage>(LittleFS);
    storage->start();
    
    climate_station = std::make_shared<shs::ClimateStation>(storage);
    climate_station->start();


    FastLED.addLeds<WS2812B, LEDS_PIN, RGB>(leds, LEDS_NUM);  // GRB ordering is typical
    FastLED.setMaxPowerInMilliWatts(1500);

    climate_station_visualizer = std::make_shared<shs::ClimateStationVisualizer>(
    climate_station,
    storage,
    tft_ptr, storage->cs_config.TFT_LED_PIN, LEDS_NUM, LEDS_PIN
    );


    climate_station_visualizer->start();

    checkUpdate();


    climate_station_visualizer->enable();
}



void loop()
{
    storage->tick();
    climate_station->tick();
    climate_station_visualizer->tick();
}


void checkUpdate()
{
    shs::UpdateWindow window(tft_ptr, CLIMATE_STATION_ESP32_VERSION);
    window.start();
}
