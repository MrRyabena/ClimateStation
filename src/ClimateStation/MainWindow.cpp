#include "MainWindow.h"

void shs::MainWindow::start()
{
    Widget::start();

    m_tft->fillScreen(shs::utils::rgb565(shs::ThemeColors::BACKGROUND));

    // time
    auto block = std::make_shared<shs::RectWidget>(m_tft,
        0, 0, width / 2 - 15, height / 4 - 10,
        8, 2,
        shs::ThemeColors::LIGHT, shs::ThemeColors::BACKGROUND, shs::ThemeColors::LIGHT
    );

    attachLayer(block, shs::Widget::Align::LEFT | shs::Widget::Align::VERTICAL_CENTER, 10, -(height / 6) + 10);

    // out

    block = std::make_shared<shs::RectWidget>(m_tft,
        0, 0, width / 2 - 15, height / 2 - 15,
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

    attachLayer(block, shs::Widget::Align::LEFT | shs::Widget::Align::BOTTOM, 10, 10);

    // in
    block = std::make_shared<shs::RectWidget>(m_tft,
        0, 0, width / 2 - 15, height - 15,
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


    // buttons
    // chart
    block = std::make_shared<shs::RectWidget>(m_tft, 0, 0, m_BUTTON_SIZE, m_BUTTON_SIZE, 8, 2);
    block->attachLayer(std::make_shared<shs::Image>(m_storage, F("chart_icon_30.shsf"), m_tft), shs::Widget::Align::CENTER);
    attachLayer(block, shs::Widget::Align::LEFT | shs::Widget::Align::TOP, 10, 10);
    buttons.push_back(block);

    block = std::make_shared<shs::RectWidget>(m_tft, 0, 0, m_BUTTON_SIZE, m_BUTTON_SIZE, 8, 2);
    block->attachLayer(std::make_shared<shs::Image>(m_storage, F("info_icon_30.shsf"), m_tft), shs::Widget::Align::CENTER);
    attachLayer(block, shs::Widget::Align::LEFT | shs::Widget::Align::TOP, 10 + m_BUTTON_SIZE + 10, 10);
    buttons.push_back(block);

    block = std::make_shared<shs::RectWidget>(m_tft, 0, 0, m_BUTTON_SIZE, m_BUTTON_SIZE, 8, 2);
    block->attachLayer(std::make_shared<shs::Image>(m_storage, F("settings_icon_30.shsf"), m_tft), shs::Widget::Align::CENTER);
    attachLayer(block, shs::Widget::Align::LEFT | shs::Widget::Align::TOP, (10 + m_BUTTON_SIZE) * 2 + 10, 10);
    buttons.push_back(block);

    Widget::start();
}


void shs::MainWindow::tick()
{
    if (m_cls) updateData(m_cls->getData());
}


void shs::MainWindow::updateData(const shs::ClimateStation::Data& data)
{
    if (!m_tft) return;

    // time

    {
        Stamp stamp(data.time);

        shs::Label time(m_tft, stamp.timeToString().substring(0, 5), 2, 2);

        shs::Widget::setAligned(*m_layers[0], time, shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::VERTICAL_CENTER);
        time.tick();
    }

    // in
    {
        // CO2
        shs::IndicatorWidget co2(m_tft, 0, 0, width / 2 - 30, 0,
            "ppm", 2, 2, 2, 1, shs::ThemeColors::LIGHT_GREEN);

        shs::Widget::setAligned(*m_layers[2], co2, shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::TOP, 0, 20);

        auto co2_trend = m_statistics->getTrend(shs::ClimateStationMetrics::CO2);
        shs::t::shs_color_t co2_color{};

        switch (co2_trend)
        {
            case shs::IndicatorWidget::ValueTrend::INCREASING: co2_color = 0xff0000; break;
            case shs::IndicatorWidget::ValueTrend::DECREASING: co2_color = 0x00ff00; break;

            case shs::IndicatorWidget::ValueTrend::CONST: [[fallthrough]];
            default:co2_color = 0xffff00;
                break;
        }

        co2.draw(shs::t::shs_string_t(data.CO2), co2_trend, co2_color);


        // pressure

        shs::IndicatorWidget pressure(m_tft, 0, 0, width / 2 - 30, 0,
            "mmHg", 2, 2, 2, 1, shs::ThemeColors::LIGHT_GREEN);


        shs::Widget::setAligned(*m_layers[2], pressure, shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::TOP, 0, co2.y + co2.height + 10);

        pressure.draw(shs::t::shs_string_t(pressureToMmHg(data.pressure), 1), m_statistics->getTrend(shs::ClimateStationMetrics::PRESSURE), shs::ThemeColors::LIGHT);


        // temperature

        shs::IndicatorWidget temp(m_tft, 0, 0, width / 2 - 30, 0,
            "C", 2, 2, 2, 1, shs::ThemeColors::LIGHT_GREEN);

        shs::Widget::setAligned(*m_layers[2], temp, shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::TOP, 0, pressure.y + pressure.height + 10);

        temp.draw(shs::t::shs_string_t(data.indoor_temperature.toFloat(), 1), m_statistics->getTrend(shs::ClimateStationMetrics::IN_TEMP), shs::ThemeColors::LIGHT);

        // humidity

        shs::IndicatorWidget hum(m_tft, 0, 0, width / 2 - 30, 0,
            "%", 2, 2, 2, 1, shs::ThemeColors::LIGHT_GREEN);

        shs::Widget::setAligned(*m_layers[2], hum, shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::TOP, 0, temp.y + temp.height + 10);

        hum.draw(shs::t::shs_string_t(data.indoor_humidity.toFloat(), 1), m_statistics->getTrend(shs::ClimateStationMetrics::IN_HUM), shs::ThemeColors::LIGHT);


    }


    // out
    {
        shs::IndicatorWidget temp(m_tft, 0, 0, width / 2 - 30, 0, "C", 2, 2, 2, 1, shs::ThemeColors::MINT);

        shs::Widget::setAligned(*m_layers[1], temp, shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::TOP, 0, 20);

        temp.draw(shs::t::shs_string_t(data.outdoor_temperature.toFloat(), 1), m_statistics->getTrend(shs::ClimateStationMetrics::OUT_TEMP), shs::ThemeColors::LIGHT);

        // humidity
        shs::IndicatorWidget hum(m_tft, 0, 0, width / 2 - 30, 0, "%", 2, 2, 2, 1, shs::ThemeColors::MINT);

        shs::Widget::setAligned(*m_layers[1], hum, shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::BOTTOM, 0, 20);

        hum.draw(shs::t::shs_string_t(data.outdoor_humidity.toFloat(), 1), m_statistics->getTrend(shs::ClimateStationMetrics::OUT_HUM), shs::ThemeColors::LIGHT);
    }
}

