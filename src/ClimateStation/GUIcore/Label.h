#pragma once


#include "Widget.h"

#include <shs_types.h>
#include "types.h"
#include "utils.h"

namespace shs
{
    class Label;
}


class shs::Label : public shs::Widget
{
public:
    shs::t::shs_font_t font;
    shs::t::shs_coord_t text_size;
    shs::t::shs_color_t background_color;
    shs::t::shs_color_t foreground_color;


    Label(const std::shared_ptr<TFT_eSPI> tft, const shs::t::shs_coord_t x, const shs::t::shs_coord_t y,
        const shs::t::shs_string_t& str,
        const shs::t::shs_font_t set_font, const shs::t::shs_coord_t set_text_size,
        const shs::t::shs_color_t set_background_color = shs::ThemeColors::BACKGROUND,
        const shs::t::shs_color_t set_foreground_color = shs::ThemeColors::LIGHT
    );


    void setText(const shs::t::shs_string_t& str) { m_text = str; start(); }
    const shs::t::shs_string_t& getText() { return m_text; }

    void start() override;
    void tick() override;

protected:
    shs::t::shs_string_t m_text;

};
