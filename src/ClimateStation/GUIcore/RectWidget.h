#pragma once

#include <memory>

#include <TFT_eSPI.h>

#include "Widget.h"
#include "shs_ThemeColors.h"
#include "types.h"
#include "utils.h"

#define DEBUG
#define SHS_SF_DEBUG
#include <shs_debug.h>
namespace shs
{
    class RectWidget;
}


class shs::RectWidget : public shs::Widget
{
public:
    shs::t::shs_coord_t radius;
    shs::t::shs_color_t stroke;
    shs::t::shs_color_t stroke_color;
    shs::t::shs_color_t background_color;
    shs::t::shs_color_t foreground_color;

    RectWidget(std::shared_ptr<TFT_eSPI> tft,
        const shs::t::shs_coord_t x, const shs::t::shs_coord_t y,
        const shs::t::shs_coord_t width, const shs::t::shs_coord_t height,
        const shs::t::shs_coord_t set_radius, const shs::t::shs_coord_t set_stroke,
        const shs::t::shs_color_t set_stroke_color = shs::ThemeColors::MINT,
        const shs::t::shs_color_t set_background_color = shs::ThemeColors::BACKGROUND,
        const shs::t::shs_color_t set_foreground_color = shs::ThemeColors::LIGHT
    );


    void tick() override;

    void draw();

};


