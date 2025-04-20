#include "MainWindow.h"

void shs::MainWindow::start()
{
    Widget::start();

    // Temperature
    
    auto block = std::make_shared<shs::RectWidget>(m_tft,
        0, 0, width / 2 - 20, height / 2 - 30,
        20, 2,
        shs::ThemeColors::LIGHT_GREEN
    );

    auto text = std::make_shared<shs::Label>(m_tft,
        0, 0,
        "TEMPERATURE", 2, 1,
        shs::ThemeColors::LIGHT_GREEN, shs::ThemeColors::LIGHT_GREEN,
        shs::ThemeColors::BACKGROUND
    );

    text->start();

    block->attachLayer(text, 0, 0,
        shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::TOP,
        0, -text->height / 2);

    attachLayer(block, 0, 0,
        shs::Widget::Align::RIGHT | shs::Widget::Align::TOP, 20, 20);

    
    // Humidity

    block = std::make_shared<shs::RectWidget>(m_tft,
        0, 0, width / 2 - 20, height / 2 - 30,
        20, 2,
        shs::ThemeColors::MINT);

    text = std::make_shared<shs::Label>(m_tft,
        0, 0,
        "HUMIDITY", 2, 1,
        shs::ThemeColors::MINT, shs::ThemeColors::MINT,
        shs::ThemeColors::BACKGROUND);

    text->start();

    block->attachLayer(text, 0, 0,
        shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::TOP,
        0, -text->height / 2);

    attachLayer(block, 0, 0,
        shs::Widget::Align::RIGHT | shs::Widget::Align::BOTTOM, 20, 20
    );

    
    // CO2

    block = std::make_shared<shs::RectWidget>(m_tft,
        0, 0, width / 3, height / 2 - 30,
        20, 2,
        shs::ThemeColors::LIGHT_MINT);

    text = std::make_shared<shs::Label>(m_tft,
        0, 0,
        "C02", 2, 1,
        shs::ThemeColors::LIGHT_MINT, shs::ThemeColors::LIGHT_MINT,
        shs::ThemeColors::BACKGROUND);

    text->start();

    block->attachLayer(text, 0, 0,
        shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::TOP,
        0, -text->height / 2);

    attachLayer(block, 0, 0,
        shs::Widget::Align::LEFT | shs::Widget::Align::TOP, 50, 20
    );

    
    // Pressure

    block = std::make_shared<shs::RectWidget>(
        m_tft,
        0, 0, width / 3, height / 2 - 30,
        20, 2,
        shs::ThemeColors::ORANGE
    ); 

    text = std::make_shared<shs::Label>(
        m_tft,
        0, 0,
        "PRESSURE", 2, 1,
        shs::ThemeColors::ORANGE, shs::ThemeColors::ORANGE,
        shs::ThemeColors::BACKGROUND
    );

    text->start();

    block->attachLayer(
        text, 0, 0,
        shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::TOP,
        0, -text->height / 2
    );

    attachLayer(
        block, 0, 0,
        shs::Widget::Align::LEFT | shs::Widget::Align::BOTTOM, 50, 20
    );

    // Time
}

void shs::MainWindow::tick()
{
    Widget::tick();
}