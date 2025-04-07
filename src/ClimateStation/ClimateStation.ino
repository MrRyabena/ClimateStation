#include "settings.h"

#define DEBUG
#define SHS_SF_DEBUG

#include <shs_debug.h>

#include <memory>

#include "shs_ClimateStation.h"


#include <shs_ControlWiFi.h>
#include <GyverNTP.h>


shs::ClimateStation climate_station(
    std::make_shared<shs::MHZ19>(MHZ19_RX, MHZ19_TX),
    std::make_shared<shs::BME280>(BME280_CACHE_EXPIRATION_TIME),
    nullptr,
    std::make_shared<GyverDS3231>(),
    std::make_shared<GyverNTP>(shs::settings::GMT)
);


void setup()
{
    dinit();
    doutln("");

    shs::ControlWiFi::connectWiFi();

    climate_station.start();
    doutln("ok");
}


void loop()
{
    climate_station.tick();
}
