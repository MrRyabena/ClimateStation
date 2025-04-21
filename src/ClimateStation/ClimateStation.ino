#include "settings.h"

#include <shs_debug.h>

#include <memory>

#include "shs_ClimateStation.h"
#include "shs_ClimateStationVisualizer.h"
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

shs::ClimateStation climate_station(
    std::make_shared<shs::MHZ19>(MHZ19_RX, MHZ19_TX),
    std::make_shared<shs::BME280>(BME280_CACHE_EXPIRATION_TIME),
    nullptr,
    std::make_shared<GyverDS3231>(),
    std::make_shared<GyverNTP>(shs::settings::GMT)
);


shs::ClimateStationVisualizer climate_station_visualizer(
    climate_station,
    tft_ptr
);


shs::SDCard sd(SD_CS, SD_MOSI, SD_MISO, SD_SCK);

shs::RectWidget rw(tft_ptr, 20, 20, 100, 100, 20, 2, shs::ThemeColors::MINT);

shs::MainWindow window(tft_ptr);

void setup()
{
  dinit();
  
  shs::ControlWiFi::connectWiFi();

  climate_station.start();
  climate_station_visualizer.start();


  //    auto text = std::make_shared<shs::Label>(tft_ptr,
  //     30, 30, 
  //     "HUMIDITY", 7, 1, 
  //     shs::ThemeColors::MINT, shs::ThemeColors::MINT, shs::ThemeColors::BACKGROUND
  //   );

  //   text->start();

  // //  rw.attachLayer(std::make_shared<shs::RectWidget>(tft_ptr, text->x - 2, text->y - 2, text->width + 4, text->height + 4, 5, 4, shs::ThemeColors::MINT, shs::ThemeColors::MINT));
  //   rw.attachLayer(text, 0, 0, shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::TOP, 0, -text->height / 2);
  window.start();
  window.tick();
}


shs::ProgramTime tmr;
void loop()
{
    climate_station.tick();


     if (tmr.milliseconds() >= 10'000)
     { 

      //   climate_station_visualizer.tick();
      //   Wire.end();
      //   sd.begin();
        
      //  climate_station_visualizer.printDebug(String("SD status: ") + static_cast<int>(shs::etoi(sd.getStatus())), 20, 20);

      //  if (sd.getStatus() == shs::SDCard::Status::CARD_OK)
      //   {
      //     climate_station_visualizer.printDebug(sd.readTest(), 20, 35);

      //       //climate_station_visualizer.printDebug(String("Card type: ") + SD.cardType(), 20, 48);
      //       //climate_station_visualizer.printDebug(String("Card size: ") + SD.cardSize(), 20, 76);
      //      // climate_station_visualizer.printDebug(String("Total bytes: ") + SD.totalBytes(), 20, 104);
      //      // climate_station_visualizer.printDebug(String("Used bytes: ") + SD.usedBytes(), 20, 132);
      //  }

      //   sd.end();
      //   Wire.begin();
      //   rw.tick();

      window.tick();
      window.updateData(climate_station.getData());
      tmr.reset();
     }
}
