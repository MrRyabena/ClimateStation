#include "shs_ClimateStationVisualizer.h"


shs::ClimateStationVisualizer::ClimateStationVisualizer(std::shared_ptr<shs::ClimateStation> climate_station,
    std::shared_ptr<shs::ClimateStationStorage> storage, std::shared_ptr<TFT_eSPI> m_tft,
    const uint8_t tft_led_pin, const uint16_t leds_num, const shs::t::shs_pin_t leds_pin
)
    : m_cls(climate_station), m_storage(storage), m_tft(m_tft), m_tft_LED_pin(tft_led_pin)
{}


void shs::ClimateStationVisualizer::start()
{
    FastLED.clear();
    FastLED.show();
    FastLED.setBrightness(20);
    //FastLED.showColor(0xffff00);


    m_tft->init();
    m_tft->setRotation(3);
    m_tft->fillScreen(shs::utils::rgb565(shs::ThemeColors::BACKGROUND));

    m_touch_calibrate();

    m_enable_MainWindow();

    enableTFT();

}


void shs::ClimateStationVisualizer::tick()
{
    if (m_sleep_tmr.milliseconds() >= m_SLEEP_TIMEOUT) disableTFT();
    else enableTFT();

    m_touch_tick();

    if (m_main_tmr.milliseconds() >= TICK_TIME)
    {
        m_main_tmr.reset();
        if (m_main_window) m_main_window->tick();
        m_updateLED();
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


void shs::ClimateStationVisualizer::m_updateLED()
{
    auto data = m_cls->getData();
    int hue = map(data.CO2, M_MIN_CO2, M_MAX_CO2, M_MIN_COLOR_H, M_MAX_COLOR_H);
    hue = constrain(hue, M_MIN_COLOR_H, M_MAX_COLOR_H);
    
    FastLED.showColor(static_cast<CRGB>(CHSV(hue, 255, 255)));    
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


void shs::ClimateStationVisualizer::m_touch_tick()
{
    // Pressed will be set true is there is a valid touch on the screen
    if (m_tft->getTouch(&m_touch_x, &m_touch_y))
    {
        m_sleep_tmr.reset();

        if (m_button_tmr.milliseconds() > m_BUTTON_TIMEOUT && m_tft_enabled)
        {
            m_button_tmr.reset();

            if (m_main_window)
            {

                auto i = 0;
                for (auto& x : m_main_window->buttons)
                {
                    x->checkPressed(m_touch_x, m_touch_y);
                    if (x->isPressed())
                    {
                        switch (i)
                        {
                            case 0: m_enable_ChartWindow(); return; break;                  // chart
                            case 1: break;                                          // info
                            case 2: break;                                          // settings
                            default: break;
                        }
                    }
                    i++;
                }
            }

            else if (m_chart_window)
            {
                auto i = 0;
                for (auto& x : m_chart_window->buttons)
                {
                    x->checkPressed(m_touch_x, m_touch_y);
                    if (x->isPressed())
                    {
                        switch (i)
                        {
                            case 0: m_enable_MainWindow(); return; break;                   // main window

                            default: break;
                        }
                    }
                    i++;
                }
            }
        }


    }
}


void shs::ClimateStationVisualizer::m_enable_MainWindow()
{
    m_disable_ChartWindow();

    m_main_window = std::make_shared<shs::MainWindow>(m_tft, m_cls, m_storage);
    m_main_window->start();
    m_main_window->tick();
}


void shs::ClimateStationVisualizer::m_disable_MainWindow()
{
    if (m_main_window) m_main_window = nullptr;
}


void shs::ClimateStationVisualizer::m_enable_ChartWindow()
{
    m_disable_MainWindow();

    m_chart_window = std::make_shared<shs::ChartWindow>(m_tft, m_storage);
    m_chart_window->attachLayer(
        std::make_shared<shs::Image>(m_storage, F("/SHS/SHS_ClimateStation/images/logo-mint.shsf"), m_tft, 0, 0, 220, 220),
        shs::Widget::Align::VERTICAL_CENTER | shs::Widget::Align::HORIZONTAL_CENTER);
    m_chart_window->start();
}


void shs::ClimateStationVisualizer::m_disable_ChartWindow()
{
    if (m_chart_window) m_chart_window = nullptr;
}

