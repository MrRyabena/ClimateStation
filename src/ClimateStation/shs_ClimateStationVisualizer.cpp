#include "shs_ClimateStationVisualizer.h"

shs::ClimateStationVisualizer::ClimateStationVisualizer(shs::ClimateStation& climate_station, std::shared_ptr<TFT_eSPI> tft)
    : m_cls(climate_station), m_tft(tft)
{}

void shs::ClimateStationVisualizer::start()
{
    if (m_tft)
    {
        m_tft->init();
        m_tft->setRotation(3);
        m_tft->fillScreen(m_rgb565(shs::ThemeColors::BACKGROUND));
    }
}

void shs::ClimateStationVisualizer::tick()
{
    if (m_main_tmr.milliseconds() >= TICK_TIME)
    {
        if (m_tft)
        {
            m_tft->fillScreen(m_rgb565(0x00, 0x12, 0x19));

            auto data = m_cls.getData();

            String str = String("CO2:                  ") + data.CO2; m_tft->drawString(str, 20, 48, 2);
            str = String("pressure:             ") + static_cast<float>(data.pressure); m_tft->drawString(str, 20, 63, 2);
            str = String("indoor_temperature:   ") + static_cast<float>(data.indoor_temperature); m_tft->drawString(str, 20, 76, 2);
            str = String("outdoor_temperature:  ") + static_cast<float>(data.outdoor_temperature); m_tft->drawString(str, 20, 104, 2);
            str = String("indoor_humidity:      ") + static_cast<float>(data.indoor_humidity); m_tft->drawString(str, 20, 132, 2);
            str = String("outdoor_humidity:     ") + static_cast<float>(data.outdoor_humidity); m_tft->drawString(str, 20, 160, 2);
            str = String("time:                 ") + data.time; m_tft->drawString(str, 20, 188, 2);


        }

        m_main_tmr.reset();
    }
}

void shs::ClimateStationVisualizer::printDebug(const String& str, const uint16_t x, const uint16_t y)
{
    if (m_tft) m_tft->drawString(str, x, y, 2);
}



