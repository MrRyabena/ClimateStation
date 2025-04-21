#include "MainWindow.h"

void shs::MainWindow::start()
{
    Widget::start();

    // time
    auto block = std::make_shared<shs::RectWidget>(m_tft,
        0, 0, width / 2 - 20, height / 2 - 20,
        8, 2,
        shs::ThemeColors::LIGHT, shs::ThemeColors::BACKGROUND, shs::ThemeColors::LIGHT
    );

    attachLayer(block, shs::Widget::Align::LEFT | shs::Widget::Align::TOP, 30, 10);

    // out

    block = std::make_shared<shs::RectWidget>(m_tft,
        0, 0, width / 2 - 20, height / 2 - 15,
        8, 2,
        shs::ThemeColors::LIGHT
    );

    auto text = std::make_shared<shs::Label>(m_tft,
        "OUT", 2, 1,
        0, 0, block->width * 0.75, 0, 8, 0,
        shs::ThemeColors::MINT, shs::ThemeColors::MINT,
        shs::ThemeColors::BACKGROUND
    );



    block->attachLayer(text, shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::TOP, 0, 2);

    attachLayer(block, shs::Widget::Align::LEFT | shs::Widget::Align::BOTTOM, 30, 10);

    // in
    block = std::make_shared<shs::RectWidget>(m_tft,
        0, 0, width / 2 - 30, height - 15,
        8, 2,
        shs::ThemeColors::LIGHT
    );

    text = std::make_shared<shs::Label>(m_tft,
        "IN", 2, 1,
        0, 0, block->width * 0.75, 0, 8, 0,
        shs::ThemeColors::LIGHT_GREEN, shs::ThemeColors::LIGHT_GREEN,
        shs::ThemeColors::BACKGROUND
    );

    block->attachLayer(text, shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::TOP, 0, 2);

    attachLayer(block, shs::Widget::Align::RIGHT | shs::Widget::Align::VERTICAL_CENTER, 10, 0);

}


void shs::MainWindow::tick()
{
    Widget::tick();
}


void shs::MainWindow::updateData(const shs::ClimateStation::Data& data)
{
    if (!m_tft) return;

    // time

    {
        Stamp stamp(data.time);

        shs::Label time(m_tft, stamp.timeToString(), 2, 2);

        shs::Widget::setAligned(*m_layers[0], time, shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::VERTICAL_CENTER);
        time.tick();
    }

    // in
    {
        // CO2

        shs::Label co2(m_tft, static_cast<shs::t::shs_string_t>(data.CO2), 2, 2);
        co2.foreground_color = shs::ThemeColors::LIGHT_GREEN;

        shs::Widget::setAligned(*m_layers[2], co2, shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::TOP, 0, 20);

        co2.tick();

        // pressure

        shs::Label pressure(m_tft, static_cast<shs::t::shs_string_t>(pressureToMmHg(data.pressure)), 2, 2);
        pressure.foreground_color = shs::ThemeColors::LIGHT_GREEN;

        shs::Widget::setAligned(*m_layers[2], pressure, shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::TOP, 0, co2.y + co2.height + 10);

        pressure.tick();
        
        // temperature
        
        shs::Label temp(m_tft, static_cast<shs::t::shs_string_t>(data.indoor_temperature.toFloat()), 2, 2);
        temp.foreground_color = shs::ThemeColors::LIGHT_GREEN;

        shs::Widget::setAligned(*m_layers[2], temp, shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::TOP, 0, pressure.y + pressure.height + 10);

        temp.tick();

        // humidity
         shs::Label hum(m_tft, static_cast<shs::t::shs_string_t>(data.indoor_humidity.toFloat()), 2, 2);
        hum.foreground_color = shs::ThemeColors::LIGHT_GREEN;

        shs::Widget::setAligned(*m_layers[2], hum, shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::TOP, 0, temp.y + temp.height + 10);

        hum.tick();
        

    }

    // out
    {
        shs::Label temp(m_tft, static_cast<shs::t::shs_string_t>(data.outdoor_temperature.toFloat()), 2, 2);
        temp.foreground_color = shs::ThemeColors::MINT;

        shs::Widget::setAligned(*m_layers[1], temp, shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::TOP, 0, 20);

        temp.tick();

        // humidity
        shs::Label hum(m_tft, static_cast<shs::t::shs_string_t>(data.outdoor_humidity.toFloat()), 2, 2);
        hum.foreground_color = shs::ThemeColors::MINT;

        shs::Widget::setAligned(*m_layers[1], hum, shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::BOTTOM, 0, 20);

        hum.tick();
    }


}

