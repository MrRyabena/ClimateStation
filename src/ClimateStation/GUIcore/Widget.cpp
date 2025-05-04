#include "Widget.h"

shs::Widget::Widget(const std::shared_ptr<TFT_eSPI> tft, const shs::t::shs_coord_t set_x, const shs::t::shs_coord_t set_y, const shs::t::shs_coord_t set_width, const shs::t::shs_coord_t set_height)
    : m_tft(tft), x(set_x), y(set_y), width(set_width), height(set_height)
{}

bool shs::Widget::contain(shs::t::shs_coord_t px, shs::t::shs_coord_t py) const
{
    return px >= x && px <= x + width && py >= y && py <= y + height;
}

void shs::Widget::setPressed(const bool pressed)
{
    m_last_pressed = m_pressed;
    m_pressed = pressed;
}

bool shs::Widget::checkPressed(const shs::t::shs_coord_t px, const shs::t::shs_coord_t py)
{
    auto pressed = contain(px, py);
    setPressed(pressed);

    return pressed;
}

bool shs::Widget::isPressed() const
{
    return m_pressed;
}

bool shs::Widget::justPressed() const
{
    return m_pressed && !m_last_pressed;
}

bool shs::Widget::justReleased() const
{
    return !m_pressed && m_last_pressed;
}


void shs::Widget::setPosition(const shs::t::shs_coord_t px, const shs::t::shs_coord_t py)
{
    auto shift_x = px - x;
    auto shift_y = py - y;

    x = px;
    y = py;

    for (auto& l : m_layers) l->setPosition(l->x + shift_x, l->y + shift_y);
}


void shs::Widget::attachLayer(std::shared_ptr<shs::Widget> ptr, const uint8_t align, const shs::t::shs_coord_t horizontal_margin, const shs::t::shs_coord_t vertical_margin)
{
    if (!ptr) return;

    auto coords = getAligned(*this, *ptr, align, horizontal_margin, vertical_margin);
    dout(coords.first); doutln(coords.second);

    ptr->setPosition(coords.first, coords.second);

    m_layers.push_back(ptr);
}

std::pair<shs::t::shs_coord_t, shs::t::shs_coord_t> shs::Widget::getAligned(const shs::Widget& w1, const shs::Widget& w2, const uint8_t align, const shs::t::shs_coord_t horizontal_margin, const shs::t::shs_coord_t vertical_margin)
{
    shs::t::shs_coord_t next_x{}, next_y{};

    if (align & Align::HORIZONTAL_CENTER) next_x = w1.x + w1.width / 2 - w2.width / 2 + horizontal_margin;
    else if (align & Align::LEFT)         next_x = w1.x + horizontal_margin;
    else if (align & Align::RIGHT)        next_x = w1.x + w1.width - w2.width - horizontal_margin;
    else                                  next_x = w1.x + w2.x;

    if (align & Align::VERTICAL_CENTER) next_y = w1.y + w1.height / 2 - w2.height / 2 + vertical_margin;
    else if (align & Align::TOP)        next_y = w1.y + vertical_margin;
    else if (align & Align::BOTTOM)     next_y = w1.y + w1.height - w2.height - vertical_margin;
    else                                next_y = w1.y + w2.y;

    return std::pair<shs::t::shs_coord_t, shs::t::shs_coord_t>(next_x, next_y);
}

void shs::Widget::setAligned(const shs::Widget& w1, shs::Widget& w2, const uint8_t align, const shs::t::shs_coord_t horizontal_margin, const shs::t::shs_coord_t vertical_margin)
{
    auto coords = getAligned(w1, w2, align, horizontal_margin, vertical_margin);

    w2.setPosition(coords.first, coords.second);
}
