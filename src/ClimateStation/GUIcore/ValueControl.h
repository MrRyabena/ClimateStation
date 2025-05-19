#pragma once

#include <memory>

#include <shs_types.h>

#include "Widget.h"
#include "Label.h"
#include "RectWidget.h"

namespace shs
{
    template <typename>
    class ValueControl;
}


template <typename ValueT>
class shs::ValueControl : public shs::Widget
{
public:
    ValueT value{};
    ValueT incr{};

    ValueControl(ValueT start_value, ValueT value_incr,
        std::shared_ptr<TFT_eSPI> tft,
        const shs::t::shs_coord_t set_x, const shs::t::shs_coord_t set_y,
        const shs::t::shs_coord_t set_width, const shs::t::shs_coord_t set_height
    )
        : Widget(tft, set_x, set_y, set_width, set_height), value(start_value), incr(value_incr)
    {}

    void start() override;
    void tick() override;

protected:
    void m_drawValue();
    


};

template<typename ValueT>
inline void shs::ValueControl<ValueT>::start()
{
    // button -
    attachLayer(std::make_shared<shs::Label>(
        m_tft, "-",
        2, 3,
        0, 0, height, height
    ),
        shs::Widget::Align::LEFT | shs::Widget::Align::VERTICAL_CENTER
    );

    // button +
    attachLayer(std::make_shared<shs::Label>(
        m_tft, "+",
        2, 3,
        0, 0, height, height
    ),
        shs::Widget::Align::RIGHT | shs::Widget::Align::VERTICAL_CENTER
    );

    // value
    m_drawValue();
    
    Widget::start();
}

template<typename ValueT>
inline void shs::ValueControl<ValueT>::tick()
{
    uint16_t touch_x{}, touch_y{};

    if (m_tft->getTouch(&touch_x, &touch_y))
    {
        auto i = 0;
        for (auto& x : m_layers)
        {
            x->checkPressed(touch_x, touch_y);
            if (x->isPressed())
            {
                switch (i)
                {
                    case 0: value -= incr; m_drawValue(); break;
                    case 1: value += incr; m_drawValue(); break;
                    default: break;
                }
            }
            i++;
        }
    }

    Widget::tick();
}

template<typename ValueT>
inline void shs::ValueControl<ValueT>::m_drawValue()
{
    shs::Label label(
        m_tft, shs::t::shs_string_t(value),
        2, 2,
        0, 0, width - 2 * height - 2
    );

    shs::Widget::setAligned(*this, label, shs::Widget::Align::CENTER);

    label.tick();
}

