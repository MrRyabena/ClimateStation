#include "Label.h"


shs::Label::Label(
    std::shared_ptr<TFT_eSPI> tft,
    const shs::t::shs_string_t& str,
    const shs::t::shs_font_t set_font, const shs::t::shs_coord_t set_text_size,
    const shs::t::shs_coord_t x, const shs::t::shs_coord_t y,
    const shs::t::shs_coord_t set_width, const shs::t::shs_coord_t set_height,
    const shs::t::shs_coord_t set_radius, const shs::t::shs_coord_t set_stroke,
    const shs::t::shs_color_t set_background_color, const shs::t::shs_color_t set_frame_color,
    const shs::t::shs_color_t set_foreground_color
)
    : Widget(tft, x, y, 0, 0), m_text(str), font(set_font), text_size(set_text_size),
    background_color(set_background_color), foreground_color(set_foreground_color),
    frame_stroke(set_stroke), frame_radius(set_radius), frame_color(set_frame_color),
    text_align(shs::Widget::Align::HORIZONTAL_CENTER | shs::Widget::Align::VERTICAL_CENTER)
{

    if (!m_tft) return;

    m_tft->setTextFont(font);
    m_tft->setTextSize(text_size);

    text_width = m_tft->textWidth(m_text);
    text_height = m_tft->fontHeight();

    width = set_width ? set_width : text_width;
    height = set_height ? set_height : text_height;
}


void shs::Label::tick()
{
    if (!m_tft) return;

    m_tft->setTextColor(shs::utils::rgb565(foreground_color), shs::utils::rgb565(background_color));

    m_tft->setTextFont(font);
    m_tft->setTextSize(text_size);

    if (width == text_width && height == text_height)
    {
        m_tft->setCursor(x, y);
    }
    else
    {
        shs::RectWidget frame(m_tft, x, y,
            width, height,
            frame_radius, frame_stroke,
            frame_color, background_color
        );

        frame.draw();

        auto coords = shs::Widget::getAligned(frame, shs::Widget(m_tft, 0, 0, text_width, text_height), text_align);

        m_tft->setCursor(coords.first, coords.second);

    }

    m_tft->print(m_text);

    Widget::tick();
}
