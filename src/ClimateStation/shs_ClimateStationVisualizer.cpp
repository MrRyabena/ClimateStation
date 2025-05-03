#include "shs_ClimateStationVisualizer.h"


shs::ClimateStationVisualizer::ClimateStationVisualizer(std::shared_ptr<shs::ClimateStation> climate_station,
    std::shared_ptr<shs::ClimateStationStorage> storage, std::shared_ptr<TFT_eSPI> m_tft,
    const uint8_t tft_led_pin
)
    : m_cls(climate_station), m_storage(storage), m_tft(m_tft), m_tft_LED_pin(tft_led_pin)
{}

void shs::ClimateStationVisualizer::start()
{
    enableTFT();

    if (!m_tft) return;

    m_tft->init();
    m_tft->setRotation(3);
    m_tft->fillScreen(m_rgb565(shs::ThemeColors::BACKGROUND));

    m_touch_calibrate();

}

void shs::ClimateStationVisualizer::tick()
{
    uint16_t x = 0, y = 0; // To store the touch coordinates

    // Pressed will be set true is there is a valid touch on the screen
    bool pressed = m_tft->getTouch(&x, &y);

    // Draw a white spot at the detected coordinates
    if (pressed)
    {
        m_sleep_tmr.reset();
        doutln("pressed");

        //tft_ptr->fillCircle(x, y, 2, TFT_WHITE);
        //Serial.print("x,y = ");
        //Serial.print(x);
        //Serial.print(",");
        //Serial.println(y);
    }

    if (m_sleep_tmr.milliseconds() >= m_SLEEP_TIMEOUT) disableTFT();
    else enableTFT();

    if (m_main_tmr.milliseconds() >= TICK_TIME)
    {
        // if (m_tft)
        // {
        //     m_tft->fillScreen(m_rgb565(0x00, 0x12, 0x19));

        //     auto data = m_cls->getData();

        //     String str = String("CO2:                  ") + data.CO2; m_tft->drawString(str, 20, 48, 2);
        //     str = String("pressure:             ") + static_cast<float>(data.pressure); m_tft->drawString(str, 20, 63, 2);
        //     str = String("indoor_temperature:   ") + static_cast<float>(data.indoor_temperature); m_tft->drawString(str, 20, 76, 2);
        //     str = String("outdoor_temperature:  ") + static_cast<float>(data.outdoor_temperature); m_tft->drawString(str, 20, 104, 2);
        //     str = String("indoor_humidity:      ") + static_cast<float>(data.indoor_humidity); m_tft->drawString(str, 20, 132, 2);
        //     str = String("outdoor_humidity:     ") + static_cast<float>(data.outdoor_humidity); m_tft->drawString(str, 20, 160, 2);
        //     str = String("time:                 ") + data.time; m_tft->drawString(str, 20, 188, 2);


        // }

        m_main_tmr.reset();
    }
}

void shs::ClimateStationVisualizer::printDebug(const String& str, const uint16_t x, const uint16_t y)
{
    if (m_tft) m_tft->drawString(str, x, y, 2);
}

void shs::ClimateStationVisualizer::enableTFT()
{
    if (!m_tft_enabled)
    {
        pinMode(m_tft_LED_pin, OUTPUT);
        digitalWrite(m_tft_LED_pin, LOW);

        m_tft_enabled = true;
    }
}

void shs::ClimateStationVisualizer::disableTFT()
{

    if (m_tft_enabled)
    {
        pinMode(m_tft_LED_pin, INPUT);
        m_tft_enabled = false;
    }
}


void shs::ClimateStationVisualizer::m_touch_calibrate()
{
    uint16_t calData[shs::ClimateStationStorage::m_TFT_TOUCH_CALIBRATION_DATA_SIZE];

    if (m_storage->get_TFT_calData(calData))
    {
        m_tft->setTouch(calData);
        return;
    }


    // Calibrate
    m_tft->fillScreen(TFT_BLACK);
    m_tft->setCursor(20, 0);
    m_tft->setTextFont(2);
    m_tft->setTextSize(1);
    m_tft->setTextColor(TFT_WHITE, TFT_BLACK);

    m_tft->println("Touch corners as indicated");

    m_tft->setTextFont(1);
    m_tft->println();

    m_tft->calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    if (m_storage) m_storage->save_TFT_calData(calData);

    m_tft->fillScreen(TFT_BLACK);

    m_tft->setTextColor(TFT_GREEN, TFT_BLACK);
    m_tft->println("Calibration complete!");

    delay(4000);
}

