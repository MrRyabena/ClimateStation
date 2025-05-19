#include "shs_ClimateStationVisualizer.h"


shs::ClimateStationVisualizer::ClimateStationVisualizer(std::shared_ptr<shs::ClimateStation> climate_station,
    std::shared_ptr<shs::ClimateStationStorage> storage, std::shared_ptr<TFT_eSPI> m_tft,
    const uint8_t tft_led_pin, const uint16_t leds_num, const shs::t::shs_pin_t leds_pin
)
    : m_cls(climate_station), m_storage(storage), m_tft(m_tft), m_tft_LED_pin(tft_led_pin),
    m_main_tmr(m_TICK_TIMEOUT), m_sleep_tmr(storage->cs_config.SLEEP_TIMEOUT), m_button_tmr(m_BUTTON_TIMEOUT),
    m_led_tmr(storage->cs_config.LED_TIMEOUT), m_smoothing_tmr(60)
{}


void shs::ClimateStationVisualizer::start()
{
    FastLED.clear();
    FastLED.show();
    FastLED.setBrightness(0);
    m_updateLED();


    m_tft->init();
    m_tft->setRotation(3);
    m_tft->fillScreen(shs::utils::rgb565(shs::ThemeColors::BACKGROUND));

    m_touch_calibrate();

    m_enable_MainWindow();

    enableTFT();

}


void shs::ClimateStationVisualizer::tick()
{
    if (m_sleep_tmr.milliseconds() >= m_storage->cs_config.SLEEP_TIMEOUT) disableTFT();  //m_storage->cs_config.SLEEP_TIMEOUT
    else enableTFT();
    if (m_led_tmr.milliseconds() >= m_storage->cs_config.LED_TIMEOUT) m_disableLED();
    else m_enableLED();

    m_touch_tick();

    if (m_main_tmr.check())
    {
        m_updateLED();
        if (m_main_window) m_main_window->tick();
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
    int hue = map(data.CO2, m_storage->cs_config.MIN_CO2, m_storage->cs_config.MAX_CO2, m_storage->cs_config.MIN_COLOR_H, m_storage->cs_config.MAX_COLOR_H);
    m_led_hue = constrain(hue, m_storage->cs_config.MIN_COLOR_H, m_storage->cs_config.MAX_COLOR_H);

    FastLED.showColor(static_cast<CRGB>(CHSV(m_led_hue, 255, 255)));
}

void shs::ClimateStationVisualizer::m_enableLED()
{
    if (m_smoothing_tmr.check())
    {
        auto brightness = FastLED.getBrightness();
        if (brightness < m_storage->cs_config.LED_BRIGHTNESS)
        {
            FastLED.setBrightness(brightness + 1);
            FastLED.showColor(static_cast<CRGB>(CHSV(m_led_hue, 255, 255)));
        }
        else if (brightness > m_storage->cs_config.LED_BRIGHTNESS)
        {
            FastLED.setBrightness(brightness - 1);
            FastLED.showColor(static_cast<CRGB>(CHSV(m_led_hue, 255, 255)));
        }
    }
}


void shs::ClimateStationVisualizer::m_disableLED()
{
    if (m_smoothing_tmr.check())
    {
        auto brightness = FastLED.getBrightness();
        if (brightness)
        {
            FastLED.setBrightness(brightness - 1);
            FastLED.showColor(static_cast<CRGB>(CHSV(m_led_hue, 255, 255)));
        }

    }
}

void shs::ClimateStationVisualizer::m_touch_calibrate()
{
    uint16_t calData[m_TFT_TOUCH_CALIBRATION_DATA_SIZE];

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
        m_led_tmr.reset();

        if (m_button_tmr.check() && m_tft_enabled)
        {
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
            else if (m_settings_window)
                auto i = 0;
            for (auto& x : m_settings_window->buttons)
            {
                x->checkPressed(m_touch_x, m_touch_y)
                    if (x->isPressed())
                    {
                        switch (i)
                        {
                            case 0: m_enable_MainWindow(); return; break;
                            default: break;
                        }
                    }
                i++;
            }
        }


    }
}


void shs::ClimateStationVisualizer::m_enable_MainWindow()
{
    m_all_disable();

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
    m_all_disable();

    m_chart_window = std::make_shared<shs::ChartWindow>(m_tft, m_cls, m_storage);
    m_chart_window->start();
}


void shs::ClimateStationVisualizer::m_disable_ChartWindow()
{
    if (m_chart_window) m_chart_window = nullptr;
}

void shs::ClimateStationVisualizer::m_enable_SettingsWindow()
{
    m_all_disable();
    m_settings_window = std::make_shared<shs::SettingsWindow>(m_tft, m_cls, m_storage);
    m_settings_window->start();
}

void shs::ClimateStationVisualizer::m_disable_SettingsWindow()
{
    if (m_settings_window) m_settings_window = nullptr;
}

void shs::ClimateStationVisualizer::m_all_disable()
{
    m_disable_MainWindow();
    m_disable_ChartWindow();
    m_disable_SettingsWindow();
}

