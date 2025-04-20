#include "Label.h"


shs::Label::Label(
    const std::shared_ptr<TFT_eSPI> tft, const shs::t::shs_coord_t x, const shs::t::shs_coord_t y,
    const shs::t::shs_string_t& str,
    const shs::t::shs_font_t set_font, const shs::t::shs_coord_t set_text_size,
    const shs::t::shs_color_t set_background_color, const shs::t::shs_color_t set_foreground_color
)
    : Widget(tft, x, y, 0, 0), m_text(str), font(set_font), text_size(set_text_size),
    background_color(set_background_color), foreground_color(set_foreground_color)
{}


void shs::Label::start()
{
    if (!m_tft) return;
    m_tft->setTextFont(font);
    m_tft->setTextSize(text_size);

    width = m_tft->textWidth(m_text);
    height = m_tft->fontHeight();
}


void shs::Label::tick()
{
    if (!m_tft) return;

    m_tft->setTextColor(shs::utils::rgb565(foreground_color), shs::utils::rgb565(background_color));
    m_tft->setTextFont(font);
    m_tft->setTextSize(text_size);
    m_tft->setCursor(x, y);
    m_tft->print(m_text);

    Widget::tick();
}
