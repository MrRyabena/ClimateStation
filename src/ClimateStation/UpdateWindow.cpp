#include "UpdateWindow.h"

void shs::UpdateWindow::start()
{
    m_tft->fillScreen(shs::utils::rgb565(shs::ThemeColors::BACKGROUND));

    AutoOTA ota(m_version, "https://raw.githubusercontent.com/MrRyabena/ClimateStation/main/project.json");

    auto label = std::make_shared<shs::Label>(m_tft, shs::t::shs_string_t(F("Version: ")) + ota.version(), 2, 2);
    attachLayer(label, shs::Widget::Align::CENTER);
    label->tick();
    delay(2000);
    m_tft->fillScreen(shs::utils::rgb565(shs::ThemeColors::BACKGROUND));


    String ver, notes;
    if (ota.checkUpdate(&ver, &notes))
    {
        {
            auto label = std::make_shared<shs::Label>(m_tft, shs::t::shs_string_t(F("New version: ")) + ver, 2, 2);
            attachLayer(label, shs::Widget::Align::CENTER);
            label->tick();
            delay(2000);
            m_tft->fillScreen(shs::utils::rgb565(shs::ThemeColors::BACKGROUND));
        }

        auto label = std::make_shared<shs::Label>(m_tft, F("Updating..."), 2, 2);
        attachLayer(label, shs::Widget::Align::CENTER);
        label->tick();

        ota.updateNow();
    }
    else if (ota.hasError() && (int)ota.getError() != 7)
    {
        m_tft->fillScreen(shs::utils::rgb565(shs::ThemeColors::BACKGROUND));
        auto label = std::make_shared<shs::Label>(m_tft, shs::t::shs_string_t(F("ERROR: ")) + (int)ota.getError(), 2, 2);
        attachLayer(label, shs::Widget::Align::CENTER);
        label->tick();
        delay(2000);
    }
}