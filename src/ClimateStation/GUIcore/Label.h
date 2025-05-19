#pragma once


#include "Widget.h"
#include "RectWidget.h"

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
    shs::t::shs_coord_t text_width;
    shs::t::shs_coord_t text_height;
    shs::t::shs_coord_t frame_stroke;
    shs::t::shs_coord_t frame_radius;
    shs::t::shs_color_t frame_color;
    shs::t::shs_color_t background_color;
    shs::t::shs_color_t foreground_color;
    uint8_t text_align;


    Label(std::shared_ptr<TFT_eSPI> tft,
        const shs::t::shs_string_t& str,
        const shs::t::shs_font_t set_font, const shs::t::shs_coord_t set_text_size,
        const shs::t::shs_coord_t x = 0, const shs::t::shs_coord_t y = 0,
        const shs::t::shs_coord_t set_width = 0, const shs::t::shs_coord_t set_height = 0,
        const shs::t::shs_coord_t set_radius = 0, const shs::t::shs_coord_t set_stroke = 0,
        const shs::t::shs_color_t set_background_color = shs::ThemeColors::BACKGROUND,
        const shs::t::shs_color_t set_frame_color = shs::ThemeColors::MINT,
        const shs::t::shs_color_t set_foreground_color = shs::ThemeColors::LIGHT
    );


    void setText(const shs::t::shs_string_t& str) { m_text = str; start(); }
    const shs::t::shs_string_t& getText() { return m_text; }

    void tick() override;

protected:
    shs::t::shs_string_t m_text;

};
