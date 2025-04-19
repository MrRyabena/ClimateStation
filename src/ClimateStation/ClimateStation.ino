#include "settings.h"

#define DEBUG
#define SHS_SF_DEBUG

#include <shs_debug.h>

#include <memory>

#include "shs_ClimateStation.h"
#include "shs_ClimateStationVisualizer.h"

#include <SPI.h>
#include <TFT_eSPI.h>       // https://github.com/Bodmer/TFT_eSPI


#include <shs_ControlWiFi.h>
#include <GyverNTP.h>


shs::ClimateStation climate_station(
    std::make_shared<shs::MHZ19>(MHZ19_RX, MHZ19_TX),
    std::make_shared<shs::BME280>(BME280_CACHE_EXPIRATION_TIME),
    nullptr,
    std::make_shared<GyverDS3231>(),
    std::make_shared<GyverNTP>(shs::settings::GMT)
);


shs::ClimateStationVisualizer climate_station_visualizer(
    climate_station,
    std::make_shared<TFT_eSPI>()
);


void setup()
{
    dinit();
    doutln("");

    shs::ControlWiFi::connectWiFi();

    climate_station.start();
    climate_station_visualizer.start();
    doutln("ok");
}


void loop()
{
    climate_station.tick();
    climate_station_visualizer.tick();
}
