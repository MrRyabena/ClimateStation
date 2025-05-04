#include "ChartWindow.h"

shs::ChartWindow::ChartWindow(std::shared_ptr<TFT_eSPI> tft)
    : Widget(tft, 0, 0, 320, 240)
{}


void shs::ChartWindow::start()
{
    m_tft->fillScreen(shs::utils::rgb565(shs::ThemeColors::BACKGROUND));

    // buttons
    auto block = std::make_shared<shs::RectWidget>(m_tft, 0, 0, m_BUTTON_SIZE, m_BUTTON_SIZE, 8, 2);
    attachLayer(block, shs::Widget::Align::LEFT | shs::Widget::Align::TOP, 10, 10);
    buttons.push_back(block);

    Widget::start();
    Widget::tick();
}

void shs::ChartWindow::tick()
{

}
