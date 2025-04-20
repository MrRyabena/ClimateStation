#include "RectWidget.h"

shs::RectWidget::RectWidget(
    const std::shared_ptr<TFT_eSPI> tft, const shs::t::shs_coord_t x, const shs::t::shs_coord_t y,
    const shs::t::shs_coord_t width, const shs::t::shs_coord_t height,
    const shs::t::shs_coord_t set_radius, const shs::t::shs_coord_t set_stroke,
    const shs::t::shs_color_t set_stroke_color,
    const shs::t::shs_color_t set_background_color, const shs::t::shs_color_t set_foreground_color
)
    : Widget(tft, x, y, width, height), radius(set_radius), stroke(set_stroke),
    stroke_color(set_stroke_color), background_color(set_background_color), foreground_color(set_foreground_color)
{}

void shs::RectWidget::tick()
{
    if (!m_tft) return;

    m_tft->fillRoundRect(x, y, width, height, radius, shs::utils::rgb565(stroke_color));
    m_tft->fillRoundRect(x + stroke, y + stroke, width - 2 * stroke, height - 2 * stroke, radius - stroke, shs::utils::rgb565(background_color));

    Widget::tick();
}

