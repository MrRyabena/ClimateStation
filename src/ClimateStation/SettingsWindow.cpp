#include "SettingsWindow.h"

shs::SettingsWindow::SettingsWindow(std::shared_ptr<TFT_eSPI> tft, std::shared_ptr<shs::ClimateStation> climate_station, std::shared_ptr<shs::ClimateStationStorage> storage)
    : Widget(tft, 0, 0, 320, 240), m_climate_station(climate_station), m_storage(storage)
{}

void shs::SettingsWindow::start()
{
    m_tft->fillScreen(shs::utils::rgb565(shs::ThemeColors::BACKGROUND));

    // buttons
    auto block = std::make_shared<shs::RectWidget>(m_tft, 0, 0, m_BUTTON_SIZE, m_BUTTON_SIZE, 8, 2);
    attachLayer(block, shs::Widget::Align::LEFT | shs::Widget::Align::TOP, 10, 10);
    block->attachLayer(std::make_shared<shs::Image>(m_storage, F("home_icon_30.shsf"), m_tft), shs::Widget::Align::CENTER);

    buttons.push_back(block);


    // LED brightness
    m_vc.push_back(std::make_shared<shs::ValueControl<uint16_t>>(
        m_storage->cs_config.LED_BRIGHTNESS, 10,
        m_tft,
        0, 0, 150, 40
    ));

    attachLayer(m_vc.back(), shs::Widget::Align::RIGHT | shs::Widget::Align::TOP, 10, 60);

    attachLayer(std::make_shared<shs::Label>(
        m_tft, F("LED brightness (0-255):"),
        2, 1
    ),
        shs::Widget::LEFT | shs::Widget::TOP, 10, 70
    );


    // display timeout
    m_vc.push_back(std::make_shared<shs::ValueControl<uint16_t>>(
        m_storage->cs_config.SLEEP_TIMEOUT / (1000 * 60), 1,
        m_tft,
        0, 0, 150, 40
    ));

    attachLayer(m_vc.back(), shs::Widget::Align::RIGHT | shs::Widget::Align::TOP, 10, 60 + 55);
    attachLayer(std::make_shared<shs::Label>(
        m_tft, F("Display timeout (min):"),
        2, 1
    ),
        shs::Widget::LEFT | shs::Widget::TOP, 10, 70 + 55
    );


    // LED timeout
    m_vc.push_back(std::make_shared<shs::ValueControl<uint16_t>>(
        m_storage->cs_config.LED_TIMEOUT / (1000 * 60), 1,
        m_tft,
        0, 0, 150, 40
    ));

    attachLayer(m_vc.back(), shs::Widget::Align::RIGHT | shs::Widget::Align::TOP, 10, 60 + 55 * 2);
    attachLayer(std::make_shared<shs::Label>(
        m_tft, F("LED timeout (min):"),
        2, 1
    ),
        shs::Widget::LEFT | shs::Widget::TOP, 10, 70 + 55 * 2
    );

    Widget::start();
    Widget::tick();
}

void shs::SettingsWindow::tick()
{
    Widget::tick();


    if (m_vc[0]->value != m_storage->cs_config.LED_BRIGHTNESS)
    {
        if (m_vc[0]->value > 255) m_vc[0]->value = 0;
        m_storage->cs_config.LED_BRIGHTNESS = m_vc[0]->value;
        m_config_changed = true;
    }


    if (m_vc[1]->value != m_storage->cs_config.SLEEP_TIMEOUT && m_vc[1]->value != 0)
    {
        if (m_vc[1]->value > 10) m_vc[1]->incr = 10;
        else m_vc[1]->incr = 1;
        m_storage->cs_config.SLEEP_TIMEOUT = m_vc[1]->value * 1000 * 60;
        m_config_changed = true;
    }


    if (m_vc[2]->value != m_storage->cs_config.LED_TIMEOUT && m_vc[2]->value != 0)
    {
        if (m_vc[2]->value > 10) m_vc[2]->incr = 10;
        else m_vc[2]->incr = 1;
        m_storage->cs_config.LED_TIMEOUT = m_vc[2]->value * 1000 * 60;
        m_config_changed = true;
    }

}



