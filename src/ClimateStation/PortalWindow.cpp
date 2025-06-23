#include "PortalWindow.h"

void shs::PortalWindow::start()
{
    // buttons
    // auto block = std::make_shared<shs::RectWidget>(m_tft, 0, 0, m_BUTTON_SIZE, m_BUTTON_SIZE, 8, 2);
    // attachLayer(block, shs::Widget::Align::LEFT | shs::Widget::Align::TOP, 10, 10);
    // block->attachLayer(std::make_shared<shs::Image>(m_storage, F("home_icon_30.shsf"), m_tft), shs::Widget::Align::CENTER);

    // buttons.push_back(block);

    // m_tft->fillScreen(shs::utils::rgb565(shs::ThemeColors::BACKGROUND));

    // portalStart();

    // shs::Label l1(m_tft,
    //     F("Please, connect your phone to WiFi access point: \"SHS_ClimateStation\"."),
    //     10, 60, 2, 1);

    // l1.tick();

    // shs::Label l2(m_tft, F("Then go to \"192.168.1.1\" in browser."), 10, 80, 2, 1);
    // l2.tick();

    Widget::start();

}

void shs::PortalWindow::tick()
{
    // if (portalTick())
    // {
    //     if (portalStatus() == SP_SUBMIT)
    //     {
    //         shs::ControlWiFi::connectWiFi(portalCfg.SSID, portalCfg.pass);
    //     }
    // }

    Widget::tick();
}
