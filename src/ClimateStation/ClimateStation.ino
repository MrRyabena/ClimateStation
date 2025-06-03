#include "settings.h"

#include <shs_settings_private.h>

#include <shs_ProgramTimer.h>

#include <memory>

#include "shs_ClimateStation.h"
#include "shs_ClimateStationVisualizer.h"
#include "shs_ClimateStationStorage.h"
#include "shs_ClimateStationConfig.h"
#include "ClimateStationGUIcore.h"
#include "shs_SDCard.h"
#include "UpdateWindow.h"

#include <SPI.h>
#include <TFT_eSPI.h>       // https://github.com/Bodmer/TFT_eSPI


#include <shs_ControlWiFi.h>
#include <shs_ProgramTimer.h>
#include <shs_utils.h>
#include <GyverNTP.h>

std::shared_ptr<TFT_eSPI> tft_ptr;

std::shared_ptr<shs::ClimateStationStorage> storage;
std::shared_ptr<shs::ClimateStation> climate_station;
std::shared_ptr<shs::ClimateStationVisualizer> climate_station_visualizer;


CRGB leds[LEDS_NUM]{};

#include <AutoOTA.h>
void checkUpdate();

void setup()
{
    // WiFi
    shs::ControlWiFi::connectWiFi();

    
    SPI.begin(SD_SCK, SD_MISO, SD_MOSI);
        
    tft_ptr = std::make_shared<TFT_eSPI>();

    // Storage

    storage = std::make_shared<shs::ClimateStationStorage>(SD_CS);
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
