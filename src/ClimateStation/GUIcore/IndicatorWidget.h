#pragma once

#include <memory>

#include <TFT_eSPI.h>       // https://github.com/Bodmer/TFT_eSPI

#include <shs_types.h>

#include "Widget.h"
#include "shs_ThemeColors.h"
#include "utils.h"


namespace shs
{
    class IndicatorWidget;
}


class shs::IndicatorWidget : public shs::Widget
{
public:

    enum class ValueTrend : uint8_t { INCREASING, DECREASING, CONST };


    shs::t::shs_font_t value_font;
    shs::t::shs_font_t unit_font;

    shs::t::shs_coord_t value_size;
    shs::t::shs_coord_t unit_size;

    uint8_t value_align;
    uint8_t unit_align;

    shs::t::shs_coord_t value_horizontal_margin{};
    shs::t::shs_coord_t value_vertical_margin{};
    shs::t::shs_coord_t unit_horizontal_margin{};
    shs::t::shs_coord_t unit_vertical_margin{};


    shs::t::shs_color_t background_color;
    shs::t::shs_color_t foreground_color;



    IndicatorWidget(std::shared_ptr<TFT_eSPI> tft,
        const shs::t::shs_coord_t set_x, const shs::t::shs_coord_t set_y,
        const shs::t::shs_coord_t set_width, const shs::t::shs_coord_t set_height,
        const shs::t::shs_string_t& set_unit,
        const shs::t::shs_font_t set_value_font, const shs::t::shs_font_t set_unit_font,
        const shs::t::shs_coord_t set_value_size, const shs::t::shs_coord_t set_unit_size,
        const shs::t::shs_color_t set_foreground_color = shs::ThemeColors::LIGHT,
        const shs::t::shs_color_t set_background_color = shs::ThemeColors::BACKGROUND,
        const uint8_t set_value_align = shs::Widget::LEFT,
        const uint8_t set_unit_align = shs::Widget::RIGHT
    );


    void draw(const shs::t::shs_string_t& value, ValueTrend trend);

    void setUnit(const shs::t::shs_string_t& unit);

    void drawArrow(const shs::Widget& base, ValueTrend trend);

protected:
    shs::t::shs_string_t m_unit;
    shs::t::shs_coord_t m_unit_width;
    shs::t::shs_coord_t m_unit_height;
};
