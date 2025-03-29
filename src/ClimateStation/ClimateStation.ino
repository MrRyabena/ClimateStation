#define DEBUG
#define SHS_SF_DEBUG

#include <shs_debug.h>

#include <memory>

#include "shs_ClimateStation.h"


#include <shs_ControlWiFi.h>
#include <GyverNTP.h>

shs::ClimateStation climate_station(nullptr, nullptr, nullptr, nullptr, std::make_shared<GyverNTP>(shs::settings::GMT));


void setup() 
{
  dinit();
  doutln("");
  shs::ControlWiFi::connectWiFiWait();
  doutln("ok");

  climate_station.start();
}

void loop() {
  climate_station.tick();
}
