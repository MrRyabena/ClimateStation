#include "Widget.h"

shs::Widget::Widget(const std::shared_ptr<TFT_eSPI> tft, const shs::t::shs_coord_t set_x, const shs::t::shs_coord_t set_y, const shs::t::shs_coord_t set_width, const shs::t::shs_coord_t set_height)
    : m_tft(tft), x(set_x), y(set_y), width(set_width), height(set_height)
{}


void shs::Widget::setPosition(const shs::t::shs_coord_t px, const shs::t::shs_coord_t py)
{
    auto shift_x = px - x;
    auto shift_y = py - y;

    x = px;
    y = py;

    for (auto& l : m_layers) l->setPosition(l->x + shift_x, l->y + shift_y);
}


void shs::Widget::attachLayer(std::shared_ptr<shs::Widget> ptr, const shs::t::shs_coord_t px, const shs::t::shs_coord_t py, const uint8_t align, const shs::t::shs_coord_t horizontal_margin, const shs::t::shs_coord_t vertical_margin)
{
    if (!ptr) return;

    shs::t::shs_coord_t shift_x{}, shift_y{};

    if (align & Align::HORIZONTAL_CENTER) shift_x = x + width / 2 - ptr->width / 2 + horizontal_margin;
    else if (align & Align::LEFT)         shift_x = x + horizontal_margin;
    else if (align & Align::RIGHT)        shift_x = x + width - ptr->width - horizontal_margin;
    else                                  shift_x = x + px;

    if (align & Align::VERTICAL_CENTER) shift_y = y + height / 2 - ptr->height / 2 + vertical_margin;
    else if (align & Align::TOP)        shift_y = y + vertical_margin;
    else if (align & Align::BOTTOM)     shift_y = y + height - ptr->height - vertical_margin;
    else                                shift_y = y + py;

    ptr->setPosition(shift_x, shift_y);

    m_layers.push_back(ptr);
}
