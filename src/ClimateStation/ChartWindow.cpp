#include "ChartWindow.h"

shs::ChartWindow::ChartWindow(std::shared_ptr<TFT_eSPI> tft, std::shared_ptr<shs::ClimateStationStorage> storage)
    : Widget(tft, 0, 0, 320, 240), m_storage(storage)
{}


void shs::ChartWindow::start()
{
    m_tft->fillScreen(shs::utils::rgb565(shs::ThemeColors::BACKGROUND));

    // buttons
    auto block = std::make_shared<shs::RectWidget>(m_tft, 0, 0, m_BUTTON_SIZE, m_BUTTON_SIZE, 8, 2);
    attachLayer(block, shs::Widget::Align::LEFT | shs::Widget::Align::TOP, 10, 10);
    block->attachLayer(std::make_shared<shs::Image>(m_storage, F("home_icon_30.shsf"), m_tft), shs::Widget::Align::CENTER);
    buttons.push_back(block);

    Widget::start();
    Widget::tick();
}


void shs::ChartWindow::tick()
{

}
