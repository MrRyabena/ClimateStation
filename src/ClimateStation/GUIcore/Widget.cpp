#include "Widget.h"

shs::Widget::Widget(const std::shared_ptr<TFT_eSPI> tft, const shs::t::shs_coord_t set_x, const shs::t::shs_coord_t set_y, const shs::t::shs_coord_t set_width, const shs::t::shs_coord_t set_height)
    : m_tft(tft), x(set_x), y(set_y), width(set_width), height(set_height)
{}




