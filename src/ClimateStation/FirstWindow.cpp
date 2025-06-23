#include "FirstWindow.h"

void shs::FirstWindow::start()
{
    m_tft->fillScreen(shs::utils::rgb565(shs::ThemeColors::BACKGROUND));

    {
        auto image = std::make_shared<shs::Image>(m_storage, F("logo-mint_220.shsf"), m_tft);
        attachLayer(image, shs::Widget::Align::CENTER);
        image->start();
    }
    delay(3000);
    m_tft->fillScreen(shs::utils::rgb565(shs::ThemeColors::BACKGROUND));

    {
        auto image_n = std::make_shared<shs::Image>(m_storage, F("inscr-mint_300x68.shsf"), m_tft, 0, 0, 300, 68);
        attachLayer(image_n, shs::Widget::Align::CENTER);
        image_n->start();
    }

    delay(3000);
}