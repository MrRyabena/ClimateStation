#include "settings.h"

#define DEBUG
#define SHS_SF_DEBUG
#include <shs_settings_private.h>

#include <shs_debug.h>

#include <memory>

#include "shs_ClimateStation.h"
#include "shs_ClimateStationVisualizer.h"
#include "shs_ClimateStationStorage.h"
#include "ClimateStationGUIcore.h"
#include "shs_SDCard.h"
#include "MainWindow.h"

#include <SPI.h>
#include <TFT_eSPI.h>       // https://github.com/Bodmer/TFT_eSPI


#include <shs_ControlWiFi.h>
#include <shs_ProgramTime.h>
#include <shs_utils.h>
#include <GyverNTP.h>

auto tft_ptr = std::make_shared<TFT_eSPI>();

auto climate_station = std::make_shared<shs::ClimateStation>(
    std::make_shared<shs::MHZ19>(MHZ19_RX, MHZ19_TX),
    std::make_shared<shs::BME280>(BME280_CACHE_EXPIRATION_TIME),
    nullptr,
    std::make_shared<GyverDS3231>(),
    std::make_shared<GyverNTP>(shs::settings::GMT)
);

auto storage = std::make_shared<shs::ClimateStationStorage>(climate_station, SD_CS);

shs::ClimateStationVisualizer climate_station_visualizer(
    climate_station,
    storage,
    tft_ptr, TFT_LED
);




shs::RectWidget rw(tft_ptr, 20, 20, 100, 100, 20, 2, shs::ThemeColors::MINT);

shs::MainWindow window(tft_ptr);

void setup()
{
  dinit();

  shs::ControlWiFi::connectWiFi();

  
  SPI.begin(SD_SCK, SD_MISO, SD_MOSI);
  dout(TFT_MISO); dout(TFT_MOSI); doutln(TFT_SCLK);
  storage->start();


  climate_station->start();
  climate_station_visualizer.start();

  window.start();
  window.tick();
  window.updateData(climate_station->getData());


  doutln("ok");
}


shs::ProgramTime tmr;
void loop()
{
    climate_station->tick();
    storage->tick();
    climate_station_visualizer.tick();



     if (tmr.milliseconds() >= 10'000)
     { 

      //   climate_station_visualizer.tick();
      //   Wire.end();
      //   sd.begin();
        
      //  climate_station_visualizer.printDebug(String("SD status: ") + static_cast<int>(shs::etoi(sd.getStatus())), 20, 20);

      // if (storage.getStatus() == shs::ClimateStationStorage::Status::CARD_OK)
      //  {
      //     doutln(storage.readTest());

      //     doutln(String("Card type: ") + SD.cardType());
      //     doutln(String("Card size: ") + SD.cardSize());
      //    doutln(String("Total bytes: ") + SD.totalBytes());
      // doutln(String("Used bytes: ") + SD.usedBytes());
      //   }

      //   sd.end();
      //   Wire.begin();
      //   rw.tick();

      //window.tick();
      window.updateData(climate_station->getData());
      tmr.reset();
      // storage.end();
     }
}
